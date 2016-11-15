//////////////////////////////////
//CharStringLink.h
//
//author:杨璧菲2015013217
//////////////////////////////////
//该部分实现了字符串的数据结构
//实现的基本操作为：
//1.add			添加元素
//2.remove		删除元素
//3.search		查找某元素位置
//////////////////////////////////

#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H
#include "CharString.h"
#include <string>
#include <iostream>
using namespace std;

typedef struct CharStringNode//字符串节点
{
	CharString data;
	struct CharStringNode *next;
}CharStringNode, *CharStringList;
typedef int Status;

class CharStringLink
{
private:
	//改变当前指针指向第pos个节点，pos == 0时指向头结点
	Status locatePos(int pos);

public:
	CharStringList head;//字符串链表的头指针
	CharStringList tail;//尾指针
	CharStringList current;//当前节点
	int currentPos;//当前节点对应的位置
	int length;//链表的长度

	//初始化，构造一条空链表
	CharStringLink();
	~CharStringLink();

	//函数结果状态
	static const int M_OVERFLOW = -2;
	static const int TRUE = 1;
	static const int FALSE = 0;
	static const int ERROR = 0;
	static const int OK = 1;

	//在pos位置之前添加元素，新的元素成为第pos个元素，从0开始编号
	Status add(const CharString& element, int pos);
	//在尾节点之后添加新元素，使新元素成为尾节点
	Status append(const CharString& element);
	//删除第pos个元素，并返回其值，链表的长度减一
	//第一个参数是位置，第二个参数是返回的元素内容
	Status remove(int pos, CharString& element);
	//查找某元素位置，如果没有找到，返回-1
	int search(CharString& element);
	//输出链表内容到文件
	void printLink(string fileName);
};

#endif
