#include"bPlus.h"
int main() {
	bPlus test;
	for (int i = 0; i <10000; ++i)
	{
		test.addKey(i);
		//cout << "insert success " << i << endl;
	}
	cout << "������ɣ� " << endl;
	Node* s = test.search(1);
	//while (s!=NULL)
	//{
	//	vector<int>::iterator it = s->key->begin();
	//	for (; it < s->key->end(); ++it)
	//		cout << *it << " ";
	//	s = s->next;
	//}
	cout << endl;
	cout << "����ɾ���� " << endl;
	cout << endl;
	for (int i = 199; i >35; i--)
	{
		test.deletekey(i);
		cout << "ɾ�� " << i << " �ɹ���" << endl;
	}
	system("pause");
	return 0;
}