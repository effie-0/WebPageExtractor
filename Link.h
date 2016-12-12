//////////////////////////////////////////////
//Link.h
//
//author:��起�2015013217
//////////////////////////////////////////////
//�ò���ʵ��������ģ����
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
	Node<T>* head;//ͷָ��
	Node<T>* current;//��ǰָ��
	Node<T>* tail;//βָ��

public:
	int currentPos;//��ǰָ���Ӧ��λ��
	int length;//����

	Link() : head(nullptr), current(nullptr), tail(nullptr), currentPos(0), length(0) {}
	Link(const Link<T> & otherLink);
	~Link();

	//��posλ��֮ǰ���Ԫ�أ��µ�Ԫ�س�Ϊ��pos��Ԫ�أ���0��ʼ���
	bool add(const T& element, int pos);
	//��β�ڵ�֮�������Ԫ�أ�ʹ��Ԫ�س�Ϊβ�ڵ�
	bool append(const T& element);
	//ɾ����pos��Ԫ�أ���������ֵ������ĳ��ȼ�һ
	//��һ��������λ�ã��ڶ��������Ƿ��ص�Ԫ������
	bool remove(int pos, T& element);
	//����ĳԪ��λ�ã����û���ҵ�������-1
	int search(const T& element);

	void printLink();

	//����=�����
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
	//��posλ��֮ǰ���Ԫ�أ��µ�Ԫ�س�Ϊ��pos��Ԫ�أ���0��ʼ���
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
	//�ı䵱ǰָ��ָ���pos���ڵ㣬pos == 0ʱָ��ͷ���
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
	//ɾ����pos��Ԫ�أ���������ֵ������ĳ��ȼ�һ����һ��������λ�ã��ڶ��������Ƿ��ص�Ԫ������
	if(pos < 0 || pos >= length)
		return false;

	bool result = true;
	Node<T>* q;//���ڷ��ص�ָ��
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
	//�������캯��
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