//////////////////////////////////////////////
//Query.h
//
//author:杨璧菲2015013217
//////////////////////////////////////////////
//该部分处理了查询操作
//////////////////////////////////////////////

#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <string>
#include "AVLTree.h"
#include "WordNode.h"
#include "CharString.h"
using namespace std;

extern void query(AVLTree<WordNode, CharString>& tree, string filename, string outName);

#endif