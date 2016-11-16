//
//Stringbuff.cpp
//
//author:杨璧菲2015013217
//
//实现了字符串缓冲区Stringbuff类

#include "Stringbuff.h"
#include <iostream>

Stringbuff::Stringbuff()
{
	capacity = MAX_INIT_SIZE;
	data = (ElemType *)malloc(MAX_INIT_SIZE * sizeof(ElemType));
	data[0] = '\0';
	current = 0;
}

Stringbuff::~Stringbuff()
{
	if(data)
		free(data);
	data = nullptr;
	current = 0;
	capacity = 0;
}

Stringbuff::Stringbuff(const Stringbuff& otherBuff)
{
	data = (ElemType *)malloc(otherBuff.capacity * sizeof(ElemType));
	capacity = otherBuff.capacity;
	current = 0;
	while(otherBuff.data[current] != '\0' && otherBuff.data[current] != L'\0')
	{
		data[current] = otherBuff.data[current];
	};
	data[current] = '\0';
}

void Stringbuff::append(ElemType element)
{
	data[current] = element;
	current++;
	data[current] = '\0';
	if(current >= capacity -1)
		enlarge();
}

void Stringbuff::enlarge()
{
	capacity += APPEND_SIZE;
	data = (ElemType *)realloc(data, capacity * sizeof(ElemType));
}

void Stringbuff::clear()
{
	int i;
	for(i = 0; i < current; i++)
	{
		data[i] = '\0';
	}
	current = 0;
}

Stringbuff& Stringbuff::operator=(const Stringbuff& otherBuff)
{
	if(data)
		free(data);

	capacity = otherBuff.capacity;
	data = (ElemType *)malloc(otherBuff.capacity * sizeof(ElemType));
	current = 0;
	while(otherBuff.data[current] != '\0' && otherBuff.data[current] != L'\0')
	{
		data[current] = otherBuff.data[current];
	};
	data[current] = '\0';

	return *this;
}