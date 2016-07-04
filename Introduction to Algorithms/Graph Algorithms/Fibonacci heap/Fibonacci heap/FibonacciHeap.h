#pragma once
#include<iostream>
#include<cmath>

using namespace std;

struct node
{
	bool mark;//��������ڲ�֪����ʲô;
	node* parent;//ָ�򸸽��;
	node* child;//ָ���ӽ��;
	node* pre;//����ǰָ��;
	node* next;//����ָ�룻
	int key;//�ؼ��ֵ�ֵ;
	int degree;
};
struct FibonacciHeap_Head
{
	node* min;//ָ����С�ĵ�;
	int n;//���ж���ĸ���;
};
class FibonacciHeap
{
public:
	//FibonacciHeap_Head H;//FibonacciHeap �����У�Ҳ����û�У���ע��
	
public:
	FibonacciHeap_Head* Make_Heap();//��ʼ��һ���յ� ��;
	void Insert(FibonacciHeap_Head *H,node* x);//�� x ������ H ;
	node* Minimum(FibonacciHeap_Head *H);//����ָ����С����ָ��;
	node* Extract_Min(FibonacciHeap_Head* H);//ɾ����С�ؼ��֣������ظ�ָ��;
	FibonacciHeap_Head* Union(FibonacciHeap_Head* H1, FibonacciHeap_Head* H2);
	FibonacciHeap();
	~FibonacciHeap();

private:
	void Consolidate(FibonacciHeap_Head* H);
	void swap(node* a,node* b);
	void Heap_Link(node* small,node* big);
private:

};

