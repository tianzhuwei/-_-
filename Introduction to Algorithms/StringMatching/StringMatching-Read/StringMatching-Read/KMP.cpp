#include"general.h"
int* Compute_Prefix_Function(char* p) {
	int p_length = strlen(p);
	int* next = new int[p_length+1];
	int j = 1;//
	int k = 0;//��ʾ�Ѿ�ƥ��ĸ���;
	next[0] = 0;
	while (j <= p_length) {
		while (k > 0 && p[k] != p[j])
			k = next[k - 1];
		if (p[k]==p[j])
			k++;
		next[j++] = k;
	}

	return next;
}
void KMP(char* buffer, char* p) {
	int count = 0;
	int buffer_length = strlen(buffer);
	int p_length = strlen(p);
	int* next = Compute_Prefix_Function(p);//next[i]�д洢��ֵ��ʾ�� ��i+1�����ַ���ʱ����󹫹�ǰ��׺�Ƕ���;
	int q = 0;//q������ʾ�Ѿ�ƥ��ĸ���;
	for (int i = 0; i < buffer_length; i++)//i������ʾԭ�ַ������浱ǰƥ��ĸ���;
	{
		while (q>0 && p[q]!=buffer[i])
			q = next[q-1];//�±�Ϊ(q-1)ʱ�Ѿ�ƥ��ĸ���Ϊq;

		if (p[q]==buffer[i])
			q++;

		if (q==p_length)
		{
//			cout << "Pattern occurs with shift " << i - p_length+1 << endl;
			q = next[q-1];
			count++;
		}
	}//for
	cout << "Kmp : number is " << count << endl;
}