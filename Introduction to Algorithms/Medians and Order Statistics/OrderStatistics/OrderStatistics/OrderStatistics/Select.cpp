#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
void InsertSort(int* arry,int start,int p) {
	for (int i= start+1; i<= p; i++)
	{
		int te = arry[i];
		int j = i;
		while (arry[j] < arry[j - 1] && j > start)
		{
			arry[j] = arry[j - 1];
			arry[j - 1] = te;
			j--;
		}
		
	}
}
int find_middle(int *arry, int left, int right){
	//5��Ԫ��Ϊһ�飬���������ֱ�Ӳ�������;
	if ((right-left)<5)
	{
		InsertSort(arry, left, right);
		int a = left + (right - left) / 2;
		return arry[a];
	}
	else
	{
		int groupNum = 0;
		if ((right-left+1)%5==0)
		{
			groupNum = (right - left + 1) / 5;
		}
		else
		{
			groupNum = (right - left + 1) / 5 + 1;
		}
		for (int i = 0; i < groupNum; ++i)
		{
			int s = 5 * i;
			int e = s + 4;
			if (e <= right)
			{
				InsertSort(arry, s, e);
			}
			else
			{
				InsertSort(arry, s, right);
			}
		}//for;
		//int* new_arry = new int[groupNum];
		vector<int>  new_arry;
		for (int i = 0; i < groupNum-1; ++i)
		{
			//new_arry[i] = arry[5 * i + 2];
			new_arry.push_back(arry[5 * i + 2]);
		}
		int m = (right - (groupNum - 1) * 5)/2;
		//new_arry[groupNum - 1] = arry[5 * (groupNum-1) + m];
		new_arry.push_back(arry[5 * (groupNum - 1) + m]);
		//find_middle(new_arry, 0, groupNum);//�ٴ�Ѱ����λ��;
		//�ĳɶ�������ֱ�ӽ�������	;
		sort(new_arry.begin(), new_arry.end()-1);
		return new_arry[groupNum / 2];
	}//else;
}
void change(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
int huafen(int*arry, int s,int e) {
	int p = arry[e];
	int i = s - 1;
	for (int j = s; j < e; j++)
	{
		if (arry[j] <= p) {
			i++;
			change(arry[i],arry[j]);
		}
	}//for;
	change(arry[i + 1], arry[e]);
	return i + 1;
}
int Select(int* arry ,int left,int right ,int pos ){
	int middle = find_middle(arry,left,right);//�����λ������λ��;
	int i = left;
	for (; i < right; i++)
	{
		if (arry[i] == middle)
			break;
	}
	change(arry[i], arry[right]);
	//�����ҵ�����λ����������л��֣����ƿ��ŵĻ��֣�;
	int m=	huafen(arry, left,right);//mΪ����Ԫ�����ڵ�λ��;
	if (m==pos)
	{
		cout << "��" << pos << "����Ϊ" << arry[m] << endl;
		return arry[m] ;
	}
	else if (m>pos)
	{
		 Select(arry, left, m - 1, pos);
	}
	else
	{
		 Select(arry, m + 1, right,pos);
	}
}