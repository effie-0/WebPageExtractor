//
//CharString.cpp
//
//author:杨璧菲2015013217
//
//实现了字符串CharString的数据结构

#include "CharString.h"
#include <iostream>

CharString::CharString(const ElemType*str)
{
	int i = 0;
	length = 0;
	if(str != nullptr)
	{
		while(str[i] != '\0')
		{
			length++;
			i++;
		}
	}

	if(length != 0)
	{
		data = new ElemType[length + 1];//特别注意，每次对data分配的内存空间都是长度+1，用于存放'\0'
		next = new int[length + 1];//just for safety
		next[length] = -2;
		if(!data || !next)
			exit(M_OVERFLOW);
		for(i = 0; i < length; i++)
		{
			data[i] = str[i];
		}
		data[length] = '\0';
		getNext();
	}
}

CharString::CharString(const CharString& str)
{
	//拷贝构造函数
	length = str.length;

	if(length > 0)
	{
		data = new ElemType[length + 1];
		next = new int[length + 1];
		next[length] = -2;
		if(!data || !next)
			exit(M_OVERFLOW);
		int i;
		for(i = 0; i <= length; i++)
		{
			data[i] = str.data[i];
			if(i != length)
				next[i] = str.next[i];
		}
		data[length] = '\0';
	}
	else
	{
		data = nullptr;
		next = nullptr;
	}
}

CharString::CharString()
{
	//below part is written just for safety reason
	data = nullptr;
	next = nullptr;
	length = 0;
}

CharString::~CharString()
{
	//std::cout << data << std::endl;
	if(length > 0)
	{
		if(data)
		{
			if(data[0] != '\0' && data[0] != L'\0')
			{
				//std::cout << data << std::endl;
				delete[] data;
			}
		}
		if(next)
			delete[] next;
	}
	length = 0;
	data = nullptr;
	next = nullptr;
}

