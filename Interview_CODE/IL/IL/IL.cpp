#include "IL.h"
#include <iostream>
#include <string>
#include <afxtempl.h>
#include <cstring>
#include <Windows.h>
using namespace std;
IL::IL(void)
{
}
IL::~IL(void)
{
}
void IL::input(){
	cout<<"������Ҫ��ѯ�Ĺؼ��ָ�����"<<endl;
	cin>>n;
	string* key;
	key=new string[n];
	CString* CString_key;
	S=new CArray<int*,int*>*;
	for (int i=0;i<n;i++)
	{
		cout<<"�������"<<i+1<<"���ؼ��֣��س�������"<<endl;
		cin>>key[i];
		CString_key=new CString[n];
		CString_key[i]=key[i].c_str();//��string����ת��ΪCString;
		if(!mycmap.Lookup(CString_key[i],S[i])){//S[i]->operator [](i)Ϊָ�������һ��ָ��;
			wcout<<"û�ܲ鵽�ؼ���"<<(LPCTSTR)CString_key[i]<<endl;
			cout<<"�����������"<<i+1<<"���ؼ��֣��س�������"<<endl;
			cin>>key[i];
		}
	}
	//������Ĺؼ��ְ���ID�ĸ�����С����������У�������߲�ѯ�ٶ�;
//	Bubble(S,n);
}

void IL::testdata(CString data[32][7],int num){
	cout<<"******��ʼ�Ե�"<<num+1<<"����в���******"<<endl;
	
	n=_ttoi(data[num][0]);
	S=new CArray<int*,int*>* [n];
	//S=NULL;
	for (int i=1;i<=n;++i)
	{
		mycmap.Lookup(data[num][i],S[i-1]);
	}
	Bubble(S,n);
}

void IL::Bubble(CArray<int*,int*>**S,int n){
	int i,j;
	int flag;
	CArray<int*,int*>*tem;
	tem=NULL;
	for (i=n;i>=1;--i)
	{
		flag=0;
		for (j=1;j<i;++j)
		{
			if ((*S[j-1]).GetSize()>(*S[j]).GetSize())
			{
				tem=S[j];
				S[j]=S[j-1];
				S[j-1]=tem;
				flag=1;
			}
			if (flag==0)
			{
				return;
			}
		}
	}
}

inline void IL::lmANDrm(int v ,CArray<int*,int*>* &S2){
	int S2_length=(*S2).GetSize();
	//int temp1=S2->operator[](0)[0];
	int temp1=S2->GetAt(0)[0];
	if (v<S2->operator[](0)[temp1])//��vС��S2����С��ֵʱ����ƥ��ΪNULL,��ƥ��ΪS2[0];
	{
		CO_lm=NULL;
		CO_rm=S2->operator[](0);
		return;
	}
	int s=S2->operator[](S2_length-1)[0];
	int temp2=S2->operator[](S2_length-1)[s];
	if (v>temp2)
	{
		CO_lm=S2->operator[](S2_length-1);
		CO_rm=NULL;
		return;
	}
	int low=1;
	int high=S2_length-1;
	while(low<=high){
		int mid=(low+high)/2;
		int len_mid=S2->operator[](mid)[0];
		int vmid=S2->GetAt(mid)[len_mid];
		if (v>vmid)
		{
			low=mid+1;
		}else
			high=mid-1;
	}//while
	CO_lm=S2->GetAt(high);
	CO_rm=S2->GetAt(high+1);
}

inline void  IL::descendant(Node &v1,Node &v2){
 	if (v1.data==NULL){
		descendant_all=v2;
		//return v2;
	}
	if (v2.data==NULL){
		descendant_all=v1;
		//return v1;
	}
	if (v1.length>v2.length)
	{
		descendant_all=v1;
		//return v1;
	}else {
		descendant_all=v2;
		//return v2;
	}
}
inline void  IL::lca(int* &v1,int* &v2){///////////////���ڿ����Ż��Ŀռ䣡��;
	if (v1==NULL||v2==NULL)
	{
		//Node a;
	//	return a;
	}else{
		//Node  beat;
		//beat=new Node;
		int n=0;
		int len1=v1[0];
		int len2=v2[0];
		int tem=len1<len2?len1:len2;
		for (int i=1;i<=tem;++i)
		{
			if (v1[i]==v2[i])
			{
				++n;
			}else break;
		}
		lca_all.length=n;
		lca_all.data=v1+1;
		//return beat;
	}//else;
}
inline int IL::IsAncestor(Node &v1,Node &v2){
	int len1=v1.length;
	int len2=v2.length;
	if (len1<len2 && v1.data[len1-1]==v2.data[len1-1])
	{
		return 1;//֮����ڸ��ӹ�ϵ;
	}else
		return 0;//v1����v2������;
}
CArray<int*,int*>* IL::get_slca(CArray<int*,int*>*&S1,CArray<int*,int*>*&S2){
	CArray<int*,int*>* Result;//Result�����洢���Ľ������;
	Result=new CArray<int*,int*>;
	Node x;
	//x=new Node;
	Node u;//��ʼʱuΪ�����;
	//u=NULL;
	int a[]={1};
	//u=new Node;
	u.length=1;
	u.data=a;
	for (int i=0;i<(*S1).GetSize();++i)
	{
		int*v=S1->operator[](i);
		int vlen=v[0];
		lmANDrm(v[vlen],S2);
		lca(v,CO_lm);
		Node lca_lm=lca_all;
		lca(v,CO_rm);
		Node lca_rm=lca_all;
		descendant(lca_lm,lca_rm);
		x=descendant_all;
   		int pre_u=u.data[u.length-1];
		int pre_x=x.data[x.length-1];
		if (pre_u<pre_x)
		{
			if (!IsAncestor(u,x)){//u����x������;
				int *change;
				change=new int[u.length+1];
				change[0]=u.length;
				for (int j=1;j<=u.length;++j)
				{
					change[j]=u.data[j-1];
				}
				(*Result).Add(change);
			}//if
			u=x;//��x��ֵ��u;////////////////ע��ע��λ�ã�����С��
		}//if
	}
	int *change;
	change=new int[u.length+1];
	change[0]=u.length;
	for (int j=1;j<=u.length;++j)
	{
		change[j]=u.data[j-1];
	}
	(*Result).Add(change);//�����һ������;
	return Result;
}
void IL::output(int*v){
	if (v==NULL)
	{
		cout<<"��"<<endl;
		return;
	}
	int length=v[0];
	for(int i=0;i<=length;i++)
		cout<<v[i]<<"  ";
	cout<<endl;
}