//
//main.cpp
//用于输出关于大作业第一个部分的内容
//
//author:杨璧菲2015013217

#include <iostream>
#include "WebPage.h"
#include "Stack.h"
#include "Stringbuff.h"
#include "Dictionary.h"
#include <string>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char* args[])
{
	system("dir /b .\\input >> directory.txt");
	ifstream dir("directory.txt");
	if(!dir.is_open())
	{
		cerr << "the directory cannot be open" << endl;
		return 1;
	}

	string inputName;
	string dicPath = ".\\extraInfo\\词库.dic";
	Dictionary m_dic;
	cout << "loading my dictionary..." << endl;
	initDictionary(m_dic, dicPath);

	string m_pagePath = ".\\input\\";
	string m_outPath = ".\\output\\";
	string out1 = "info";
	string out2 = "txt";

	while(!dir.eof())
	{
		dir >> inputName;
		WebPage m_page;
		string m_inPath = m_pagePath + inputName;
		string m_outPath1 = m_outPath + inputName;
		int length = m_outPath1.length() - 4;
		m_outPath1 = m_outPath1.substr(0, length);
		m_outPath1 += out1;
		extractInfo(m_page, m_inPath);
		printInfo(m_page, m_outPath1);

		CharStringLink m_link(divideWords(m_dic, m_page));
		string m_outPath2 = m_outPath + inputName;
		m_outPath2 = m_outPath2.substr(0, length);
		m_outPath2 += out2;
		m_link.printLink(m_outPath2);
	};
	dir.close();
	return 0;
}