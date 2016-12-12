//////////////////////////////////////////////
//Link.h
//
//author:杨璧菲2015013217
//////////////////////////////////////////////
//该部分实现了链表模板类
//todo: adjust the order
/////////////////////////////////////////////

#ifndef LINK_H
#define LINK_H
 
template<typename T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node() : next(nullptr) {}
};

template<typename T>
class Link
{
private:
	bool locatePos(int pos);

public:
	Node<T>* head;//头指针
	Node<T>* current;//当前指针
	Node<T>* tail;//尾指针

public:
	int currentPos;//当前指针对应的位置
	int length;//长度

	Link() : head(nullptr), current(nullptr), tail(nullptr), currentPos(0), length(0) {}
	Link(const Link<T> & otherLink);
	~Link();

	//在pos位置之前添加元素，新的元素成为第pos个元素，从0开始编号
	bool add(const T& element, int pos);
	//在尾节点之后添加新元素，使新元素成为尾节点
	bool append(const T& element);
	//删除第pos个元素，并返回其值，链表的长度减一
	//第一个参数是位置，第二个参数是返回的元素内容
	bool remove(int pos, T& element);
	//查找某元素位置，如果没有找到，返回-1
	int search(const T& element);

	void printLink();

	//重载=运算符
	Link& operator=(const Link<T>& otherLink);
};

template<typename T>
Link<T>::~Link()
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

template<typename T>
bool Link<T>::add(const T& element, int pos)
{
	//在pos位置之前添加元素，新的元素成为第pos个元素，从0开始编号
	if(pos < 0)
		return false;

	bool outcome = true;
	if(pos != 0)
	{
		outcome = locatePos(pos - 1);
	
		if(outcome && current != nullptr)
		{
			Node<T>* p = new Node<T>;
			p->data = element;
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
		head = new Node<T>;
		head->data = element;
		head->next = current;
		if(tail == nullptr)
			tail = head;
		current = head;
		currentPos = 0;
		length++;
	}

	return outcome;
}

template<typename T>
bool Link<T>::locatePos(int pos)
{
	//改变当前指针指向第pos个节点，pos == 0时指向头结点
	bool result = true;
	int i;

	if(currentPos != pos && head != nullptr)
	{
		if(pos < 0 || pos >= length)
			result = false;
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

		if(result)
			currentPos = pos;
	}
	else if(head == nullptr)
	{
		current = head;
		currentPos = 0;
	}

	return result;
}

template<typename T>
bool Link<T>::remove(int pos, T& element)
{
	//删除第pos个元素，并返回其值，链表的长度减一，第一个参数是位置，第二个参数是返回的元素内容
	if(pos < 0 || pos >= length)
		return false;

	bool result = true;
	Node<T>* q;//用于返回的指针
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

template<typename T>
int Link<T>::search(const T& element)
{
	Node<T>* p = head;
	int result = -1;
	int i;
	for(i = 0; i < length; i++)
	{
		if(element == p->data)
		{
			result = i;
			break;
		}
		p = p->next;
	}
	return result;
}

template<typename T>
bool Link<T>::append(const T& element)
{
	bool outcome;
	if(this->length == 0)
	{
		outcome = this->add(element, 0);
	}
	else
	{
		outcome = this->add(element, length);
	}
	return outcome;
}

template<typename T>
Link<T>::Link(const Link<T>& otherLink)
{
	//拷贝构造函数
	head = nullptr;
	tail = head;
	current = head;
	currentPos = 0;
	length = 0;

	Node<T>* p = otherLink.head;
	while(p != nullptr)
	{
		this->append(p->data);
		p = p->next;
	};
}

template<typename T>
Link<T>& Link<T>::operator=(const Link<T>& otherLink)
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

	Node<T>* p = otherLink.head;
	while(p != nullptr)
	{
		this->append(p->data);
		p = p->next;
	};

	return *this;
}

template<typename T>
void Link<T>::printLink()
{
	int i;
	for(i = 0; i <length; i++)
	{
		locatePos(i);
		if(current != nullptr)
			std::cout << current->data << endl;
	}
}
#endif