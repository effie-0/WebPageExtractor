//////////////////////
//
//Dictionatry.h
//
//author:��起�2015013217
//////////////////////
//�ò���ʵ�����ֵ���
//�������ֵ�������Ϣ
//��Ҫʵ�ֵĹ�����
//
///////////////////////

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <map>
#include <string>
#include "CharString.h"
#include "CharStringLink.h"
#include "WebPage.h"
#include "AVLTree.h"
#include "WordNode.h"
using namespace std;

class Dictionary
{
public:
	map<CharString, int> stringMap;
	int maxLength;//�ֵ�������ַ����ĳ���

	//Dictionary(){maxLength = 0;}
};

//��ʼ���ֵ䣬�ɹ�����true�����ɹ�����false
extern bool initDictionary(Dictionary& m_dic, string fileName);
//�ִ�
extern CharStringLink divideWords(Dictionary& m_dic, WebPage& m_page);
//���طִʺ���������ƽ�������
extern void divideWords(Dictionary& m_dic, WebPage& m_page, AVLTree<WordNode, CharString> &tree);

#endif