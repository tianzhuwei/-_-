#include "SuffixTree.h"

Node SuffixTree::InitSuffixTree() {
	words = "abcd";
	addChar(&head, words);
	return head;
}
bool SuffixTree::find(char word) {
	Node* currentNode = activePoint.active_node;
	EdgeNode* currentEdge = activePoint.active_edge;
	bool exist = false;
	if (currentEdge==NULL)//�����ǰ���ΪNULL�Ļ�;��ӻ�����ӽ����ң�
	{
		if (currentNode->alph[word-'A']!=NULL)
		{
			exist = true;
			activePoint.active_length++;
			activePoint.active_edge = currentNode->alph[word - 'A'];
		}//if
	}//if
	 //����л�ߣ����ڻ���ϲ��� ;
	else if (words[currentEdge->startNum+activePoint.active_length]==word)//����ڻ������ָ�����ַ� word�Ƿ���ͬ;
	{//����ע��һ��;
		activePoint.active_length++;
		exist = true;
		if (activePoint.active_length==currentEdge->endNum)
		{// �����ߵĳ����Ѵﵽ��ߵ����һ���ַ����򽫻����Ϊ��ߣ�ͬʱ�����Ϊnull��������Ϊ0
			activePoint.active_node = currentEdge->nextNode;
			activePoint.active_edge = NULL;
			activePoint.active_length = 0;
		}
		else
		{
			exist = false;
		}
	}
	return exist;
}

