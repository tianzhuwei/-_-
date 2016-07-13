#pragma once
#include<iostream>
#include<string>
using namespace std;

struct EdgeNode;
struct Node {//���ṹ;
	EdgeNode* alph[27];//ǰ26����ʾ��ĸ ��ÿ27����ʾһ�������ַ�;
	Node* suffixNode;
	Node() {
		this->suffixNode = NULL;
		for (int i = 0; i < 26; i++)
			alph[i] = NULL;
	}
};
struct active {
	Node* active_node;
	EdgeNode* active_edge;
	int active_length;
};
struct EdgeNode {//�߽��ṹ;
	int startNum;
	int endNum;
	Node* nextNode;
	EdgeNode() {
		startNum = 0;
		endNum = 0;
		nextNode = NULL;
	}
};
class SuffixTree
{
public:
	string words;
	Node head;
public:
	SuffixTree();
	~SuffixTree();
	Node InitSuffixTree();//��ʼ��һ���� ��׺����Ҳ����˵ֻ��һ��ͷ���;
private:
	bool find(char word);//�������ҵ�ǰ�����Ƿ����ַ���a��;
	void addChar(Node* head,string content);
	void innerSplit(int position, Node* prefixNode);//  innerSplit(chars, currenctIndex, splitNode);
private:
	active activePoint;//һ��������Ԫ����;

	int reminder;	//��ÿ�����迪ʼʱʣ���׺��������������Ϊ1�����������������������뵽ÿһ����ĩβ�ĺ�׺��Ŀ��1���������һ���ַ���;
};