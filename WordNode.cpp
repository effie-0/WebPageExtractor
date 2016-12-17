//
//WordNode.cpp
//
//author:杨璧菲2015013217
//
//实现了单词节点类WordNode以及文档节点类DocNode

#include "WordNode.h"

void DocNode::addTimes()
{
	times++;
	mergeTimes++;
}

void DocNode::addMergeTimes(const DocNode& other)
{
	termSum++;
	mergeTimes += other.mergeTimes;
}

bool DocNode::IDisEqual(const DocNode & other)
{
	bool result = false;
	if(other.docID == docID)
		result = true;

	return result;
}

bool DocNode::IDisEqual(int DocNum)
{
	bool result = false;
	if(DocNum == docID)
		result = true;

	return result;
}

DocNode& DocNode::operator=(const DocNode& other)
{
	docID = other.docID;
	times = other.times;
	termSum = other.termSum;
	mergeTimes = other.mergeTimes;
	return *this;
}

void DocNode::printContent(std::wostream &fout)
{
	if(times != 0)
	{
		fout << "(" << docID << "," << mergeTimes << ")" << std::flush;
	}
}

void WordNode::addArtical(int DocNum)
{
	if(m_link.empty())
	{
		DocNode newDoc(DocNum);
		m_link.append(newDoc);
		articalNum++;
	}
	else
	{
		if((m_link.current->data).IDisEqual(DocNum))
		{
			m_link.current->data.addTimes();
		}
		else
		{
			DocNode newDoc(DocNum);
			m_link.append(newDoc);
			articalNum++;
		}
	}
	occurTimes++;
}

void mergeOutcome(Link<WordNode> &wordLink, std::wostream &fout)
{
	int i, j;

	Link<DocNode> docLink;//文档链表
	for(i = 0; i < wordLink.length; i++)
	{
		wordLink.locatePos(i);
		auto iter1 = wordLink.current;//当前关键字指针
		for(j = 0; j < iter1->data.m_link.length; j++)
		{
			iter1->data.m_link.locatePos(j);
			auto iter2 = iter1->data.m_link.current;
			int result = docLink.search(iter2->data);
			if(result != -1)
			{
				docLink.locatePos(result);
				docLink.current->data.addMergeTimes(iter2->data);
			}
			else
			{
				docLink.append(iter2->data);
			}
		}
	}

	//按照单词种类进行排序
	for(i = 0; i < docLink.length - 1; i++)
	{
		for(j = docLink.length - 1; j > i; j--)
		{
			docLink.locatePos(j - 1);
			auto it = docLink.current;
			if(it->data.termSum < it->next->data.termSum)
			{
				bool result = docLink.locatePos(j - 2);
				if(result)
				{
					docLink.current->next = it->next;
					auto temp = it->next;
					it->next = temp->next;
					temp->next = it;
					if(temp == docLink.tail)
						docLink.tail = it;
				}
				else
				{
					if(it == docLink.head)
					{
						auto temp = it->next;
						docLink.head = temp;
						it->next = temp->next;
						temp->next = it;
						if(temp == docLink.tail)
							docLink.tail = it;
					}
				}
			}
		}
	}

	//输出结果
	for(i = 0; i < docLink.length; i++)
	{
		docLink.locatePos(i);
		docLink.current->data.printContent(fout);
		if(i < docLink.length - 1)
		{
			fout << " " << std::flush;
		}
		else
		{
			fout << "\n" << std::flush;
		}
	}
}

WordNode& WordNode::operator=(const WordNode& other)
{
	term = other.term;
	termID = other.termID;
	articalNum = other.articalNum;
	occurTimes = other.occurTimes;
	m_link = other.m_link;
	return *this;
}

bool WordNode::operator==(const WordNode& other) const
{
	if(term == other.term)
		return true;
	else
		return false;
}

bool DocNode::operator==(const DocNode& other)const
{
	if(docID == other.docID)
		return true;
	else
		return false;
}