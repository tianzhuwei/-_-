#pragma once
#include <iostream>
#include<time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;
struct Edge 
{
	int vexName;//��������;
	Edge* next;//ָ�����һ����;
	int weight;//Ȩ��;
};
struct ArcNode
{
	int incount;//�������;
	Edge* firstEdge;
	int visit;
};
class Graph
{
private:
	//;
	int edgeNum;//;
public:
	ArcNode* head;
	int vexNum;
private:
	void initGraph();
	void initArcNode();
	void dirGraph(int start,int end);
	void nodirGraph(int start,int end);
	void DFS(int v);
public:
	void Kahn();
	void Under_DFS();
	Graph(void);
	~Graph(void);
	void readfile();

};

