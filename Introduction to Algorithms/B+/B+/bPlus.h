#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Node
{
	vector<int>*key;//���ڴ�Źؼ��ֵ�����;
	vector<Node*>*child;//���ڴ�ź���ָ�������;
	Node* parent;//�洢���׽��;
	Node* next;//����Ҷ�ӽ��ָ����һ��Ҷ�ӽ��;
	Node* pre;//����Ҷ�ӽ��ָ����һ��Ҷ�ӽ��;
	Node() {
		next = NULL;
		pre = NULL;
		parent = NULL;
		key = new vector<int>;
		child = new vector<Node*>;
	}
};

class bPlus
{
public:
	Node* head;
public:
	bPlus();
	~bPlus();
	void addKey(int key);
	void deletekey(int key);
	Node* search(int key);
private:
	int m;//B+ ���Ľ�����˽ÿ�����ؼ��ֵĸ����� (m/2)~m   ;  ����������������ؼ���  ;            ����������������������Ŀǰֻ��ѡż��
	int min;//�����С����;
private:
	void InitBplus();
	void InsertSort(vector<int>* ve);
	void Union(Node* node);
	void changeBig(Node* node,int key);
	void changeSmall(Node* node);
	void BrrowKey(Node* deleteNode, Node* brother);
	void leavesUnion(Node* left,Node* right);
};