#pragma once
#include<iostream>
#include<vector>
using namespace std;

struct Rectangle//ע��һ�¿�������������;��������������������������������������������������������
{
	int leftPoint_x;
	int leftPoint_y;
	int rightPoint_x;
	int rightPoint_y;
	Rectangle() {
		leftPoint_x = 0;
		leftPoint_y = 0;
		rightPoint_x = 0;
		rightPoint_y = 0;
	}
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
	void Delete(Rectangle re);//ɾ��R���е�һ������;
	RTree();
	~RTree();
private:
	Node* ChooseLeaf(Rectangle re);//����Ҫ�����Ҷ�ӽ��;
	inline int areaIncrease(Rectangle r1,Rectangle r2);//��r1 ����� r2 ʱ������Ӷ���;
	inline int area_compute(Rectangle r1, Rectangle r2);//����r1 ��r2 �������ι��ɵ�MBR�����;
	inline void changeRegion(Rectangle& r1 ,Rectangle r2);//�����r2���޸�r1�� region ��;
	void splitNode(Node* node);
	inline bool RectangleEqual(Rectangle r1, Rectangle r2);
	void updateRegion(Node* node);
};

