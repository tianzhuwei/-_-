#include <iostream>
using namespace std;
//��������������ж�һ�������Ƿ���һ���������ĺ������;
/*��Ҫ˼�룺 ��һ������������ĺ������˳����   D E B F G C A ;
	�����ǿ���֪��AΪ������� �����  �Ӻ�ǰ���бȽϵ�������AС��ʱ�� ֮��ĵ㼴ΪA�������������еݹ���ü���;
*/

int check(int a[],int start,int end){
	if (start<=end){

		int i=end-1;
		for (;a[i]>a[end]&&i>=0;--i)
		{
		}
		
		//i��Ϊ������е����ֵ㣬���������з�Ϊ�����������У�start,i��ΪС�ڸ��Ĳ��֣���i+1,end��Ϊ���ڸ��Ĳ���;
	
		for (int j=i;j>=0;j--)
		{
			if (a[j]>a[end])
			{
				cout<<"no"<<endl;
				return 0;//����0������;
			}
		}
		check(a,start,i);
		check(a,i+1,end-1);
	}
	return 1;
}


int  main(){

	int a[7]={5,7,6,9,11,10,8};
	int result=check(a,0,6);
	if (result==1)
	{
		cout<<"yes"<<endl;
	}


	system("pause");
	return 0;
}