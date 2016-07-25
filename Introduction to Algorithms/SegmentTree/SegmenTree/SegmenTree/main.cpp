#include<iostream>
#include<time.h>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
int iMin = 1;
int iMax = RAND_MAX;
//void readfile(int* ve) {
void readfile(vector<int> & ve){
	//ifstream myread("E:\\mid.txt");
	ifstream myread("E:\\large.txt");
	if (!myread)
	{
		cout << "Can Not Open The File!!!" << endl;
		system("pause");
		exit(0);
	}

/*
	//�����·���    ������ķ���Ҫ��
	string t;
	myread.seekg(0, myread.end);
	int length = myread.tellg();
	myread.seekg(0, myread.beg);
	char* buffer = new char[length + 1];
	memset(buffer, 0, length+1);
	buffer[length] = '\0';
	myread.read(buffer, length);
	istringstream ss(buffer);
	char temp_char;
	int temp_num;
	while (ss >> temp_char)
	{
		ss >> temp_num;
		ve.push_back(temp_num);
		ss >> temp_char;
		ss >> temp_num;
		ve.push_back(temp_num);
		ss >> temp_char;
	}

*/  //�Ϸ���
	int temp=0;
	char a;
	while (myread.get(a))
	{
		if (a=='(')
		{
			//myread >> ve[temp++];
			myread >> temp;
			ve.push_back(temp);	
		}
		myread.get(a);
		if (a==',') 
		{
			//myread >> ve[temp++];
			myread >> temp;
			ve.push_back(temp);
		}
	}
	myread.close();
}
struct SegmentTreeNode
{
	int left;
	int right;
	int  cover;
	int value;
};
void InitSegmentTree(int left, int right, SegmentTreeNode* Seg_Arr, int root) {
	SegmentTreeNode temp;
	temp.left = left;
	temp.right = right;
	temp.cover = 0;
	temp.value = 0;
	Seg_Arr[root] = temp;
	if (left != right)
	{
		int mid = (left + right) / 2;
		InitSegmentTree(left, mid, Seg_Arr, 2 * root + 1);
		InitSegmentTree(mid + 1, right, Seg_Arr, 2 * root + 2);
	}
	else
	{
		return;
	}
}

void Search(SegmentTreeNode* Seg_Arr,int root,int left ,int right) {
	if (Seg_Arr[root].left>=left&&Seg_Arr[root].right<=right)
	{
		//���һ������λ;
		//���root����;
	}
	if ((Seg_Arr[root].left+ Seg_Arr[root].right)/2 >=left)
	{
		Search(Seg_Arr, 2 * root + 1, left, right);
	}
	if ((Seg_Arr[root].left + Seg_Arr[root].right) / 2 <right)
	{
		Search(Seg_Arr, 2 * root + 2, left, right);
	}
}

//��
void InsertSegmentTree(SegmentTreeNode* Seg_Arr,int root,int left,int right) {
	if (Seg_Arr[root].left >= left&&Seg_Arr[root].right <= right)
	{
		Seg_Arr[root].cover++;
		return;
	}
	if ((Seg_Arr[root].left+Seg_Arr[root].right)/2 >=left)
	{
		InsertSegmentTree(Seg_Arr, 2 * root + 1, left,right);
	}
	if ((Seg_Arr[root].left + Seg_Arr[root].right) / 2<right )
	{
		InsertSegmentTree(Seg_Arr, 2 * root + 2, left, right);
	}
}

//1   ����ĳһ�����ݵ�ʱ��������������⣬��ʱû�з�������������⣬   yuanmo  ���ֵ����� 
//void InsertSegmentTree1(SegmentTreeNode* Seg_Arr, int root, int left, int right) {
//	//if (root>2 * (iMax - iMin) + 1)
//	//{
//	//	return;
//	//}
//	if (Seg_Arr[root].left>=left&&Seg_Arr[root].right<=right)
//	{
//		Seg_Arr[root].cover++;
//		return;
//	}
//	if (left<= (Seg_Arr[root].left + Seg_Arr[root].right) / 2 && (Seg_Arr[root].left + Seg_Arr[root].right) / 2<right)
//	{
//		InsertSegmentTree1(Seg_Arr, 2 * root + 1, left, (Seg_Arr[root].left + Seg_Arr[root].right) / 2);
//		InsertSegmentTree1(Seg_Arr, 2 * root + 2,  (Seg_Arr[root].left + Seg_Arr[root].right) / 2+1,right);
//	}
//	if (right<= (Seg_Arr[root].left + Seg_Arr[root].right) / 2)
//	{
//		InsertSegmentTree1(Seg_Arr, 2 * root + 1, left, right);
//	}
//	if (left>(Seg_Arr[root].left + Seg_Arr[root].right) / 2)
//	{
//		InsertSegmentTree1(Seg_Arr, 2 * root + 2, left, right);
//	}
//}

int main() {
	clock_t time = clock();
//	int iMax = 10;
	SegmentTreeNode * Seg_Arr = new SegmentTreeNode[2 * (iMax - iMin)+1];
	InitSegmentTree(iMin, iMax, Seg_Arr, 0);
//	cout << iMin << "��" << iMax << "֮����߶��������ɹ�" << endl;
	vector<int> ve;
	vector<int>::iterator ve_iterator = ve.begin();
	readfile(ve);
	//�����洢�߶��������飬��ʱ�Ȳ�������Ĵ洢�ṹ;
	//�� ve �е��߶β���Seg_Arr  ;
	//for (ve_iterator; ve_iterator != ve.end(); ve_iterator++)
	for(int i=0;i<ve.size();++i)
	{
		//InsertSegmentTree(Seg_Arr,0, *ve_iterator++, *ve_iterator);
		//InsertSegmentTree1(Seg_Arr, 0, *(ve_iterator++), *ve_iterator);
		InsertSegmentTree(Seg_Arr, 0, ve[i++], ve[i]);
		//InsertSegmentTree1(Seg_Arr, 0, ve[i++], ve[i]);
	}
	time = clock() - time;
	cout << "The program run time is " << time << " ms" << endl;
	delete[] Seg_Arr;//�ͷŴ���������  ע��һ��Ҫ�ͷţ�����;
	system("pause");
	return 0;
}