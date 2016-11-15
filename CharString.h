//////////////////////////////////
//CharString.h
//
//author:��起�2015013217
//////////////////////////////////
//�ò���ʵ�����ַ��������ݽṹ
//ʵ�ֵĻ�������Ϊ��
//1.indexOf			�����Ӵ���λ��
//2.substring		��ȡ�ַ���
//3.concat			�����ַ���
//4.assign			��ֵ
//////////////////////////////////

#ifndef CHARSTRING_H
#define CHARSTRING_H

typedef wchar_t ElemType;

class CharString
{
private:
	//��ô���Ϊģʽ����next����ֵ���Ҵ�������next��
	void getNext();
public:
	static const int M_OVERFLOW = -2;
	ElemType* data;//�洢�������մ���ʵ�ó��Ƚ��з��䣬����Ϊnullptr
	int *next;//����ģʽƥ�������������
	int length;//������

	//����һ�������봫����ַ�������һ�����ַ���
	CharString(const ElemType *str);
	//�������캯��
	CharString(const CharString& str);
	CharString();
	~CharString();

	//�����Ӵ���λ�ã�ʵ��KMP�㷨����һ�������Ǵ�ƥ����Ӵ�
	//�ڶ���������������ʼƥ���λ�ã�Ĭ�ϴ�0��ʼ��ţ�������Ӵ���ƥ�䣬����-1
	int indexOf(const CharString& subStr, int pos);
	//substring��ȡ�ַ��������ص��Ǵ�off��ʼ����Ϊcount���Ӵ���Ĭ��off��count����0
	CharString substring(int off = 0, int count = 0);
	//�����ַ�������������Ҫ�ӵ�������ַ���������ֵ�������Ӻ���ַ�����ԭ���ַ������ı䣩
	CharString concat(const CharString& otherStr);
	//�����ַ�����������ElemType*������ֵ��������֮����ַ�����ԭ���ַ����ı�Ϊ���ӳ��ȵ��ַ�����
	CharString concat(const ElemType* str);
	//��ֵ����������ΪElemType*
	void assign(const ElemType *str);
	//���ظ�ֵ����������������const CharString&
	void assign(const CharString& str);
	//ȥ���ַ�������һ���ַ�������ַ������ݳ���<=1������false
	bool trim();
	// = ���������
	CharString& operator = (const CharString& str);

	// == ���������
	bool operator == (const CharString& str);
	// > ���������
	bool operator>(const CharString& str);
	// < ���������
	bool operator<(const CharString& str);
	//�ж������ַ����Ƿ����
	bool equalsTo(const CharString& otherStr);
};

extern bool operator<(const CharString& str1, const CharString& str2);
#endif