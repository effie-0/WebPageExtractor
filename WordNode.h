//////////////////////////////////////////////
//WordNode.h
//
//author:杨璧菲2015013217
//////////////////////////////////////////////
//该部分声明了单词节点类
/////////////////////////////////////////////

#ifndef WORDNODE_H
#define WORDNODE_H

#include "CharString.h"

class WordNode
{
public:
	CharString term;//单词
	int articalNum;//文章数量
	int occur;//出现总次数

	WordNode() : articalNum(0), occur(0) {}
};

#endif