void CharString::getNext()
{
	if(next == nullptr || length == 0)
		return;

	int j = 0;
	next[0] = -1;
	int k = -1;
	while(j < length)
	{
		if(k == -1)
		{
			j++;
			k++;
			next[j] = k;
		}
		else if(data[j] == data[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	};

	for(j = 1; j < length; j++)//对失效函数进行修正
	{
		k = next[j];
		if(data[j] == data[k])
			next[j] = next[k];
	}
}

int CharString::indexOf(const CharString& subStr, int pos)
{
	if(pos < 0 || pos >= length)
		return -1;

	int i = pos;
	int j = 0;
	while(i < this->length && j < subStr.length && data[i] != '\0')
	{
		if(j == -1 || data[i] == subStr.data[j])
		{
			//继续比较后继字符
			i++;
			j++;
		}
		else
		{
			j = subStr.next[j];//模式串移动，i不变
		}
	}

	if(j >= subStr.length)
		return i - subStr.length;
	else return -1;
}

CharString CharString::substring(int off, int count)
{
	CharString subStr;
	if(off >= length || off < 0)
	{
		subStr.data = nullptr;
		subStr.next = nullptr;
		subStr.length = 0;
	}
	else
	{
		//如果所求数据的长度超过主串长度，并且起始位置合法，就进行相应截断
		subStr.length = (count <= (length - off)) ? count : (length - off);
		subStr.data = new ElemType[subStr.length + 1];
		subStr.next = new int[subStr.length + 1];
		//subStr.next[subStr.length] = -2;
		if(!subStr.data || !subStr.next)
			exit(M_OVERFLOW);
		int i, j;
		for(i = 0; i < subStr.length; i++)
		{
			j = off + i;
			subStr.data[i] = data[j];
		}
		subStr.data[subStr.length] = '\0';
		subStr.getNext();
	}

	return subStr;
}

CharString& CharString::concat(const CharString& otherStr)
{
	CharString longStr;//新建的返回字符串
	longStr.length = length + otherStr.length;
	longStr.data = new ElemType[longStr.length + 1];
	longStr.next = new int[longStr.length + 1];
	longStr.next[length] = -2;

	if(!longStr.data || !longStr.next)
		exit(M_OVERFLOW);

	int i, j = 0;
	for(i = 0; i < length; i++)
	{
		longStr.data[i] = data[i];
	}
	for(i = length; i < longStr.length; i++)
	{
		longStr.data[i] = otherStr.data[j];
		j++;
	}
	longStr.data[longStr.length] = '\0';
	longStr.getNext();
	(*this) = longStr;
	return *this;
}

CharString& CharString::concat(const ElemType* str)
{
	int i = 0;
	int addLength = 0;
	if(str != nullptr)
	{
		while(str[i] != '\0')
		{
			i++;
		}
		addLength = i;

		ElemType *newData = new ElemType[length + addLength + 1];
		int *newNext = new int[length + addLength + 1];
		for(i = 0; i < length; i++)
		{
			newData[i] = data[i];
		}
		for(i = 0; i < addLength; i++)
		{
			newData[length + i] = str[i];
		}
		length += addLength;
		newData[length] = '\0';
		delete[] data;
		data = newData;
		next = newNext;
		getNext();
	}

	return *this;
}

void CharString::assign(const ElemType *str)
{
	if(length > 0)
	{
		if(data)
		{
			if(data[0] != '\0' && data[0] != L'\0')
				delete[] data;
		}
		//if(next)
			//delete[] next;
	}

	int i = 0;
	length = 0;
	data = nullptr;
	next = nullptr;
	if(str != nullptr)
	{
		while(str[i] != '\0' && str[i] != L'\0')
		{
			length++;
			i++;
		}
	}

	if(length > 0)
	{
		data = new ElemType[length + 1];//每次对data分配的内存空间都是长度+1，用于存放'\0'
		next = new int[length + 1];
		next[length] = -2;
		if(!data || !next)
			exit(M_OVERFLOW);

		for(i = 0; i <= length; i++)
		{
			data[i] = str[i];
		}
		data[length] = '\0';
		getNext();
	}
}

void CharString::assign(const CharString& str)
{
	if(length > 0)
	{
		if(data)
			delete[] data;
		if(next)
			delete[] next;
	}
	length = str.length;
	data = nullptr;
	next = nullptr;

	if(length > 0)
	{
		data = new ElemType[length + 1];
		next = new int[length + 1];
		next[length] = -2;
		if(!data || !next)
			exit(M_OVERFLOW);

		int i;
		for(i = 0; i <= length; i++)
		{
			data[i] = str.data[i];
			if(i != length)
				next[i] = str.next[i];
		}
		data[length] = '\0';
	}
}

CharString& CharString::operator=(const CharString &str)
{
	if(length > 0)
	{
		if(data)
		{
			if(length > 1)
				delete[] data;
		}
		if(next)
			delete[] next;
	}
	length = str.length;
	data = nullptr;

	if(length > 0)
	{
		data = new ElemType[length + 1];
		next = new int[length + 1];
		next[length] = -2;
		int i;
		for(i = 0; i <= length; i++)
		{
			data[i] = str.data[i];
			if(i != length)
				next[i] = str.next[i];
		}
		data[length] = '\0';
	}
	else
	{
		data = nullptr;
		next = nullptr;
	}
	return *this;
}

bool CharString::equalsTo(const CharString& otherStr)
{
	bool result = true;
	if(otherStr.length != length)
		result = false;
	else
	{
		int i;
		for(i = 0; i < length; i++)
		{
			if(data[i] != otherStr.data[i])
			{
				result = false;
				break;
			}
		}
	}

	return result;
}

bool CharString::trim()
{
	if(length <= 1)
		return false;

	data[length - 1] = '\0';
	length--;
	next[length] = -2;//失效
	return true;
}

bool operator<(const CharString& str1, const CharString& str2)
{
	bool result = false;
	if(str1.length > 0 && str2.length > 0 && str1.data != nullptr && str2.data != nullptr)
	{
		int i;
		int min_length = (str1.length > str2.length) ? str2.length : str1.length;
		for(i = 0; i < min_length; i++)
		{
			if(str1.data[i] < str2.data[i])
			{
				result = true;
				break;
			}
			else if(str1.data[i] > str2.data[i])
			{
				result = false;
				break;
			}
		}

		if(i >= min_length)
		{
			if(str1.length < str2.length)
				result = true;
			else if(str1.length >= str2.length)
				result = false;
		}
	}
	else if(str2.length == 0)
	{
		result = false;
	}
	else if(str1.length == 0)
	{
		result = true;
	}

	return result;
}

bool CharString::operator==(const CharString& otherStr) const
{
	bool result = true;
	if(otherStr.length != length)
		result = false;
	else
	{
		int i;
		for(i = 0; i < length; i++)
		{
			if(data[i] != otherStr.data[i])
			{
				result = false;
				break;
			}
		}
	}

	return result;
}