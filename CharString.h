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

class CharString
{
private:
	//��ô���Ϊģʽ����next����ֵ���Ҵ�������next��
	void getNext();
public:
	static const int M_OVERFLOW = -2;
	char *data;//�洢�������մ���ʵ�ó��Ƚ��з��䣬����Ϊnullptr
	int *next;//����ģʽƥ�������������
	int length;//������

	//����һ�������봫����ַ�������һ�����ַ���
	CharString(const char *str);
	//�������캯��
	CharString(const CharString& str);
	CharString();
	~CharString();

	//�����Ӵ���λ�ã�ʵ��KMP�㷨����һ�������Ǵ�ƥ����Ӵ�
	//�ڶ���������������ʼƥ���λ�ã�Ĭ�ϴ�0��ʼ��ţ�������Ӵ���ƥ�䣬����-1
	int indexOf(const CharString& subStr, int pos);
	//substring��ȡ�ַ��������ص��Ǵ�off��ʼ����Ϊcount���Ӵ���Ĭ��off��count����0
	CharString substring(int off = 0, int count = 0);
	//�����ַ�������������Ҫ�ӵ�������ַ���������ֵ�������Ӻ���ַ���
	CharString concat(const CharString& otherStr);
	//��ֵ����������Ϊchar*
	void assign(const char *str);
	//���ظ�ֵ����������������const CharString&
	void assign(const CharString& str);
	// = ���������
	CharString& operator = (const CharString& str);

	//�����ӵĺ������ж������ַ����Ƿ����
	bool equalsTo(const CharString& otherStr);
};

#endif