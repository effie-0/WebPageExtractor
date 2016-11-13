//////////////////////
//
//Stringbuff.h
//
//author:��起�2015013217
///////////////////////
//�ַ�����������
//just for coding convenience
///////////////////////

#ifndef STRINGBUFF_H
#define STRINGBUFF_H

typedef wchar_t ElemType;

class Stringbuff
{
private:
	static const int MAX_INIT_SIZE = 50;
	static const int APPEND_SIZE = 25;

public:
	ElemType *data;
	int capacity;//����
	int current;//��ǰָ��

	Stringbuff();
	~Stringbuff();

	//��û������������ַ�
	void append(ElemType element);
	//���󻺳�������
	void enlarge();
	//��ջ�������ע���������ܸı�
	void clear();
};

#endif