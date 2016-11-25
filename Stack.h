//////////////////////////////
//Stack.h
//
//author:杨璧菲2015013217
//////////////////////////////
//该部分实现了栈的数据结构
//实现的基本操作为：
//1.push		压栈
//2.pop			退栈
//3.top			获取栈顶元素
//4.empty		判断栈是否为空
//////////////////////////////

#ifndef STACK_H
#define STACK_H

typedef int Status;

template <typename T>
class Stack
{
private:
	T* Base;//栈底
	T* Top;//栈顶
	int Size;//栈的长度

public:
	T* Current;//栈顶元素
	//栈的构造函数，用于初始化数据域
	Stack(int length);
	//重载，默认长度为0
	Stack();
	//拷贝构造函数
	Stack(const Stack& otherStack);
	~Stack();

	//函数结果状态
	static const int M_OVERFLOW = -2;
	static const int TRUE = 1;
	static const int FALSE = 0;
	static const int ERROR = 0;
	static const int OK = 1;

	//压栈
	Status push(T data);
	//退栈
	Status pop(T& data);
	Status pop();
	//获取栈顶元素
	Status top(T& data);
	//判断栈是否为空
	bool empty();
	//判断栈是否还有一个元素
	bool One();

	//重载=运算符
	Stack& operator=(const Stack& otherStack);
};

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

template<typename T>
Stack<T>::Stack(const Stack<T>& otherStack)
{
	Size = otherStack.Size;
	Base = new T[Size];
	if(!Base)
		exit(M_OVERFLOW);
	Top = Base;

	T* p = otherStack.Base;
	while(p != otherStack.Top)
	{
		this->push(*p);
		p++;
	};
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& otherStack)
{
	if(Base != nullptr)
	{
		Top = nullptr;
		Current = nullptr;
		Size = 0;
		delete[] Base;
	}

	Size = otherStack.Size;
	Base = new T[Size];
	if(!Base)
		exit(M_OVERFLOW);
	Top = Base;

	T* p = otherStack.Base;
	while(p != otherStack.Top)
	{
		this->push(*p);
		p++;
	};
}

template <typename T>
Stack<T>::~Stack()
{
	if(Base != nullptr)
	{
		Top = nullptr;
		Current = nullptr;
		Size = 0;
		delete[] Base;
		Base = nullptr;
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
	Current = Top - 1;
	return OK;
}

template <typename T>
Status Stack<T>::pop(T& data)
{
	//退栈
	if(Top == Base)
		return ERROR;

	Top--;
	data = (*Top);
	//delete Top;
	//Top = new T;
	Current = Top - 1;
	return OK;
}

template<typename T>
Status Stack<T>::pop()
{
	//退栈
	if(Top == Base)
		return ERROR;

	Top--;
	Current = Top - 1;
	return OK;
}

template <typename T>
Status Stack<T>::top(T& data)
{
	//获取栈顶元素
	if(Top == Base)
		return ERROR;

	Top--;
	data = *Top;
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
template<typename T>
bool Stack<T>::One()
{
	if(Current == Base)
		return true;
	else
		return false;
}
#endif