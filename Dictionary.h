//////////////////////
//
//Dictionatry.h
//
//author:杨璧菲2015013217
//////////////////////
//该部分实现了字典类
//加载了字典的相关信息
//主要实现的功能有
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
	int maxLength;//字典里最长的字符串的长度

	//Dictionary(){maxLength = 0;}
};

//初始化字典，成功返回true，不成功返回false
extern bool initDictionary(Dictionary& m_dic, string fileName);
//分词
extern CharStringLink divideWords(Dictionary& m_dic, WebPage& m_page);
//重载分词函数，创建平衡二叉树
extern void divideWords(Dictionary& m_dic, WebPage& m_page, AVLTree<WordNode, CharString> &tree);

#endif