//////////////////////////////////////////////
//WordNode.h
//
//author:��起�2015013217
//////////////////////////////////////////////
//�ò��������˵��ʽڵ���
/////////////////////////////////////////////

#ifndef WORDNODE_H
#define WORDNODE_H

#include "CharString.h"

class WordNode
{
public:
	CharString term;//����
	int articalNum;//��������
	int occur;//�����ܴ���

	WordNode() : articalNum(0), occur(0) {}
};

#endif