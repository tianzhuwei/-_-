#pragma once
#include "Graph.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

struct EdgeNode
{
	int start_id;
	int end_id;
	float f;//���� ������С;
	float c;//�ߵĿ�ͨ���������;
	EdgeNode* nextout;//ָ�������ͬͷ���ĺ�;
	EdgeNode* nextin;//ָ�������ͬ�ս��ĺ�;
};

struct VexNode
{
	EdgeNode* firstin;//��һ��ָ��ö���ı�;
	EdgeNode* firstout;//�ö���ĵ�һ������;
};

class Graph//ͼ�Ĵ洢����ʮ������Ĵ洢�ṹ;
{
public:
	vector<VexNode>GraphHead;
public:
	void Relabel_To_Front();
	Graph();
	~Graph();

private:
	int* h;//�����洢ÿ�����ĵ�ǰ�߶�;
	float* e;//������Ŷ���ĳ������Ĵ�С;
	int souce_node;//Դ��㣻
	int sinks_node;//���;
	int* link;//����;
	int ifend();//�ж�link�����Ƿ��вд��������û�з���-1�����򷵻� �±�;
private:
	void Init();
};

