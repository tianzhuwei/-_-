#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<time.h>
using namespace std;

//��һ�����õ�д���������
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
/*
void Swap_Father_Sons(vector<int> & ve,int root) {
	if (2*root+1 >ve.size()-1)
	{
		return;
	}
	int min;
	if (2*root+2>ve.size()-1)
	{
		min = ve[2 * root + 1];
	}else
	 min = ve[2*root+1] > ve[2*root+2] ? ve[2*root+2] : ve[2*root+1];
	if (min<ve[root])
	{
		if (min == ve[2 * root + 1])//�������ve[1]�����ģ�����������;
		{
			swap(min, ve[0]);
			Swap_Father_Sons(ve, 2 * root + 1);
		}
		else   //����������;
		{
			swap(min, ve[0]);
			Swap_Father_Sons(ve, 2 * root + 2);
		}
	}
}

void Init_BinaryHeap(vector<int> &ve) {
	int length = ve.size()-1;//lengthΪ���һ��Ԫ�ص��±�;
	if (length==0)
	{
		return;
	}
	int min;
	if (length%2==0)//���һ����Ҷ�ӽ�����������ӽ��;
	{
		min = ve[length] > ve[length - 1] ? ve[length - 1] : ve[length];
		if (ve[(length-1)/2]>min)
		{
			swap(min, ve[(length - 1) / 2]);
		}
	}
	else    //���һ��������һ�����ӽ��;
	{
		if (ve[length]<ve[(length - 1) / 2])
		{
			swap(ve[length],ve[(length - 1) / 2]);
		}
	}
	for (int i = (length-1)/2-1; i >0;--i)//�����±�Ϊ 1 ʱѭ��������֮���ֹ������±�Ϊ 0 ��λ������ ;
	{
		min = ve[2 * i + 1] > ve[2 * i + 2] ? ve[2 * i + 2] : ve[2 * i + 1];
		if (min<ve[i])
		{
			swap(min, ve[i]);
		}
	}
	Swap_Father_Sons(ve, 0);
	min = ve[1] > ve[2] ? ve[2] : ve[1];
	if (min<ve[0])
	{
		if (min == ve[1])//�������ve[1]�����ģ�����������;
		{
			swap(min, ve[0]);
			Swap_Father_Sons(ve,1);
		}
		else   //����������;
		{
			swap(min, ve[0]);
			Swap_Father_Sons(ve, 2);
		}
	}
}
*/
void fixup(vector<int> &ve,int root) {
	if (2*root+1<=ve.size())//��Ҫ����Ľ���к��ӽ��ʱ;
	{
		int min = 2 * root + 1;
		if (min+1<=ve.size()-1&&ve.at(min)>ve.at(min+1))
			min++;
		if (ve.at(root)>ve.at(min))
		{
			swap(ve.at(min), ve.at(root));
			fixup(ve, min);
		}
		else
		{
			return;
		}
	}
}
void Init_BinaryHeap(vector<int> &ve) {
	for (int i = (ve.size()-2)/2; i >=0; --i)//�����һ����Ҷ�ӽ�㿪ʼ���д���;
	{
		fixup(ve, i);
	}
}
void output(int &a ){
//	cout << a << " ";
}
int main() {
	clock_t time = clock();
	vector<int> ve;//������±�Ϊ  0  ʱ��ʼ;
	for (size_t i = 0; i < 100000; i++)
	{
		ve.push_back(rand());
		//cout << ve[i] << " ";
	}
	cout << endl;
	Init_BinaryHeap(ve);
	vector<int>::iterator it = ve.begin();
	for_each(ve.begin(), ve.end(),output);
	cout << endl;
	time = clock() - time;
	cout << "Use time  "<<time<<" ms ��" << endl;
	system("pause");
	return 0;
 }