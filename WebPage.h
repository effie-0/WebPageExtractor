//////////////////////////////////////////////
//WebPage.h
//
//author:杨璧菲2015013217
//////////////////////////////////////////////
//该部分进行了网页的解析操作
//实现了网页WebPage这个对象
//主要功能（接口）有：
//1、由文件名称获取读取该文件
//2、使用栈结构遍历信息，获取相应关键信息
//3、输出关键信息到文件
/////////////////////////////////////////////

#ifndef WEBPAGE_H
#define WEBPAGE_H

#include"CharString.h"
#include <iostream>
#include <string>
using namespace std;

class WebPage
{
public:
	CharString title;
	CharString body;
	CharString div;
	CharString span;
	CharString p;
	CharString li;
	CharString h2;
	CharString h1;
	CharString question;
	CharString author;
	CharString content;
	CharString img;
	CharString extraInfo;
	CharString meta;
	CharString link;
	CharString base;
	//static CharString lt;//左标签<
	//static CharString rt;//右标签>

public:
	static const int ERROR = 0;
	string m_fileName;//网页文件名
	CharString m_title;//标题
	CharString m_question;//问题
	CharString m_author;//作者
	CharString m_content;//内容

	WebPage();
	~WebPage(){}
	//拷贝构造函数
	WebPage(const WebPage& page);
};

extern bool match(CharString& mainStr, const CharString& otherStr);
//解析网址，获取关键信息（todo:中文分词）
extern void extractInfo(WebPage& page, string inputPath);
//输出信息到*.info文件中
extern void printInfo(WebPage& page, string outputPath);

#endif