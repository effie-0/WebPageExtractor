/////////////////////////////////////
//AVLTree.h
//
//author:��起�2015013217
/////////////////////////////////////
//�ò���ʵ����ƽ������������ݽṹ��ģ���ࣩ
//ʵ�ֵĻ�������Ϊ��
//1.insert		��ӽڵ�
//2.search		���ҽڵ�
//3.adjust		��������ƽ����ʹ��ƽ��
//4.remove		�Ƴ�ĳ�ڵ㣨todo��
//5.edit			�༭ĳ�ڵ㣨todo��
/////////////////////////////////////
//Ϊ�˷��㣬ʵ���˶��������ڲ��ڵ���
//ûд�������캯�������Բ�Ҫ���������
/////////////////////////////////////

#ifndef AVLTREE_H
#define AVLTREE_H

template <typename T, typename keyType>
class BiNode
{
public :
	T data;//������
	keyType key;//�ؼ���
	int balanceFactor;//ƽ������
	static enum Horizon{LH, EH, RH};//��ߣ��ȸߣ��Ҹ�
	BiNode *parent, *lchild, *rchild;//˫�׽ڵ��Լ����Һ���

	BiNode() : balanceFactor(Horizon.EH), parent(nullptr), lchild(nullptr), rchild(nullptr){}
	BiNode(T d, keyType k, BiNode* p = nullptr, BiNode* l = nullptr, BiNode* r = nullptr, int bf = EH) : 
		data(d), key(k), parent(p), lchild(l), rchild(r), balanceFactor(bf){}
};

template <typename T, typename keyType>
extern void DestroyTree(BiNode<T, keyType>* tree);//��ɶ����İ�ȫ����

template <typename T, typename keyType>
class AVLTree
{
private:
	//��ƽ����ת���������Ǵ���ת�ĸ��ڵ㣬��������֮��treeָ���µĽڵ�
	void LeftBalance(BiNode<T, keyType>* &tree);
	 //��ƽ����ת����
	void RightBalance(BiNode<T, keyType>* &tree);
	//������ת����
	void R_Rotate(BiNode<T, keyType>* &tree);
	//������ת����
	void L_Rotate(BiNode<T, keyType>* &tree);
	static enum LROri{Left, Right};//����ӵĽڵ����������ϻ���������

public:
	int size;//�ڵ���Ŀ
	BiNode<T, keyType>* root;//���ڵ�
	AVLTree() : size(0), root(nullptr) {}
	~AVLTree() { if(size > 0) DestroyTree(root);  size = 0;}

	//�����µĽڵ㣬�����ڶ��������������ж����������ı���
	bool insert(const T & content, const keyType & key, bool& taller, BiNode<T, keyType>* &tree);
	bool insert(const T & content, const keyType & key);//��װ�����ڵ���
	//�����Ƿ��йؼ���Ϊkey�Ľڵ㣬����У�����true��address���ؽڵ��λ�ã����򷵻�false��address����nullptr
	bool search(BiNode<T, keyType>* tree, const keyType& key, BiNode<T, keyType>* &address);
	bool search(const keyType& key, BiNode<T, keyType>* &address);//��װ�����ڵ���
	//����������ʹ��ƽ�⣬��һ�������Ǵ����������ĸ��ڵ㣬
	//�ڶ�������Ϊ����Ľڵ�λ�����������ϻ����������ϣ�����������Ϊ�����ж����������ı�����insert�����һ��������
	void adjust(BiNode<T, keyType>* &tree, int LRtag, bool& taller);
	//todo: remove and edit
};

template <typename T, typename keyType>
void DestroyTree(BiNode<T, keyType>* tree)
{
	if(!tree)
		return;

	if(tree->lchild)
	{
		DestroyTree(tree->lchild);
		tree->lchild = nullptr;
	}

	if(tree->rchild)
	{
		DestroyTree(tree->rchild);
		tree->rchild = nullptr;
	}

	tree->parent = nullptr;
	delete tree;
	tree = nullptr;
}

template<typename T, typename keyType>
bool AVLTree<T, keyType>::insert(const T & content, const keyType & key)
{
	bool taller = false;
	bool result = insert(content, key, taller, root);
	return result;
}

template <typename T, typename keyType>
bool AVLTree<T, keyType>::insert(const T & content, const keyType & key, bool & taller, BiNode<T, keyType>* &tree)
{
	if(!tree)
	{
		tree = new BiNode<T, keyType>(content, key);
		tree->balanceFactor = BiNode<T, keyType>::EH;
		taller = true;
		size++;
	}
	else
	{
		if(key == tree->key)
		{
			taller = false;
			return false;
		}
		
		if(key < tree->key)
		{
			if(!insert(content, key, taller, tree->lchild))
				return false;
			else
			{
				if(!tree->lchild->parent)
					tree->lchild->parent = tree;
			}

			if(taller)
			{
				adjust(tree, this->Left, taller);
			}
		}
		else
		{
			if(!insert(content, key, taller, tree->rchild))
				return false;
			else
			{
				if(!tree->rchild->parent)
					tree->rchild->parent = tree;
			}

			if(taller)
			{
				adjust(tree, this->Right, taller);
			}
		}
	}
}

