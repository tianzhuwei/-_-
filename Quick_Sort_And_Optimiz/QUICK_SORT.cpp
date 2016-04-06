#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;

void qucik_sort_origin(int ve[],int low,int high){
	if (low>=high)
	{
		return;
	}
	int i=low;
	int j=high;
	int pivot=ve[i];

	while (i!=j)
	{
		while(ve[j]>pivot&&i<j) 
			j--;
		if (i<j)
		{
			ve[i]=ve[j];
			i++;
		}
		while(ve[i]<pivot&&i<j)
			i++;
		if(i<j){
			ve[j]=ve[i];
			j--;
		}
	}
	ve[i]=pivot;
	qucik_sort_origin(ve,low,i-1);
	qucik_sort_origin(ve,i+1,high);
}
int main(){

	cout<<"�������н����ʹ��  ԭʼ  ��������˼��û�н����Ż���"<<endl;
	int * ve;
	int num=1000000;//һ���������;
	//int num=10;
	ve=new int[num];
	srand((unsigned)time(NULL));
	for (int i=0;i<num;++i)
		ve[i]=rand();
	clock_t time1=clock();
	qucik_sort_origin(ve,0,num-1);
	time1=clock()-time1;
	cout<<"�������(һ����)��ʱ��"<<time1<<"ms"<<endl;
	clock_t time2=clock();
	qucik_sort_origin(ve,0,num-1);
	time2=clock()-time2;
	cout<<"��������(һ����)��ʱ��"<<time2<<"ms"<<endl;

	for (int i=0;i<num;++i)
	{
		ve[i]=i/2;
	}
	clock_t time3 =clock();
	qucik_sort_origin(ve,0,num-1);
	time3=clock()-time3;
	cout<<"�ظ�����(һ����)��ʱ��"<<time3<<"ms"<<endl;


	delete[] ve;
	ve=NULL;

	system("pause");
	return 0;
}