//
//Stack.cpp
//
//author:��起�2015013217
//
//ʵ����ջStack�����ݽṹ

#include "Stack.h"
#include <iostream>

template <typename T>
Stack<T>::Stack(int length)
{
	//����һ������Ϊlength�Ŀ�ջ
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
	//ѹջ
	if(Top - Base >= Size)//ջ��
		return M_OVERFLOW;

	(*Top) = data;
	Top++;
	return OK;
}

template <typename T>
Status Stack<T>::pop(T& data)
{
	//��ջ
	if(Top == Base)
		return ERROR;

	Top--;
	data =  *Top;
	return OK;
}

template <typename T>
Status Stack<T>::top(T& data)
{
	//��ȡջ��Ԫ��
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
	//�ж�ջ�Ƿ�Ϊ��
	if(Top == Base)
		return true;
	else
		return false;
}