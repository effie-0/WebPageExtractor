//////////////////////////////////////////////
//WordNode.h
//
//author:杨璧菲2015013217
//////////////////////////////////////////////
//该部分声明了单词节点类WordNode
//以及文档节点类DocNode
//////////////////////////////////////////////

#ifndef WORDNODE_H
#define WORDNODE_H

#include "CharString.h"
#include "Link.h"
#include <iostream>

class DocNode
{
public:
	int docID;//出现该单词的文档ID
	int times;//单词出现的次数
	int termSum;//出现的关键词个数，合并输出的时候要用
	int mergeTimes;//合并之后出现的总次数

	DocNode() : docID(-1), times(0), termSum(0), mergeTimes(0) {}
	DocNode(int ID) : docID(ID), times(1), termSum(1), mergeTimes(1){}
	DocNode(const DocNode& other) : docID(other.docID), times(other.times) , termSum(other.termSum), mergeTimes(other.mergeTimes){}

	void addTimes();//增加单词出现次数
	void addMergeTimes(const DocNode& other);//增加单词合并之后的次数
	bool IDisEqual(const DocNode& other);//判断ID是否相同
	bool IDisEqual(int DocNum);//重载，判断ID是否相同
	DocNode& operator=(const DocNode& other);//=运算符重载
	bool operator==(const DocNode& other)const;//==运算符重载
	void printContent(std::wostream &fout);//输出节点内容
};

class WordNode
{
public:
	CharString term;//单词
	int termID;//单词ID（可能用不上）
	int articalNum;//文章数量
	int occurTimes;//出现总次数
	Link<DocNode> m_link;//文章链表

	WordNode() : articalNum(0), occurTimes(0), termID(0) {}
	WordNode(CharString t) : term(t), articalNum(0), occurTimes(0), termID(0) {}
	//拷贝构造函数
	WordNode(const WordNode& other) : term(other.term), termID(other.termID), 
		articalNum(other.articalNum), occurTimes(other.occurTimes), m_link(other.m_link){}

	void addArtical(int docNum);//将文章添加入链表中
	//=运算符重载
	WordNode& operator=(const WordNode& other);
	//==运算符重载
	bool operator==(const WordNode& other)const;
};

//合并多个多个关键字的搜索结果，前提条件是wordLink当中的所有关键字都不相同
extern void mergeOutcome(Link<WordNode> &wordLink, std::wostream& fout);
#endif