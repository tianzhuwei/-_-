#include"general.h"
void PuSu_match(char* buffer,char* p);
void KMP(char* buffer, char* p);
void BM(char* buffer, char* p);
void Sunday(char* buffer, char * p);
#include<string>
int main() {
	clock_t time = clock();
	ifstream DNA("E:\\���ݼ�\\DNA.txt");
	//ifstream DNA("E:\\test.txt");
	if (!DNA)
	{
		cout << "Can not open the file!" << endl;
		system("pause");
		return 1;
	}
	DNA.seekg(0,DNA.end);
	unsigned length = DNA.tellg();
	DNA.seekg(0,DNA.beg);
	cout << "string length is "<<length << endl;
	char* buffer = new char[length+1];
	memset(buffer, 0, length+1);
	DNA.read(buffer, length+1);
	//cout << "the string is " << endl;
	//cout << buffer << endl;
	if (DNA.eof())
	{
		cout << "all chacter readed!" << endl;
	}
	else
	{
		cout << "error: only  " <<DNA.gcount() << "  could be read";
	}
	DNA.close();
	time = clock() - time;
	cout << "Read Use time is " << time <<" ms"<< endl;

// char* a ;
//	string a;
//	getline(DNA, a);

	time = clock();
	//char* p = "11";
//buffer = "aaaaa";
	//char* p="aa";
	char* p = "GTGCTGACACATCCA";
	PuSu_match(buffer, p);
	KMP(buffer, p);
	cout << "KMP  Matched use time   " << time << "ms" << endl;
	time = clock();
	BM(buffer, p);
	time = clock() - time;
	cout << "BM  Matched use time  " << time << "ms" << endl;
	time = clock();
	Sunday(buffer, p);
	time = clock() - time;
	cout << "Sunday Matched use time  " << time << "ms" << endl;
	delete[] buffer;
	system("pause");
  	return 0;
}