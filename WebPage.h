//////////////////////////////////////////////
//WebPage.h
//
//author:��起�2015013217
//////////////////////////////////////////////
//�ò��ֽ�������ҳ�Ľ�������
//ʵ������ҳWebPage�������
//��Ҫ���ܣ��ӿڣ��У�
//1�����ļ����ƻ�ȡ��ȡ���ļ�
//2��ʹ��ջ�ṹ������Ϣ����ȡ��Ӧ�ؼ���Ϣ
//3������ؼ���Ϣ���ļ�
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
	//static CharString lt;//���ǩ<
	//static CharString rt;//�ұ�ǩ>

public:
	static const int ERROR = 0;
	string m_fileName;//��ҳ�ļ���
	CharString m_title;//����
	CharString m_question;//����
	CharString m_author;//����
	CharString m_content;//����

	WebPage();
	~WebPage(){}
	//�������캯��
	WebPage(const WebPage& page);
};

extern bool match(CharString& mainStr, const CharString& otherStr);
//������ַ����ȡ�ؼ���Ϣ��todo:���ķִʣ�
extern void extractInfo(WebPage& page, string inputPath);
//�����Ϣ��*.info�ļ���
extern void printInfo(WebPage& page, string outputPath);

#endif