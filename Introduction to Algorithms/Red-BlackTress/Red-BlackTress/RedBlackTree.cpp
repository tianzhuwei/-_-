#include "RedBlackTree.h"



RedBlackTree::RedBlackTree()
{
	nil = new Node;
	nil->color = Black;
	nil->key = -1;
	root = nil;
}

void RedBlackTree::RBInsert(Node* node){
	Node* x , *y;
	x = root;
	y = nil;
	while (x!=nil)
	{
		y = x;
		if (node->key<x->key)
		{
			x = x->leftChild;
		}
		else
		{
			x = x->rightChild;
		}
	}
	node->parent = y;
	if (y == nil)
	{
		root = node;
	}
	else if (node->key < y->key)
		{
			y->leftChild = node;
		}
		else
		{
			y->rightChild = node;
		}
	node->leftChild = nil;
	node->rightChild = nil;
	//���ı���ɫ�Ĳ����ŵ�RBInsertFixup������;
	//����һ�����֮��Բ�������е���;
	RBInsertFixup(node);
}

void RedBlackTree::RBInsertFixup(Node* node)
{
	while (node->parent->color==Red)//���׽��Ϊ��ɫ;
	{
		if (node->parent == node->parent->parent->leftChild)//����������游��������;
		{
			Node* y = node->parent->parent->rightChild;//y Ϊnode �游�����Һ���;
			if (y->color == Red)//�Ǻ���;
			{
				node->parent->color = Black;
				y->color = Black;
				node->parent->parent->color = Red;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->rightChild)
				{
					node = node->parent;
					LeftRotate(node);
				}
				node->parent->color = Black;
				node->parent->parent->color = Red;
				RightRotate(node->parent->parent);
			}
		}
		else//���׽��Ϊ�游�����Һ���;
		{
			Node*y = node->parent->parent->leftChild;
			if (y->color == Red)
			{
				node->parent->color = Black;
				y->color = Black;
				node->parent->parent->color = Red;
				node = node->parent->parent;
			}//if;
			else {
				if (node == node->parent->leftChild)
				{
					node = node->parent;
					RightRotate(node);
				}
			node->parent->color = Black;
			node->parent->parent->color = Red;
			LeftRotate(node->parent->parent);
			}
		}
	}//
	root->color = Black;
}

void RedBlackTree::LeftRotate(Node* node) 
{
	Node* y = node->rightChild;
	node->rightChild = y->leftChild;
	if (y->leftChild!=nil)
	{
		y->leftChild->parent = node;
	}
	y->parent = node->parent;
	if (node->parent==nil)
	{
		root = y;
	}
	else if(node==node->parent->leftChild)
	{
		node->parent->leftChild = y;
	}
	else
	{
		node->parent->rightChild = y;
	}
	y->leftChild = node;
	node->parent = y;
}

void RedBlackTree::RightRotate(Node* node)
{
	Node* x = node->leftChild;
	node->leftChild = x->rightChild;
	if (x->rightChild!=nil)
	{
		x->rightChild->parent = node;
	}
	x->parent = node->parent;
	if (node->parent==nil)
	{
		root = x;
	}
	else if(node==node->parent->rightChild)
	{
		node->parent->rightChild = x;
	}
	else
	{
		node->parent->leftChild = x;
	}
	x->rightChild = node;
	node->parent = x;
}

void RedBlackTree::RBTransplant(Node* u, Node* v) //��v����u;
{
	if (u->parent==nil)
	{
		root = v;
	}
	else if (u==u->parent->leftChild)////////////////////////////////u=u->parent->leftChild,���������⣬����ô�ò��ҵ�����
	{
		u->parent->leftChild = v;
	}
	else
	{
		u->parent->rightChild = v;
	}
	v->parent = u->parent;
}

Node* RedBlackTree::TreeMinmum(Node* node)
{

	while (node->leftChild!=nil)
	{
		node = node->leftChild;
	}
	return node;
}

Node* RedBlackTree::RBSearch(int key)
{
	Node* cur = root;
	while (cur->key!=key&&cur!=nil)
	{
		//if (cur==nil)
		//{
		//	cout << "Can not find the key" << endl;
		//	return NULL;
		//}
		if (cur->key > key)
		{
			cur = cur->leftChild;
		}
		else
		{
			cur = cur->rightChild;
		}
	}
	return cur;
}

void RedBlackTree::RBDeleteFixup(Node* node)
{
	Node* w = NULL;
	while (node!=root&&node->color==Black)
	{
		if (node == node->parent->leftChild) //Ϊ����;
		{
			w = node->parent->rightChild;
			if (w->color==Red)
			{
				w->color = Black;
				node->parent->color = Red;
				LeftRotate(node->parent);
				w = node->parent->rightChild;
			}
			if (w->leftChild->color==Black&&w->rightChild->color==Black)
			{
				w->color = Red;
				node = node->parent;
			}
			else
			{
				if (w->rightChild->color == Black)
				{
					w->leftChild->color = Black;
					w->color = Red;
					RightRotate(w);
					w = node->parent->rightChild;
				}
				w->color = node->parent->color;
				node->parent->color = Black;
				w->rightChild->color = Black;
				LeftRotate(node->parent);
				node = root;
			}
		}
		else//Ϊ�Һ���;
		{
			 w = node->parent->leftChild;
			if (w->color==Red)
			{
				w->color = Black;
				node->parent->color = Red;
				RightRotate(node->parent);
				w = node->parent->leftChild;
			}
			if (w->leftChild->color==Black&&w->rightChild->color==Black)
			{
				w->color = Red;
				node = node->parent;
			}
			else
			{
				if (w->leftChild->color == Black)
				{
					w->rightChild->color = Black;
					w->color = Red;
					LeftRotate(w);
					w = node->parent->leftChild;
				}
				w->color = node->parent->color;
				node->parent->color = Black;
				w->leftChild->color = Black;
				RightRotate(node->parent);
				node = root;
			}
		}
	}
	node->color = Black;
}

void RedBlackTree::RBDelete(Node* node)
{
	Node* x=NULL;
	Node* y = node;
	color y_original_color = y->color;
	if (node->leftChild==nil)//left child is null;
	{
		x = node->rightChild;
		RBTransplant(node, node->rightChild);
	}
	else 	if (node->rightChild == nil)//only have left child ;
		{
			x = node->leftChild;
			RBTransplant(node, x);
		}
		else//have two child;
		{
			y = TreeMinmum(node->rightChild);
			y_original_color = y->color;
			x = y->rightChild;
			if (y->parent == node)
			{
				x->parent = y;
			}
			else
			{
				RBTransplant(y, y->rightChild);
				y->rightChild = node->rightChild;
				y->rightChild->parent = y;
			}
			RBTransplant(node, y);
			y->leftChild = node->leftChild;
			y->leftChild->parent = y;
			y->color = node->color;
		}
	if (y_original_color==Black)
	{
		RBDeleteFixup(x);
	}
}

RedBlackTree::~RedBlackTree()
{

}
