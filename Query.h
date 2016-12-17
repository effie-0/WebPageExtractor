//////////////////////////////////////////////
//Query.h
//
//author:��起�2015013217
//////////////////////////////////////////////
//�ò��ִ����˲�ѯ����
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