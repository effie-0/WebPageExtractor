//
//Dictionary.h
//
//author:杨璧菲2015013217
//
//实现了字典类Dictionary的加载功能

#include "Dictionary.h"
#include <fstream>
#include <locale>
#include <codecvt>
#define MAX_WORD_SIZE 30

bool initDictionary(Dictionary& m_dic, string fileName)
{
	//参考了群主@孙子平 的三行输入输出代码
	ifstream infile(fileName);
	wbuffer_convert<codecvt_utf8<wchar_t>> conv(infile.rdbuf());
	wistream fin(&conv);

	if(!infile.is_open())
	{
		cerr << "Unable to open the file" << endl;
		return false;
	}

	wchar_t temp[MAX_WORD_SIZE];
	CharString m_string;
	m_dic.maxLength = 0;
	while(!fin.eof())
	{
		fin >> temp;
		m_string.assign(temp);
		if(m_string.length > m_dic.maxLength)
			m_dic.maxLength = m_string.length;
		m_dic.stringMap[m_string] = 1;
	}
	return true;
}

CharStringLink divideWords(Dictionary& m_dic, WebPage& m_page)
{
	CharStringLink outputLink;//返回的链表
	int current = 0;//在m_page的content里面用于不断向后移动的光标
	int length = m_dic.maxLength;
	CharString tempStr;//临时储存变量的字符串
	map<CharString, int>::iterator iter;
	bool result = true;//判断当前字符串长度是否>1
	while(current < m_page.m_content.length)
	{
		tempStr = m_page.m_content.substring(current, length);
		iter = m_dic.stringMap.find(tempStr);
		if(iter != m_dic.stringMap.end())
		{
			//字符串在字典中
			outputLink.append(tempStr);
			current += length;
			length = m_dic.maxLength;
		}
		else
		{
			length--;
			result = tempStr.trim();
			if(!result)
			{
				if(tempStr.data[0] >= 0x4E00 && tempStr.data[0] <= 0x9FBB)
				{
					outputLink.append(tempStr);
					current += 1;
					length = m_dic.maxLength;
				}
				else
				{
					current += 1;
					length = m_dic.maxLength;
				}
			}
		}
	};

	return outputLink;
}
