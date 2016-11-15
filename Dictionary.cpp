//
//Dictionary.h
//
//author:��起�2015013217
//
//ʵ�����ֵ���Dictionary�ļ��ع���

#include "Dictionary.h"
#include <fstream>
#include <locale>
#include <codecvt>
#define MAX_WORD_SIZE 30

bool initDictionary(Dictionary& m_dic, string fileName)
{
	//�ο���Ⱥ��@����ƽ �����������������
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
	CharStringLink outputLink;//���ص�����
	int current = 0;//��m_page��content�������ڲ�������ƶ��Ĺ��
	int length = m_dic.maxLength;
	CharString tempStr;//��ʱ����������ַ���
	map<CharString, int>::iterator iter;
	bool result = true;//�жϵ�ǰ�ַ��������Ƿ�>1
	while(current < m_page.m_content.length)
	{
		tempStr = m_page.m_content.substring(current, length);
		iter = m_dic.stringMap.find(tempStr);
		if(iter != m_dic.stringMap.end())
		{
			//�ַ������ֵ���
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
