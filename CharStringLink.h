//////////////////////////////////
//CharStringLink.h
//
//author:��起�2015013217
//////////////////////////////////
//�ò���ʵ�����ַ��������ݽṹ
//ʵ�ֵĻ�������Ϊ��
//1.add			���Ԫ��
//2.remove		ɾ��Ԫ��
//3.search		����ĳԪ��λ��
//////////////////////////////////

#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H
#include "CharString.h"
#include <string>
#include <iostream>
using namespace std;

typedef struct CharStringNode//�ַ����ڵ�
{
	CharString data;
	struct CharStringNode *next;
}CharStringNode, *CharStringList;
typedef int Status;

class CharStringLink
{
private:
	//�ı䵱ǰָ��ָ���pos���ڵ㣬pos == 0ʱָ��ͷ���
	Status locatePos(int pos);

public:
	CharStringList head;//�ַ��������ͷָ��
	CharStringList tail;//βָ��
	CharStringList current;//��ǰ�ڵ�
	int currentPos;//��ǰ�ڵ��Ӧ��λ��
	int length;//����ĳ���

	//��ʼ��������һ��������
	CharStringLink();
	~CharStringLink();

	//�������״̬
	static const int M_OVERFLOW = -2;
	static const int TRUE = 1;
	static const int FALSE = 0;
	static const int ERROR = 0;
	static const int OK = 1;

	//��posλ��֮ǰ���Ԫ�أ��µ�Ԫ�س�Ϊ��pos��Ԫ�أ���0��ʼ���
	Status add(const CharString& element, int pos);
	//��β�ڵ�֮�������Ԫ�أ�ʹ��Ԫ�س�Ϊβ�ڵ�
	Status append(const CharString& element);
	//ɾ����pos��Ԫ�أ���������ֵ������ĳ��ȼ�һ
	//��һ��������λ�ã��ڶ��������Ƿ��ص�Ԫ������
	Status remove(int pos, CharString& element);
	//����ĳԪ��λ�ã����û���ҵ�������-1
	int search(CharString& element);
	//����������ݵ��ļ�
	void printLink(string fileName);
};

#endif
