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
	int const MAX = 99999;
	vector< vector<int> >A;//
	vector< vector<int> >Path;//;
	int nodeNum, edgeNum;
	double**L;
	double**temp;
private://˽�к���;
	void readfile();
	void Init_A_Path();
	void W_L();
public://�����ı���;
	//vector<vector<double>> GraphHead;//���þ���Ľṹ�洢ͼ;
	double* *a;//��ά����;
public://�����ĺ���;
	void Floyd();
	void Juzhenchengfa();
	Graph();
	~Graph();
};