void SuffixTree::innerSplit(int position, Node* prefixNode) {
	// �˴�����ʣ�������ĺ�׺�Ŀ�ʼλ��
	//����������Ҫ����������׺(abx,bx,x)���Ѵ�����abx����ʣ��ba��x������������λ�þ���b��λ��
	int start = position - reminder + 1;
	// dealStart��ʾ���β���������Ҫ���в��ҵĿ�ʼ�ַ�λ�ã���Ϊ���ڹ���2�����ܳ���ͨ����׺�ڵ�ֱ���ҵ���ڵ�����
	// ��ͨ��ab�ڵ�ĺ�׺�ڵ㣬ֱ���ҵ��ڵ�b����ô��ʱ��activePoint(node[b], null, 0)��������Ҫ��node[b]��ʼ����x��dealStart��λ�þ���x��λ��
	//int dealStart = start + activePoint.point.chars.length + activePoint.length;
	int delstart=start+activePoint.active_length;//!!!!!!!!!!!!!!!!!!!!������ע��
	for (int index = delstart; index <= position; index++) {
		if (find(words[position]))
		{
			continue;
		}
		Node* splitNode = new Node;
		EdgeNode *edge_temp = new EdgeNode;
		if (activePoint.active_edge==NULL)//˵��û���ҵ���ߣ���ôֻ��Ҫ�ڻ�ڵ��²���һ���ڵ㼴��
		{
			activePoint.active_node->alph[words[position] - 'A'] = edge_temp;
			edge_temp->startNum = activePoint.active_length;
			edge_temp->endNum = activePoint.active_length + 1;
			edge_temp->nextNode = splitNode;
		}
		else
		{//��ʼ�ָ�;
			activePoint.active_edge->nextNode = splitNode;
			splitNode->alph[words[position]] = edge_temp;
			edge_temp->startNum = delstart;
			edge_temp->endNum = activePoint.active_edge->endNum;
			activePoint.active_edge->endNum = delstart - 1;
			prefixNode->suffixNode = splitNode;
		}
		reminder--;
		if (&head == activePoint.active_node)//��������Ǹ����Ļ�;
		{
			/*
			1. ���㱣��Ϊ�����
			2. ���û��Ϊ
			*/
		}//���չ���3����;
		else if (activePoint.active_node->suffixNode == NULL)// �޺�׺�ڵ㣬���ڵ��Ϊroot
		{
			activePoint.active_node = &head;
		}
		else
		{// �����ڵ��Ϊ��ǰ��ڵ�ĺ�׺�ڵ�
			activePoint.active_node = activePoint.active_node->suffixNode;
		}//else;
		 // ��ߺͻ�߳��ȶ�����
		activePoint.active_length = 0;
		activePoint.active_edge = NULL;
		//�ݹ鴦��ʣ��Ĵ������׺;
		if (reminder>0)//;���reminder < 0 ����Ҫ�ٽ��зָ�
		{
			innerSplit(position, splitNode);
		}		
	}
}
void SuffixTree::addChar(Node* head, string words) {
	int position = 0;
	//�Ի������г�ʼ��;
	activePoint.active_edge = NULL;//��ı߳�ʼ��Ϊ�ձ�;
	activePoint.active_length = 0;//����ȳ�ʼ��Ϊ0;
	activePoint.active_node = head;//�����ʼ��Ϊ��׺���ĸ����;

	//��ÿ�����迪ʼʱʣ���׺��������������Ϊ1;  
	//�� �� �� ����ô��;ʲô��TM�ġ�ÿһ�����迪ʼʱ��������Ϊ 0��
	reminder = 0;//��ʼ��ʱ�ߵĸ���Ϊ 0 ��;
	for (; position < words.length(); ++position)//�������ҵ�˳���ַ����е��ַ���ӵ���׺��;
	{
		if (find(words[position]))//����ҵ���ǰ�ַ�;
		{
			reminder++;
			continue;
		}
		// �����ڵĻ������reminder==0��ʾ֮ǰ�ڸ��ַ�֮ǰδʣ��������������ĺ�׺�ַ�������ֱ�Ӳ���ú�׺�ַ�����
		if (reminder==0)
		{
			// ֱ���ڵ�ǰ��ڵ����һ���ڵ㼴��
			Node* Nodetemp = new Node;
			EdgeNode* Edge_temp = new EdgeNode;
			Edge_temp->startNum = activePoint.active_length;
			Edge_temp->endNum = ++activePoint.active_length;
			activePoint.active_node->alph[words[position]-'A'] = Edge_temp;
		}
		else//���	reminder > 0,˵�����ַ�֮ǰ���ڻ�����ַ�������Ҫ���зָ�;
		{
			// ���ָ�Ľڵ㼴Ϊ���(active_edge);
			Node* node_temp = new Node;
			EdgeNode* edge_temp = new EdgeNode;
			edge_temp->endNum = activePoint.active_edge->endNum;
			edge_temp->startNum = activePoint.active_edge->startNum + reminder;
			edge_temp->nextNode = node_temp;
			activePoint.active_edge->nextNode = node_temp;
			node_temp->alph[words[position]-'A'] = edge_temp;

			// �ָ����֮������ݹ���1�͹���2�������ֶԴ�
			// ���չ���1���д���
			if (head==activePoint.active_node)//��������Ǹ����Ļ�;
			{
				/*
				1. ���㱣��Ϊ�����
				2. ���û��Ϊ
				*/
			}//���չ���3����;
			else if (activePoint.active_node->suffixNode==NULL)// �޺�׺�ڵ㣬���ڵ��Ϊroot
			{
				activePoint.active_node = head;
			}
			else
			{// �����ڵ��Ϊ��ǰ��ڵ�ĺ�׺�ڵ�
				activePoint.active_node = activePoint.active_node->suffixNode;
			}//else;
			 // ��ߺͻ�߳��ȶ�����
			activePoint.active_length = 0;
			activePoint.active_edge = NULL;
			//�ݹ鴦��ʣ��Ĵ������׺;
			innerSplit(position, node_temp);
		}//else
	}
	EdgeNode edge1;
	Node* node1=new Node;
	edge1.startNum = 0;
	edge1.endNum = position;
	edge1.nextNode = node1;
}

SuffixTree::SuffixTree()
{
}


SuffixTree::~SuffixTree()
{

}
