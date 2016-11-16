//////////////////////
//
//Stringbuff.h
//
//author:杨璧菲2015013217
///////////////////////
//字符串缓冲区类
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
	int capacity;//容量
	int current;//当前指针

	Stringbuff();
	//拷贝构造函数
	Stringbuff(const Stringbuff& otherBuff);
	~Stringbuff();

	//向该缓冲区增添新字符
	void append(ElemType element);
	//扩大缓冲区容量
	void enlarge();
	//清空缓冲区，注意容量不能改变
	void clear();

	//重载=运算符
	Stringbuff& operator=(const Stringbuff& otherBuff);
};

#endif