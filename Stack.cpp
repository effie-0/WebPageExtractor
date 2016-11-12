//
//Stack.cpp
//
//author:杨璧菲2015013217
//
//实现了栈Stack的数据结构

#include "Stack.h"
#include <iostream>

template <typename T>
Stack<T>::Stack(int length)
{
	//创造一个长度为length的空栈
	if(length <= 0)
		return;

	Base = new T[length];
	if(!Base)
		exit(M_OVERFLOW);
	Top = Base;
	Size = length;
}

template <typename T>
Stack<T>::Stack()
{
	Size = 0;
	Base = nullptr;
	Top = Base;
}

template <typename T>
Stack<T>::~Stack()
{
	if(Base != nullptr)
	{
		Top = nullptr;
		Size = 0;
		delete[] Base;
	}
}

template <typename T>
Status Stack<T>::push(T data)
{
	//压栈
	if(Top - Base >= Size)//栈满
		return M_OVERFLOW;

	(*Top) = data;
	Top++;
	return OK;
}

template <typename T>
Status Stack<T>::pop(T& data)
{
	//退栈
	if(Top == Base)
		return ERROR;

	Top--;
	data =  *Top;
	return OK;
}

template <typename T>
Status Stack<T>::top(T& data)
{
	//获取栈顶元素
	if(Top == Base)
		return ERROR;

	Top--;
	Data = *Top;
	Top++;
	return OK;
}

template <typename T>
bool Stack<T>::empty()
{
	//判断栈是否为空
	if(Top == Base)
		return true;
	else
		return false;
}