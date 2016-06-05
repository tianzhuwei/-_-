#include<iostream>
#include<algorithm>
using namespace std;
void InsertSort(int* arry, int start, int p);
int find_middle(int *arry, int left, int right){//�����±�;
	//5��Ԫ��Ϊһ�飬���������ֱ�Ӳ�������;
	if ((right-left)<5)
	{
		InsertSort(arry, left, right);
		int a = left + (right - left) / 2;
		return a;
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
		int* new_arry = new int[groupNum];
		for (int i = 0; i < groupNum-1; ++i)
		{
			new_arry[i] = arry[left+5 * i + 2];
		}
		int m = (right - (groupNum - 1) * 5)/2;
		//int m=(right - (groupNmu - 1 )*5);
		new_arry[groupNum - 1] = arry[5 * (groupNum-1) + m];
		//�ĳɶ�������ֱ�ӽ�������	;
		sort(new_arry, new_arry+groupNum);
		int aaa = new_arry[groupNum / 2];
		delete[] new_arry;
		for (int i = left; i <=right; i++)
		{
			if (aaa==arry[i])
			{
				return i;
			}
		}
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
			change(arry[++i],arry[j]);
		}
	}//for;
	change(arry[++i], arry[e]);
	return i ;
}
int Select(int* arry ,int left,int right ,int pos ){
	if (left==right)
	{
		cout << "The number is " << arry[left] << endl;
		return arry[left];
	}
	int middle = find_middle(arry,left,right);//�����λ������λ�����±�);
	change(arry[middle], arry[right]);
	//�����ҵ�����λ����������л��֣����ƿ��ŵĻ��֣�;
	//int m=	huafen(arry, left,right);//mΪ����Ԫ�����ڵ�λ��;
	int low = left, high = right;
	int i = low, j = high;
	int left_mark = low - 1, right_mark = high + 1;
	int temp = arry[high];

	int ll = low - 1;
	int m = low;
	for (; m<high; ++m)
	{
		if (arry[m] <= temp)
		{
			change(arry[m], arry[++ll]);
			if (arry[ll] == temp)
			{
				change(arry[++left_mark], arry[ll]);
			}
		}
	}
	change(arry[++ll], arry[high]);
	//llΪ�����λ��
	int aa = low;
	j = ll;
	while (aa <= left_mark)
	{
		change(arry[aa++], arry[--ll]);
	}
	i = ll;

	if (pos>=i&&pos<=j)
	{
		cout << "The number is " << arry[pos] << endl;
		return arry[m] ;
	}
	else if (i>pos)
	{
		 Select(arry, left, i - 1, pos);
	}
	else
	{
		 Select(arry, j + 1, right,pos);
	}
}