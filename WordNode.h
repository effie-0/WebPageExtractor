//////////////////////////////////////////////
//WordNode.h
//
//author:��起�2015013217
//////////////////////////////////////////////
//�ò��������˵��ʽڵ���WordNode
//�Լ��ĵ��ڵ���DocNode
//////////////////////////////////////////////

#ifndef WORDNODE_H
#define WORDNODE_H

#include "CharString.h"
#include "Link.h"
#include <iostream>

class DocNode
{
public:
	int docID;//���ָõ��ʵ��ĵ�ID
	int times;//���ʳ��ֵĴ���
	int termSum;//���ֵĹؼ��ʸ������ϲ������ʱ��Ҫ��
	int mergeTimes;//�ϲ�֮����ֵ��ܴ���

	DocNode() : docID(-1), times(0), termSum(0), mergeTimes(0) {}
	DocNode(int ID) : docID(ID), times(1), termSum(1), mergeTimes(1){}
	DocNode(const DocNode& other) : docID(other.docID), times(other.times) , termSum(other.termSum), mergeTimes(other.mergeTimes){}

	void addTimes();//���ӵ��ʳ��ִ���
	void addMergeTimes(const DocNode& other);//���ӵ��ʺϲ�֮��Ĵ���
	bool IDisEqual(const DocNode& other);//�ж�ID�Ƿ���ͬ
	bool IDisEqual(int DocNum);//���أ��ж�ID�Ƿ���ͬ
	DocNode& operator=(const DocNode& other);//=���������
	bool operator==(const DocNode& other)const;//==���������
	void printContent(std::wostream &fout);//����ڵ�����
};

class WordNode
{
public:
	CharString term;//����
	int termID;//����ID�������ò��ϣ�
	int articalNum;//��������
	int occurTimes;//�����ܴ���
	Link<DocNode> m_link;//��������

	WordNode() : articalNum(0), occurTimes(0), termID(0) {}
	WordNode(CharString t) : term(t), articalNum(0), occurTimes(0), termID(0) {}
	//�������캯��
	WordNode(const WordNode& other) : term(other.term), termID(other.termID), 
		articalNum(other.articalNum), occurTimes(other.occurTimes), m_link(other.m_link){}

	void addArtical(int docNum);//�����������������
	//=���������
	WordNode& operator=(const WordNode& other);
	//==���������
	bool operator==(const WordNode& other)const;
};

//�ϲ��������ؼ��ֵ����������ǰ��������wordLink���е����йؼ��ֶ�����ͬ
extern void mergeOutcome(Link<WordNode> &wordLink, std::wostream& fout);
#endif