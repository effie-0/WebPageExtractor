//////////////////////////////
//Stack.h
//
//author:��起�2015013217
//////////////////////////////
//�ò���ʵ����ջ�����ݽṹ
//ʵ�ֵĻ�������Ϊ��
//1.push		ѹջ
//2.pop			��ջ
//3.top			��ȡջ��Ԫ��
//4.empty		�ж�ջ�Ƿ�Ϊ��
//////////////////////////////

#ifndef STACK_H
#define STACK_H

typedef int Status;

template <typename T>
class Stack
{
private:
	T* Base;//ջ��
	T* Top;//ջ��
	int Size;//ջ�ĳ���

public:
	T* Current;//ջ��Ԫ��
	//ջ�Ĺ��캯�������ڳ�ʼ��������
	Stack(int length);
	//���أ�Ĭ�ϳ���Ϊ0
	Stack();
	~Stack();

	//�������״̬
	static const int M_OVERFLOW = -2;
	static const int TRUE = 1;
	static const int FALSE = 0;
	static const int ERROR = 0;
	static const int OK = 1;

	//ѹջ
	Status push(T data);
	//��ջ
	Status pop(T& data);
	Status pop();
	//��ȡջ��Ԫ��
	Status top(T& data);
	//�ж�ջ�Ƿ�Ϊ��
	bool empty();
};

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
	Current = Top - 1;
	return OK;
}

template <typename T>
Status Stack<T>::pop(T& data)
{
	//��ջ
	if(Top == Base)
		return ERROR;

	Top--;
	data = (*Top);
	Current = Top - 1;
	return OK;
}

template<typename T>
Status Stack<T>::pop()
{
	//��ջ
	if(Top == Base)
		return ERROR;

	Top--;
	Current = Top - 1;
	return OK;
}

template <typename T>
Status Stack<T>::top(T& data)
{
	//��ȡջ��Ԫ��
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
	//�ж�ջ�Ƿ�Ϊ��
	if(Top == Base)
		return true;
	else
		return false;
}

#endif