#include "RTree.h"
#include<math.h>
RTree::RTree()
{
	M = 4;
	(M % 2 == 0) ? (m = M / 2) : (m = M / 2 + 1);
	Root = NULL;
}


Node* RTree::ChooseLeaf(Rectangle re)
{
	Node* T = Root;
	if (T->child.size()==0)//���T��Ҷ�ӽ�㣬��ֱ�ӷ���;
		return T;
	Node* suit=T->child[0].child;//��������Ŀǰ�ҵ������ʺϵĽ��ָ��,��ʼ����һ��������Ϊ���;

	for (int i = 1; i < T->child.size(); i++)
	{

	}
}

void RTree::Insert(Rectangle re)
{
	
}


RTree::~RTree()
{
}
