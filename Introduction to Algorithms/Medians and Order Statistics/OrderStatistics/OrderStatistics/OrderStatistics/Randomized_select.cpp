#include<iostream>
#include<time.h>
#include<algorithm>
using namespace std;

void InsertSort(int* arry, int start, int p);
void change1(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}
void random(int low, int high, int *arry) {
	if (low<high)
	{
		srand((unsigned)time(NULL));
		int r = rand() % (high - low);
		r = r + low + 1;
		change1(arry[r], arry[high]);
	}
}
void ThreeOfMiddle(int low ,int high,int *arry) {
	if (low<high)
	{
		int middle = (low + high) / 2;
		if (arry[low]>arry[high])
		{
			change1(arry[low], arry[high]);
		}
		if (arry[low]>arry[middle])
		{
			change1(arry[low], arry[middle]);
		}
		if (arry[middle]<arry[high])
		{
			change1(arry[middle], arry[high]);
		}
	}
}
int partition(int low, int high, int *arry) {//���ػ��ֵ�λ�ã�
		//random(low, high, arry);
		ThreeOfMiddle(low, high, arry);
		int temp = arry[high];
		int i = low - 1, j = low;
		for (; j <high ; j++)
		{
			if (arry[j]<=temp)
			{
				++i;
				change1(arry[i], arry[j]);
			}
		}
		change1(arry[++i], arry[high]);
		return i;
}
//�Ƿ���Բ��þ�key�ķ��������Randomized_select���ڴ�����ͬԪ�رȽ϶�ʱ��Ч���أ���


void Randomized_select(int low ,int high,int *arry,int pos){

	if (high-low<20)
	{
		//InsertSort(arry, low, high);
		sort(arry+low, arry+high);
		cout << "In the number is " << arry[pos] << endl;
	}
	
	//if (low==high)//ԭ����;
	//{
	//	cout << "In the number is " << arry[low] << endl;
	//}
	else
	{
		//���þ�key������ȡ������������
		ThreeOfMiddle(low, high, arry);
		int i = low, j = high;
		int left_mark = low - 1, right_mark = high + 1;
		int temp = arry[high];

		int ll = low - 1;
		int m = low;
		for (;m<high;++m)
		{
			if (arry[m]<=temp)
			{
				change1(arry[m], arry[++ll]);
				if (arry[ll]==temp)
				{
					change1(arry[++left_mark],arry[ll]);
				}
			}
		}
		change1(arry[++ll], arry[high]);
		//llΪ�����λ��
		int aa = low;
		j = ll;
		while (aa<=left_mark)
		{
			change1(arry[aa++], arry[--ll]);
		}
		i = ll;

		//while (i != j)
		//{
		//	while (arry[i] <= temp&&i<j)
		//	{
		//		if (arry[i] == temp)
		//		{
		//			change1(arry[i], arry[++left_mark]);
		//		}
		//		++i;
		//	}//while;
		//	arry[j] = arry[i];
		//	while (arry[j] >= temp&&i<j)
		//	{
		//		if (arry[j] == temp)
		//		{
		//			change1(arry[j], arry[--right_mark]);
		//		}
		//		--j;
		//	}//while;
		//	arry[i] = arry[j];
		//}//��ѭ������ʱ����temp��ͬ��Ԫ���Ѿ��ֲ������������
		//arry[i] = temp;
		// //�������ǽ��ֲ�����temp��ͬ��Ԫ�طŵ��м�λ��;
		//int a = low;
		//while (a <= left_mark)
		//{
		//	change1(arry[a++], arry[--i]);
		//}
		//int b = high;
		//while (b >= right_mark)
		//{
		//	change1(arry[j++], arry[b--]);
		//}
		//�� i �� j ֮��Ϊ��ͬ��key;
		//ֻҪpos�� i �� j ֮������ڼ��κ�һ��ֵ����;
		if (pos >= i&&pos <= j)
		{
			cout << "In the number is " << arry[pos] << endl;
		}
		else if (pos<i)
		{
			Randomized_select(low, i - 1, arry, pos);
		}
		else
		{
			Randomized_select(j + 1, high, arry, pos);
		}
		//������ԭ������
		//int pivot = partition(low, high, arry);
		//if (pivot==pos)
		//{
		//	cout << "In the number is " << arry[pos] << endl;
		//}
		//else if (pivot>pos)
		//{
		//	Randomized_select(low, pivot - 1, arry, pos);
		//}else
		//	Randomized_select(pivot + 1,high, arry, pos);

	}//else;

}//end;
