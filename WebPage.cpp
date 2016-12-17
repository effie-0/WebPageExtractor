//
//WebPage.cpp
//
//author:杨璧菲2015013217
//
//实现了网页WebPage类的内容

#include "WebPage.h"
#include "Stack.h"
#include "Stringbuff.h"
#include <fstream>
#include <locale>
#include <cstdlib>
#include <codecvt>
#define MAX_STACK_SIZE 500
#define MAX_TEMP_LENGTH 50//输入缓冲长度
using namespace std;

WebPage::WebPage()
{
		title.assign(L"title");
		body.assign(L"body");
		div.assign(L"div");
		span.assign(L"span");
		p.assign(L"p");
		li.assign(L"li");
		h2.assign(L"h2");
		h1.assign(L"h1");
		question.assign(L"question");
		author.assign(L"author");
		content.assign(L"\"content\"");
		img.assign(L"img");
		extraInfo.assign(L"!doctype html");
		meta.assign(L"meta");
		link.assign(L"link");
		base.assign(L"base");
		//lt.assign("<");
		//rt.assign(">");

		docID = 0;
}

WebPage::WebPage(const WebPage& page)
{
	m_title = page.m_title;
	m_question = page.m_question;
	m_author = page.m_author;
	m_content = page.m_content;
	docID = page.docID;
}

void extractInfo(WebPage& page, string inputPath)
{
	//参考了群主@孙子平 的三行输入输出代码
	ifstream fl(inputPath);
 	if(!fl.is_open())
		exit(page.ERROR);
	wbuffer_convert<codecvt_utf8<wchar_t>> conv(fl.rdbuf());
	wistream fin(&conv);
	page.getID(inputPath);

	Stack<CharString> m_stack(MAX_STACK_SIZE);
	CharString tempElem;//临时存储进出栈元素
	CharString cmpElem;//用于比较标签是否相同的字符串
	ElemType ch1, ch2;
	Stringbuff tagBuff;//标签\缓冲区
	Stringbuff contentBuff;//内容缓冲区
	//tag是标志位，判断接下来读的那一行应该进行的操作
	//如果是0的话表示当前应该储存的字符串为应该进栈的标签
	//1，结束标签
	//2，内容
	//-1，暂时不需要储存
	int tag = -1;
	bool startContent = false;//正文正式开始
	Status StackStatus = Stack<CharString>::OK;
	bool isEnd = false;
	while(!fin.eof() && StackStatus != m_stack.ERROR && !isEnd)
	{
		fin.get(ch1);
		if(ch1 == '\n')
			continue;

		if(ch1 == '<')
		{
			tag = 0;
			do
			{
				fin.get(ch2);
			}while(ch2 == '\n');
			
			//cout << ch2 << flush;
			if(ch2 == '/')
			{
				tag = 1;
				StackStatus = m_stack.pop(tempElem);
				tagBuff.clear();
				fin.getline(tagBuff.data, tempElem.length + 10, '>');
				cmpElem.assign(tagBuff.data);
				bool isMatch = false;
				do
				{
					if(match(tempElem, cmpElem) && cmpElem.length != 0)//标签相同，匹配
					{
						isMatch = true;
						if(!startContent)
							tag = -1;
						if(page.m_title.length == 0 && tempElem.indexOf(page.title, 0) != -1)
						{
							page.m_title.assign(contentBuff.data);
							contentBuff.clear();
						}
						else if(page.m_question.length == 0 && tempElem.indexOf(page.h2, 0) != -1 && tempElem.indexOf(page.question, 0) != -1)
						{
							page.m_question.assign(contentBuff.data);
							contentBuff.clear();
						}
						else if(page.m_author.length == 0 && tempElem.indexOf(page.span, 0) != -1 && tempElem.indexOf(page.author, 0) != -1)
						{
							page.m_author.assign(contentBuff.data);
							if(page.m_author.length >= 2)
							{
								if(page.m_author.data[page.m_author.length - 1] == L'，')
								{
									page.m_author.length--;
									page.m_author.data[page.m_author.length] = '\0';
								}
							}
							contentBuff.clear();
						}
						else if(tempElem.indexOf(page.div, 0) != -1 && tempElem.indexOf(page.content, 0) != -1)
						{
							if(page.m_content.length == 0)
								page.m_content.assign(contentBuff.data);
							else if(page.m_content.length < 100)
							{
								page.m_content.concat(contentBuff.data);
								//contentBuff.clear();
								//while(!m_stack.One())
								//{
								//	CharString elem;
								//	StackStatus = m_stack.pop(elem);
								//};
								isEnd = true;
								//break;
							}
							contentBuff.clear();
						}
						else if(match(tempElem, page.p) || match(tempElem, page.li))
						{
							contentBuff.append('\n');
						}
						//其他标签不用管，直接ignore就好
					}
					else
					{
						StackStatus = m_stack.pop(tempElem);
					}
				}while(!isMatch && !fin.eof() && StackStatus != m_stack.ERROR && StackStatus != m_stack.M_OVERFLOW);
			}
			else
			{
				tagBuff.append(ch2);
				continue;
				//继续往下读，直到读到>为止
			}
		}
		else if(ch1 == '>')
		{
			if(tag == 0)
			{
				//进栈操作，如果是结束标或者自闭合标签的话就不用管了
				tempElem.assign(tagBuff.data);
				tagBuff.clear();
				if(match(tempElem, page.img) || match(tempElem, page.meta) || match(tempElem, page.link) || match(tempElem, page.base))
				{
					tag = -1;
					continue;
				}
				else if(tempElem.length >= 2)
				{
					if(tempElem.data[tempElem.length - 1] == '/')
					{
						tag = -1;
						continue;
					}
				}
				m_stack.push(tempElem);
				if(tempElem.indexOf(page.extraInfo, 0) == -1)
				{
					if(!startContent && tempElem.indexOf(page.content, 0) != -1)
						startContent = true;
					if(!startContent)
						contentBuff.clear();
					tag = 2;
				}
				else
					tag = -1;
			}
			else
			{
				continue;
			}
		}
		else
		{
			if(tag == 0)//只有需要进栈的标签才储存其中内容，结束标签不需要
			{
				tagBuff.append(ch1);
			}
			else if(tag == 2)
			{
				contentBuff.append(ch1);
			}
		}
	};

}

void printInfo(WebPage& page, string outputPath)
{
	//参考了群主@孙子平 的三行输入输出代码
	ofstream outFile(outputPath);
	wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(outFile.rdbuf());
	wostream fout(&conv);
	if(page.m_title.data != nullptr)
		fout << page.m_title.data << endl;
	else
		fout << endl;

	if(page.m_question.data != nullptr)
		fout << page.m_question.data << endl;
	else
		fout << endl;

	if(page.m_author.data != nullptr)
		fout << page.m_author.data << endl;
	else
		fout << endl;

	if(page.m_content.data != nullptr)
		fout << page.m_content.data << endl;
	else
		fout << endl;
	outFile.close();
}

bool match(CharString mainStr, const CharString& otherStr)
{
	int num = mainStr.indexOf(otherStr, 0);
	if(num != -1 && num <= otherStr.length + 3)
		return true;
	else
		return false;
}

void WebPage::getID(string inputPath)
{
	const char* str = inputPath.data();
	int i;
	docID = 0;
	int length = inputPath.length();
	for(i = 8; i < length - 5; i++)
	{
		docID = docID * 10 + str[i] - '0';
	}
}