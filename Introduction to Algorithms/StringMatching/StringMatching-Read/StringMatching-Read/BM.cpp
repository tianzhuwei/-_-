#include	"general.h"

/*
iע�⣺
����д����� �����ʱ���ұϲ���⣡������������������
�����Ѿ���ˮ
*/

void PreBmBc(char*p,int* bmbc ) {
	int p_length = strlen(p);
	for (int i = 0; i < p_length; i++)
	{
		bmbc[i] = p_length;
	}
	for (int i  = 0; i < p_length; i++)
	{
		bmbc[p[i]] = p_length - i - 1;
	}
}
void Suffixes(char* p, int* suff) {
	int p_length = strlen(p);
	int q;
	suff[p_length - 1] = p_length;
	for (int i = p_length - 2; i >= 0; --i) {
		q = i;
		while (q>=0&& p[q]==p[p_length-1-i+q])
		{
			--q;
		}//while
		suff[i] = i - q;
	}
}
void preBmGs(char* p, int* suff,int * bmGs) {
	int p_length = strlen(p);
	for (int i = 0; i < p_length; i++)
	{
		bmGs[i] = p_length;
	}
	int j = 0;
	for (int i = p_length-1; i >=0; --i)
	{
		if (suff[i]==i+1)
		{
			for ( ;  j<p_length -1-i ;++j)
			{
				if (bmGs[j]==p_length)
				{
					bmGs[j] = p_length - 1 - i;
				}
			}
		}
	}//for;
	for (int i = 0; i < p_length-2; i++)
	{
		bmGs[p_length - 1 - suff[i]] = p_length - 1 - i;
	}
}
void BM(char* buffer, char* p) {
	int count = 0;
	int* bmbc = new int[128];//������ʾp�е�ĳ���ַ�����λ�õ��±�;
	memset(bmbc, -1, 128 * sizeof(int));//ȫ����ʼ��Ϊ-1;
	PreBmBc(p, bmbc);
	int p_length = strlen(p);
	int b_length = strlen(buffer);
	int i = 0, j = p_length-1;//i������ʾ�ı�buffer��ǰ��ָʾ��j����ָʾģʽp��ǰ��ָʾ��
	int temp = 0;
	int* suff = new int[p_length];   //suff[i]=s  ��ʾ��ȡ��iλ�ã���s���ַ�ƥ�� ; 
	memset(suff, 0, p_length * sizeof(int));
	Suffixes(p, suff);
	int* bmGs = new int[p_length];//bmGs[i] ��ʾ�����ú�׺ʱ��ģʽ��Ӧ���ƶ��ľ��룬����i��ʾ�ú�׺ǰ��һ���ַ���λ�ã�Ҳ���ǻ��ַ���λ�ã�;
	preBmGs(p, suff, bmGs);
	while (i<=b_length-p_length)
	{
		for (j=p_length-1; j >= 0 && buffer[i + j] == p[j]; --j);
		if (j<0)
		{
//			cout << "shift " << i << endl;
			//i +=bmGs[0];
			i += p_length;
			count++;
		}
		else
		{
			i += bmGs[j];
			temp = bmbc[buffer[i + j]] - (p_length - 1) + j;
			if (i<temp)
			{
				i += temp;
			}
		}
	}
	cout << "Number is " << count << endl;
/*
	while (i<b_length-p_length)
	{
		temp = i + p_length-1;
		while (p[j]==buffer[temp]&&j>=0&&temp>=0)
		{
			temp--;
			j--;
		}
		if (j==0)
		{
			cout << "shift " << temp << endl;
			j = p_length;
			i += p_length;
		}
		else
		{
			if (bmbc[buffer[temp]]!=-1)//���û��ַ�����������  i  Ӧ���ڵ�λ��;   ��ʼ
			{
				i = temp - bmbc[buffer[temp]];
				j = p_length - 1;
			}//���û��ַ�����������  i  Ӧ���ڵ�λ��;   ����
			else
			{
				i = temp + 1;
				j = p_length - 1;
			}
			//�����������úú�׺�Ĺ���������ó�  i  Ӧ���ڵ�λ��     ��ʼ;
			//��������Ѿ�д����  bmGs[ ]
			if (bmGs[temp]>i)
			{
				i = bmGs[i];
			}
			//�ú�׺����    ����;
		}//else
	}
	*/
}