#pragma once
#include<iostream>

using namespace std;

struct node
{
	bool mark;//��ǰ����Ƿ����һ���ַ�;
	node**child;//��һ������洢���ӵ�λ��ָ��;
	char alphabet;
	int num;
	node() {
		mark = false;
		child = new node*[26];
		alphabet = NULL;
		num = 0;
		for (int i = 0; i < 26; i++)
		{
			child[i] = NULL;
		}
	}
};
class Trie
{
public:
	node* MakeTrie();//��ʼ��һ���ֵ���;
	void Insert(node* T,const char* a);//���һ���ַ���;
	void Delete(node* T, char* a);//ɾ��һ���ַ���;
	node* search(node* T, char* a);
	Trie();
	~Trie();
};

