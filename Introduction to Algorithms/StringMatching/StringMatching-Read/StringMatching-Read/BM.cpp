#include	"general.h"
void PreBmBc(char*p,int* bmbc ) {

}
void Suffixes(char* p, int* suff) {
	int p_length = strlen(p);
	suff[p_length - 1] = p_length;

	for (int i = p_length - 2; i > 0; ++i) {

	}
}
void BM(char* buffer, char* p) {
	int* bmbc = new int[128];
	memset(bmbc, -1, 128 * sizeof(int));
	PreBmBc(p, bmbc);
	int p_length = strlen(p);
	int b_length = strlen(buffer);
	int i = 0, j = p_length-1;//i������ʾ�ı�buffer��ǰ��ָʾ��j����ָʾģʽp��ǰ��ָʾ��
	int temp = 0;
	int* suff = new int[p_length];   //suff[i]=s  ��ʾ��ȡ��iλ�ã���s���ַ�ƥ�� ; 
	memset(suff, 0, p_length * sizeof(int));
	Suffixes(p, suff);
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
			}
			else
			{
				j = p_length - 1;
				i = temp+1;
			}//���û��ַ�����������  i  Ӧ���ڵ�λ��;   ����

			//�����������úú�׺�Ĺ���������ó�  i  Ӧ���ڵ�λ��     ��ʼ;



			//�ú�׺����    ����;


		}//else
	}
}