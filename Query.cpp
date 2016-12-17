//
//Query.h
//
//author:杨璧菲2015013217
//
//实现了查询函数
#include "Query.h"
#include "Stringbuff.h"
#include <fstream>
#include <locale>
#include <codecvt>
using namespace std;

void query(AVLTree<WordNode, CharString>& tree, string filename, string outName)
{
	//参考了群主@孙子平 的三行输入输出代码
	ifstream infile(filename);
	wbuffer_convert<codecvt_utf8<wchar_t>> conv(infile.rdbuf());
	wistream fin(&conv);

	ofstream outFile(outName);
	wbuffer_convert<codecvt_utf8<wchar_t>> converter(outFile.rdbuf());
	wostream fout(&converter);

	while(!fin.eof())
	{
		Link<WordNode> wordLink; 
		ElemType* str = new ElemType[200];
		fin.getline(str, 200, L'\n');
		Stringbuff buff;
		CharString chStr;
		buff.clear();
		int i = 0;
		while(str[i] != '\0' && str[i] != '\n' && str[i] != L'\0' && str[i] != L'\n')
		{
			if(str[i] != L' ')
			{
				buff.append(str[i]);
			}
			else
			{
				buff.append('\0');
				chStr.assign(buff.data);
				buff.clear();
				BiNode<WordNode, CharString>* address = nullptr;
				if(tree.search(chStr, address))
				{
					wordLink.append(address->data);
				}
				else
				{
					cout << "error! can't find the node" << endl;
				}
			}
			i++;
		};

		if(buff.current != 0)
		{
			buff.append('\0');
			chStr.assign(buff.data);
			buff.clear();
			BiNode<WordNode, CharString>* address = nullptr;
			if(tree.search(chStr, address))
			{
				wordLink.append(address->data);
			}
			else
			{
				cout << "error! can't find the node" << endl;
			}
		} 

	mergeOutcome(wordLink, fout);
	};

	infile.close();
	outFile.close();
}