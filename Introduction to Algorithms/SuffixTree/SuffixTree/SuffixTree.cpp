#include "SuffixTree.h"

SuffixTree::SuffixTree()
{
	activePoint.point = &root;
	activePoint.index = NULL;
	activePoint.length = 0;
	reminder = 0;
}

bool SuffixTree::find(char word)
{
	Node*start = activePoint.point;
	Node* current = activePoint.index;
	bool exist= false;
	if (current==NULL)//�����ǰ���Ϊ�գ���鿴����ĺ��ӽ��;
	{
		if (start->alph[word-'A']!=NULL)
		{
			activePoint.index = start->alph[word-'A'];
			activePoint.length++;
			exist = true;
		}
	}
	else if(word==current->words[activePoint.length])//��ǰ��߲�Ϊ��,���ڻ���Ͻ��в���;
	{
		activePoint.length++;
		exist = true;
		int a = (current->words).length();
		if (a==activePoint.length)//�����߳����Ѿ��ﵽ���һ���ַ�����	�����Ϊ�µĻռ;
		{
			activePoint.point = current;
			activePoint.index = NULL;
			activePoint.length = 0;
		}
	}
	else
	{
		exist = false;
	}
	return exist;
}

void SuffixTree::bulid(string str)
{
	myWords = str;
	int index = 0;
	int teleng= (myWords.length());
	for (; index < teleng; index++)
	{
		//��ȡҪ������ַ�;
		char word = myWords[index];
		if (find(word))//����Ƿ��е�ǰ�ַ�;
		{
			reminder++;
			continue;
		}
		if (reminder==0)//���û�в��ҵ����Ҵ����������Ϊ0����ֱ�Ӳ��뼴��;
		{
			Node* te = new Node;

			//�޸�;
			//string s(myWords, index);
			(te->words) = (myWords, index,teleng);
			
			activePoint.point->alph[te->words[0]-'A'] = te;
		}
		else//���reminder>0,��Ҫ���зָ�;
		{
			Node* splitNode = activePoint.index;
			//Ҫ�ָ�ı�Ϊ��ǰ�Ļ��;
			Node* te = new Node;
			//string s(activePoint.index->words, activePoint.length);
			//te->words = s;
			(te->words)=(activePoint.index->words, activePoint.length);
			activePoint.index->alph[(te->words)[0]-'A'] = te;
			//string ss(activePoint.index->words, 0, activePoint.length);
			//activePoint.index->words =ss;
			activePoint.index->words = (activePoint.index->words, 0, activePoint.length);
			Node* newnode = new Node;
			//string sss(myWords, index);//�����µĽ��;
			(newnode->words) = (myWords, index,myWords.length());// sss;

			splitNode->alph[(newnode->words)[0] - 'A'] = newnode;

			//�ָ����֮���չ��� 1 2 ���д���;

			if (&root==activePoint.point)//���������Ǹ����;
			{/*
			 1. ��������Ϊ��
			 2. ���û��Ϊ�²���ĵ�һ���ַ�
			 3. ����ȼ�һ��������������������������������������Ϊʲôû�����ֳ���
			 */
				//ע�⣡����
			}
			else if(activePoint.point->suffixNode==NULL)// �޺�׺�ڵ㣬���ڵ��Ϊroot
			{
				activePoint.point = &root;
			}
			else
			{
				// �����ڵ��Ϊ��ǰ��ڵ�ĺ�׺�ڵ�
				activePoint.point = activePoint.point->suffixNode;
			}
			// ��ߺͻ�߳��ȶ�����
			activePoint.index = NULL;
			activePoint.length = 0;
			// �ݹ鴦��ʣ��Ĵ������׺
			innerSplit(index, splitNode);
		}
	}//for;
}

void SuffixTree::innerSplit(int position, Node* prefixNode)
{
	// �˴�����ʣ�������ĺ�׺�Ŀ�ʼλ��
	//����������Ҫ����������׺(abx,bx,x)���Ѵ�����abx����ʣ��ba��x������������λ�þ���b��λ��
	int start = position - reminder + 1;
	// dealStart��ʾ���β���������Ҫ���в��ҵĿ�ʼ�ַ�λ�ã���Ϊ���ڹ���2�����ܳ���ͨ����׺�ڵ�ֱ���ҵ���ڵ�����
	// ��ͨ��ab�ڵ�ĺ�׺�ڵ㣬ֱ���ҵ��ڵ�b����ô��ʱ��activePoint(node[b], null, 0)��������Ҫ��node[b]��ʼ����x��dealStart��λ�þ���x��λ��
	int dealStart = start + activePoint.point->words.length() + activePoint.length;
	// ��dealStart��ʼ�������к�׺�ַ��Ƿ񶼴���(����ڻ��)
	for (int index = dealStart; index <= position; index++)
	{
		char w = myWords[index];
		if (find(w))//����ҵ���ǰ�ַ�����ֻ�����ӻ���ĳ���;
		{
			continue;		
		}
		Node* splitNode = NULL;
		if (activePoint.index==NULL)//��ǰ���Ϊ�գ���ֻҪ�ڻ����²���һ�����;
		{
			Node* node = new Node;
			//string s(myWords,index);
			node->words = myWords, index;// s;
			activePoint.point->alph[node->words[0]-'A'] = node;
		}
		else//��ʼ�ָ���;
		{
			splitNode = activePoint.index;
			Node* node = new Node;
			string s(splitNode->words,activePoint.length);
			node->words = splitNode->words, activePoint.length;// s;
			splitNode->alph[node->words[0] - 'A'] = node;
			for (int i = 0; i < 27; i++)
				node->alph[i] = splitNode->alph[i];
			splitNode->suffixNode = NULL;
			Node* newnode = new Node;
			//string ss(myWords, index);
			newnode->words = myWords, index;// ss;
			splitNode->alph[newnode->words[0] - 'A'] = newnode;
			//string sss(splitNode->words,0,activePoint.length);
			splitNode->words = splitNode->words, 0, activePoint.length;// sss;
			prefixNode->suffixNode = splitNode;//
		}
		reminder--;
		if (activePoint.point==&root)
		{

		}
		else if (activePoint.point->suffixNode==NULL)
		{
			activePoint.point = &root;
		}
		else
		{
			activePoint.point = activePoint.point->suffixNode;
		}

		activePoint.index = NULL;
		activePoint.length = 0;
		if (reminder>0)
		{
			innerSplit(position, splitNode);
		}
	}
}

SuffixTree::~SuffixTree()
{
}
