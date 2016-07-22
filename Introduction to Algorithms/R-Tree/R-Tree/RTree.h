#pragma once
#include<iostream>
#include<vector>
using namespace std;

struct Rectangle
{
	int leftPoint;
	int rightPoint;
};

struct Node;
struct childNode
{
	Rectangle region;
	Node* child;
	childNode() {
		child = NULL;
	}
};

struct Node
{
	Rectangle region;
	vector<childNode> child;
	Node* parent;
	Node() {
		parent = NULL;
	}
};

class RTree
{
public:
	int M;//M ��R��;
	int m;//M ��R�����ڽ�����ٵ�Ԫ�ظ�����M/2 ����ȡ��;
	Node * Root;//R���ĸ����;
public:
	void Insert(Rectangle re);//��R�����һ������;
	
	RTree();
	~RTree();
private:
	Node* ChooseLeaf(Rectangle re);//����Ҫ�����Ҷ�ӽ��;
	void AdjustTree();//������һ���µ�Ԫ�غ󣬿�����ɽ�㲻�ٷ���R�����ʣ�������Ҫ���е���;

};

