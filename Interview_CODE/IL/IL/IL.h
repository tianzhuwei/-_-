#pragma once
#include "Read.h"
#include "Node.h"
class IL:public Read
{
public:
	int*CO_lm;//����ƥ��;
	int*CO_rm;

	int n;
	Node descendant_all;//����ȫ�ִ洢descendant���;
	Node lca_all;//�����洢ȫ��lca���;

//	int num;//�����Բ���ʱ�����ݽ���ѭ��ʹ��;
	CArray<int*,int*>* *S;//�����洢��Ӧ�ؼ���id������ָ��;
	IL(void);
	~IL(void);
	void input();
	void output(int*v);
// 	int* rm(int v, CArray<int*,int*>* S2);//right match ��ƥ�� ,v�������������һ��intֵ,S2Ϊ�ؼ��ֵ�һ������;
// 	int* lm(int v ,CArray<int*,int*>*S2);//left match ��ƥ��,����ƥ���෴��˼·����;
	void  descendant(Node &v1,Node &v2);
	void  lca(int*&v1,int*&v2);
	int IsAncestor(Node  &v1,Node  &v2);
	void Bubble(CArray<int*,int*>**S,int n);
	CArray<int*,int*>* get_slca(CArray<int*,int*>*&S1,CArray<int*,int*>*&S2);
	void testdata(CString data[32][7],int num);
	void lmANDrm(int v ,CArray<int*,int*>* &S2);
};