template <typename T, typename keyType>
void AVLTree<T, keyType>::adjust(BiNode<T, keyType>* &tree, int LRTag, bool &taller)
{
	if(LRTag == Left)
	{
		switch(tree->balanceFactor)
		{
		case tree->LH:
			LeftBalance(tree);
			taller = false;
			break;

		case tree->EH:
			tree->balanceFactor = tree->LH;
			taller = true;
			break;

		case tree->RH:
			tree->balanceFactor = tree->EH;
			taller = false;
			break;
		}
	}
	else if(LRTag == Right)
	{
		switch(tree->balanceFactor)
		{
		case tree->LH:
			tree->balanceFactor = tree->EH;
			taller = false;
			break;
		case tree->EH:
			tree->balanceFactor = tree->RH;
			taller = true;
			break;
		case tree->RH:
			RightBalance(tree);
			taller = false;
			break;
		}
	}
}

template<typename T, typename keyType>
void AVLTree<T, keyType>::R_Rotate(BiNode<T, keyType>* &tree)
{
	if(!tree)
		return;

	BiNode<T, keyType>* temp = tree->lchild;
	if(!temp)
		return;

	tree->lchild = temp->rchild;
	if(temp->rchild)
		temp->rchild->parent = tree;

	temp->parent = tree->parent;
	temp->rchild = tree;
	tree->parent = temp;
	tree = temp;
}

template<typename T, typename keyType>
void AVLTree<T, keyType>::L_Rotate(BiNode<T, keyType> *&tree)
{
	if(!tree)
		return;

	BiNode<T, keyType>* temp = tree->rchild;
	if(!temp)
		return;

	tree->rchild = temp->lchild;
	if(temp->lchild)
		temp->lchild->parent = tree;

	temp->parent = tree->parent;
	temp->lchild = tree;
	tree->parent = temp;
	tree = temp;
}

template<typename T, typename keyType>
void AVLTree<T, keyType>::LeftBalance(BiNode<T, keyType>* &tree)
{
	BiNode<T, keyType>* temp = tree->lchild;
	switch(temp->balanceFactor)
	{
	case tree->LH:
		tree->balanceFactor = tree->EH;
		temp->balanceFactor = temp->EH;
		R_Rotate(tree);
		break;

	case tree->RH:
		BiNode<T, keyType>* rtemp = temp->rchild;
		switch(rtemp->balanceFactor)
		{
		case rtemp->LH:
			tree->balanceFactor = tree->RH;
			temp->balanceFactor = temp->EH;
			break;

		case rtemp->EH:
			tree->balanceFactor = tree->EH;
			temp->balanceFactor = temp->EH;
			break;

		case rtemp->RH:
			tree->balanceFactor = tree->EH;
			temp->balanceFactor = temp->LH;
			break;
		}
		rtemp->balanceFactor = rtemp->EH;
		L_Rotate(tree->lchild);
		R_Rotate(tree);
	}
}

template<typename T, typename keyType>
void AVLTree<T, keyType>::RightBalance(BiNode<T, keyType>* &tree)
{
	BiNode<T, keyType>* temp = tree->rchild;
	switch(temp->balanceFactor)
	{
	case temp->RH:
		tree->balanceFactor = tree->EH;
		temp->balanceFactor = temp->EH;
		L_Rotate(tree);
		break;

	case temp->LH:
		BiNode<T, keyType>* ltemp = temp->lchild;
		switch(ltemp->balanceFactor)
		{
		case ltemp->LH:
			tree->balanceFactor = tree->EH;
			temp->balanceFactor = temp->RH;
			break;

		case ltemp->EH:
			tree->balanceFactor = tree->EH;
			temp->balanceFactor = temp->EH;
			break;

		case ltemp->RH:
			tree->balanceFactor = tree->LH;
			temp->balanceFactor = tree->EH;
			break;
		}
		R_Rotate(tree->rchild);
		L_Rotate(tree);
	}
}

template<typename T, typename keyType>
bool AVLTree<T, keyType>::search(BiNode<T, keyType>* tree, const keyType& key, BiNode<T, keyType>* &address)
{
	if(!tree)
	{
		address = nullptr;
		return false;
	}

	if(tree->key == key)
	{
		address = tree;
		return true;
	}
	else if(tree->key < key)
	{
		return search(tree->rchild, key, address);
	}
	else
	{
		return search(tree->lchild, key, address);
	}
}

template<typename T, typename keyType>
bool AVLTree<T, keyType>::search(const keyType& key, BiNode<T, keyType>* &address)
{
	bool result = search(root, key, address);
	return result;
}

#endif