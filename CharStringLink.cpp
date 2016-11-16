//
//CharStringLink.cpp
//
//author:杨璧菲2015013217
//
//实现了字符串链表CharStringLink的数据结构

#include "CharStringLink.h"
#include <fstream>
#include <locale>
#include <codecvt>

CharStringLink::CharStringLink()
{
	head = nullptr;
	tail = head;
	current = head;
	currentPos = 0;
	length = 0;
}

CharStringLink::~CharStringLink()
{
	if(head)
	{
		while(head->next)
		{
			current = head->next;
			head->next = current->next;
			current->next = nullptr;
			delete current;
		}

		delete head;
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		length = 0;
		currentPos = 0;
	}
}

Status CharStringLink::add(const CharString& element, int pos)
{
	//在pos位置之前添加元素，新的元素成为第pos个元素，从0开始编号
	Status outcome = OK;
	if(pos != 0)
	{
		outcome = locatePos(pos - 1);
	
		if(outcome != ERROR && outcome != M_OVERFLOW && current != nullptr)
		{
			CharStringList p = new CharStringNode;
			if(!p)
				exit(M_OVERFLOW);
			p->data.assign(element);
			p->next = current->next;
			current->next = p;
			if(tail == current)
				tail = p;
			current = p;
			currentPos = pos;
			length++;
		}
	}
	else
	{
		current = head;
		head = new CharStringNode;
		if(!head)
			exit(M_OVERFLOW);
		head->data.assign(element);
		head->next = current;
		if(tail == nullptr)
			tail = head;
		current = head;
		currentPos = 0;
		length++;
	}

	return outcome;
}

Status CharStringLink::locatePos(int pos)
{
	//改变当前指针指向第pos个节点，pos == 0时指向头结点
	Status result = OK;
	int i;

	if(currentPos != pos && head != nullptr)
	{
		if(pos < 0 || pos >= length)
			result = ERROR;
		else if(pos == 0)
		{
			current = head;
		}
		else if(pos == length - 1)
		{
			current = tail;
		}
		else if(pos < currentPos)
		{
			current = head;
			for(i = 0; i < pos; i++)
			{
				current = current->next;
			}
		}
		else if(pos > currentPos)
		{
			for(i = currentPos; i < pos; i++)
			{
				current = current->next;
			}
		}

		if(result != ERROR)
			currentPos = pos;
	}
	else if(head == nullptr)
	{
		current = head;
		currentPos = 0;
	}

	return result;
}

Status CharStringLink::remove(int pos, CharString& element)
{
	//删除第pos个元素，并返回其值，链表的长度减一，第一个参数是位置，第二个参数是返回的元素内容
	if(pos < 0 || pos >= length)
		return M_OVERFLOW;

	Status result = OK;
	CharStringList q;//用于返回的指针
	if(pos != 0)
	{
		result = locatePos(pos - 1);
		q = current->next;
		current->next = q->next;

		if(tail == q)
			tail = current;
		element = q->data;
		q->next = nullptr;
		delete q;
		length--;
	}
	else
	{
		current = head->next;
		if(tail == head)
			tail = nullptr;

		element = head->data;
		delete head;
		head = current;
		currentPos = 0;
		length--;
	}
	return result;
}

int CharStringLink::search(CharString& element)
{
	CharStringList p = head;
	int result = -1;
	int i;
	for(i = 0; i < length; i++)
	{
		if(element.equalsTo(p->data))
		{
			result = i;
			break;
		}
		p = p->next;
	}
	return result;
}


Status CharStringLink::append(const CharString& element)
{
	Status outcome;
	if(this->length == 0)
	{
		outcome = this->add(element, 0);
	}
	else
	{
		outcome = this->add(element, length - 1);
	}
	return outcome;
}

void CharStringLink::printLink(string fileName)
{
	ofstream outFile(fileName);
	wbuffer_convert<codecvt_utf8<wchar_t>> conv(outFile.rdbuf());
	wostream fout(&conv);

	int i;
	for(i = 0; i <length; i++)
	{
		locatePos(i);
		if(current->data.data != nullptr)
			fout << current->data.data << endl;
	}
	outFile.close();
}

CharStringLink::CharStringLink(const CharStringLink& otherLink)
{
	//拷贝构造函数
	head = nullptr;
	tail = head;
	current = head;
	currentPos = 0;
	length = 0;

	CharStringList p = otherLink.head;
	while(p != nullptr)
	{
		this->append(p->data);
		p = p->next;
	};
}

CharStringLink& CharStringLink::operator=(const CharStringLink& otherLink)
{
	if(head)
	{
		while(head->next)
		{
			current = head->next;
			head->next = current->next;
			current->next = nullptr;
			delete current;
		}

		delete head;
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		length = 0;
		currentPos = 0;
	}

	CharStringList p = otherLink.head;
	while(p != nullptr)
	{
		this->append(p->data);
		p = p->next;
	};

	return *this;
}