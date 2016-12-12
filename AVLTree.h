/////////////////////////////////////
//AVLTree.h
//
//author:杨璧菲2015013217
/////////////////////////////////////
//该部分实现了平衡二叉树的数据结构（模板类）
//实现的基本操作为：
//1.insert		添加节点
//2.search		查找节点
//3.adjust		调整二叉平衡数使其平衡
//4.remove		移除某节点（todo）
//5.edit			编辑某节点（todo）
/////////////////////////////////////
//为了方便，实现了二叉树的内部节点类
//没写拷贝构造函数，所以不要复制这棵树
/////////////////////////////////////

#ifndef AVLTREE_H
#define AVLTREE_H

template <typename T, typename keyType>
class BiNode
{
public :
	T data;//数据域
	keyType key;//关键词
	int balanceFactor;//平衡因子
	static enum Horizon{LH, EH, RH};//左高，等高，右高
	BiNode *parent, *lchild, *rchild;//双亲节点以及左、右孩子

	BiNode() : balanceFactor(Horizon.EH), parent(nullptr), lchild(nullptr), rchild(nullptr){}
	BiNode(T d, keyType k, BiNode* p = nullptr, BiNode* l = nullptr, BiNode* r = nullptr, int bf = EH) : 
		data(d), key(k), parent(p), lchild(l), rchild(r), balanceFactor(bf){}
};

template <typename T, typename keyType>
extern void DestroyTree(BiNode<T, keyType>* tree);//完成对树的安全析构

template <typename T, typename keyType>
class AVLTree
{
private:
	//左平衡旋转处理，参数是待旋转的根节点，操作结束之后，tree指向新的节点
	void LeftBalance(BiNode<T, keyType>* &tree);
	 //右平衡旋转处理
	void RightBalance(BiNode<T, keyType>* &tree);
	//右旋旋转处理
	void R_Rotate(BiNode<T, keyType>* &tree);
	//左旋旋转处理
	void L_Rotate(BiNode<T, keyType>* &tree);
	static enum LROri{Left, Right};//新添加的节点在左子树上或右子树上

public:
	int size;//节点数目
	BiNode<T, keyType>* root;//根节点
	AVLTree() : size(0), root(nullptr) {}
	~AVLTree() { if(size > 0) DestroyTree(root);  size = 0;}

	//插入新的节点，倒数第二个变量是用于判断树长高与否的变量
	bool insert(const T & content, const keyType & key, bool& taller, BiNode<T, keyType>* &tree);
	bool insert(const T & content, const keyType & key);//封装，便于调用
	//查找是否有关键词为key的节点，如果有，返回true，address返回节点的位置，否则返回false，address返回nullptr
	bool search(BiNode<T, keyType>* tree, const keyType& key, BiNode<T, keyType>* &address);
	bool search(const keyType& key, BiNode<T, keyType>* &address);//封装，便于调用
	//调整二叉树使其平衡，第一个参数是待调整的树的根节点，
	//第二个参数为插入的节点位置在左子树上还是右子树上，第三个参数为用于判断树长高与否的变量（insert的最后一个变量）
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