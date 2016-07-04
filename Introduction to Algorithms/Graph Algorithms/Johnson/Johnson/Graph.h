#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<time.h>
using namespace std;
struct EdgeNode {
	int end;
	double weight;
};

class Graph
{
private://˽�б���;
	int *dis;
private://˽�к���;
	void readfile();
public://�����ı���;
	//ArcNode* GraphHead;
	vector<vector<EdgeNode>*> GraphHead;
public://�����ĺ���;
	void BellmanFord(int S);
	void Dijkstra(int S);
	void Johnson();
	Graph();
	~Graph();
};
