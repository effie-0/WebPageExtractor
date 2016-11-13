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
}

WebPage::WebPage(const WebPage& page)
{
	//fileName = page.fileName;
	m_title = page.m_title;
	m_question = page.m_question;
	m_author = page.m_author;
	m_content = page.m_content;
}

void WebPage::extractInfo(string inputPath)
{
	ifstream fl(inputPath);
 	if(!fl.is_open())
		exit(ERROR);
	wbuffer_convert<codecvt_utf8<wchar_t>> conv(fl.rdbuf());
	wistream fin(&conv);
	//m_fileName = inputPath;

	Stack<CharString> m_stack(MAX_STACK_SIZE);
	CharString tempElem;//临时存储进出栈元素
	CharString cmpElem;//用于比较标签是否相同的字符串
	ElemType ch1, ch2;
	Stringbuff tagBuff;//标签缓冲区
	Stringbuff contentBuff;//内容缓冲区
	//tag是标志位，判断接下来读的那一行应该进行的操作
	//如果是0的话表示当前应该储存的字符串为应该进栈的标签
	//1，结束标签
	//2，内容
	//-1，暂时不需要储存
	int tag = -1;
	bool startContent = false;//正文正式开始
	while(!fin.eof())
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
				m_stack.top(tempElem);
				tagBuff.clear();
				fin.getline(tagBuff.data, tempElem.length + 2, '>');
				cmpElem.assign(tagBuff.data);
				if(match(tempElem, cmpElem) && cmpElem.length != 0)//标签相同，匹配
				{
					m_stack.pop();
					tag = -1;
					if(m_title.length == 0 && tempElem.indexOf(title, 0) != -1)
					{
						m_title.assign(contentBuff.data);
						contentBuff.clear();
					}
					else if(m_question.length == 0 && tempElem.indexOf(h2, 0) != -1 && tempElem.indexOf(question, 0) != -1)
					{
						m_question.assign(contentBuff.data);
						contentBuff.clear();
					}
					else if(m_author.length == 0 && tempElem.indexOf(span, 0) != -1 && tempElem.indexOf(author, 0) != -1)
					{
						m_author.assign(contentBuff.data);
						if(m_author.length >= 2)
						{
							if(m_author.data[m_author.length - 1] == L'，')
							{
								m_author.length--;
								m_author.data[m_author.length] = '\0';
							}
						}
						contentBuff.clear();
					}
					else if(m_content.length == 0 && tempElem.indexOf(div, 0) != -1 && tempElem.indexOf(content, 0) != -1)
					{
						m_content.assign(contentBuff.data);
						contentBuff.clear();
						break;//如果内容也存完了，就不再遍历，直接退出
					}
					else if(match(tempElem, p) || match(tempElem, li))
					{
						contentBuff.append('\n');
					}
					//其他标签不用管，直接ignore就好
				}
				else
					continue;//如果不匹配也不用管（？）TODO
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
				if(match(tempElem, img) || match(tempElem, meta) || match(tempElem, link) || match(tempElem, base))
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
				if(tempElem.indexOf(extraInfo, 0) == -1)
				{
					if(!startContent && tempElem.indexOf(content, 0) != -1)
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

void WebPage::printInfo(string outputPath)
{
	//参考了http://blog.csdn.net/xujiezhige/article/details/17843831上的内容，对输出进行设置
	std::locale oNewLocale(std::locale(), "", std::locale::ctype);
	std::locale oPreviousLocale = std::locale::global(oNewLocale);

	wofstream fout(outputPath, ios::out);
	fout << m_title.data << endl;
	fout << m_question.data << endl;
	fout << m_author.data << endl;
	fout << m_content.data << endl;
	fout.close();

	std::locale::global(oPreviousLocale);
}

bool match(CharString& mainStr, const CharString& otherStr)
{
	int num = mainStr.indexOf(otherStr, 0);
	if(num != -1 && num <= otherStr.length + 3)
		return true;
	else
		return false;
}