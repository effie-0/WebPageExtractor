//////////////////////////////////
//CharString.h
//
//author:杨璧菲2015013217
//////////////////////////////////
//该部分实现了字符串的数据结构
//实现的基本操作为：
//1.indexOf			查找子串的位置
//2.substring		截取字符串
//3.concat			连接字符串
//4.assign			赋值
//////////////////////////////////

#ifndef CHARSTRING_H
#define CHARSTRING_H

typedef wchar_t ElemType;

class CharString
{
private:
	//求该串作为模式串的next函数值并且存入数组next中
	void getNext();
public:
	static const int M_OVERFLOW = -2;
	ElemType* data;//存储区，按照串的实用长度进行分配，否则为nullptr
	int *next;//用于模式匹配的特征数据域
	int length;//串长度

	//构造一个内容与传入的字符串数组一样的字符串
	CharString(const ElemType *str);
	//拷贝构造函数
	CharString(const CharString& str);
	CharString();
	~CharString();

	//查找子串的位置，实现KMP算法，第一个参数是待匹配的子串
	//第二个参数是主串开始匹配的位置，默认从0开始编号，如果找子串不匹配，返回-1
	int indexOf(const CharString& subStr, int pos);
	//substring截取字符串，返回的是从off开始长度为count的子串，默认off跟count都是0
	CharString substring(int off = 0, int count = 0);
	//连接字符串，参数是需要接到后面的字符串，返回值就是连接后的字符串（原有字符串不改变）
	CharString concat(const CharString& otherStr);
	//连接字符串，参数是ElemType*，返回值就是连接之后的字符串（原有字符串改变为增加长度的字符串）
	CharString concat(const ElemType* str);
	//赋值，参数类型为ElemType*
	void assign(const ElemType *str);
	//重载赋值函数，参数类型是const CharString&
	void assign(const CharString& str);
	//去掉字符串最后的一个字符，如果字符串内容长度<=1，返回false
	bool trim();
	// = 运算符重载
	CharString& operator = (const CharString& str);

	// == 运算符重载
	bool operator == (const CharString& str);
	// > 运算符重载
	bool operator>(const CharString& str);
	// < 运算符重载
	bool operator<(const CharString& str);
	//判断两个字符串是否相等
	bool equalsTo(const CharString& otherStr);
};

extern bool operator<(const CharString& str1, const CharString& str2);
#endif