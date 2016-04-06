#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;
int shuzhou(int ve[], int low ,int high){
	srand((unsigned)time(NULL));
	int random_num=rand()%(high-low)+low+1;

	int tem=ve[low];
	ve[low]=ve[random_num];
	ve[random_num]=tem;

	return ve[low];
}
void qucik_sort_random(int ve[],int low,int high){
	if (low>=high)
	{
		return;
	}
	int i=low;
	int j=high;
	int pivot=shuzhou(ve,low,high);

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
	qucik_sort_random(ve,low,i-1);
	qucik_sort_random(ve,i+1,high);
}
int main(){

	cout<<"�������н����ʹ��  �������  ��������˼��û�н����Ż���"<<endl;
	int * ve;
	int num=1000000;//һ���������;
	//int num=10;
	ve=new int[num];
	srand((unsigned)time(NULL));
	for (int i=0;i<num;++i)
		ve[i]=rand()%100;
	clock_t time1=clock();
	qucik_sort_random(ve,0,num-1);
	time1=clock()-time1;
	cout<<"�������(һ����)��ʱ��"<<time1<<"ms"<<endl;
	clock_t time2=clock();
	qucik_sort_random(ve,0,num-1);
	time2=clock()-time2;
	cout<<"��������(һ����)��ʱ��"<<time2<<"ms"<<endl;

	for (int i=0;i<num;++i)
	{
		ve[i]=10;
	}
	clock_t time3 =clock();
	qucik_sort_random(ve,0,num-1);
	time3=clock()-time3;
	cout<<"�ظ�����(һ����)��ʱ��"<<time3<<"ms"<<endl;


	delete[] ve;
	ve=NULL;

	system("pause");
	return 0;
}