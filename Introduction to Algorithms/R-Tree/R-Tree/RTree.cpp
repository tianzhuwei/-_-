#include "RTree.h"
#include<math.h>
RTree::RTree()
{
	M = 4;
	(M % 2 == 0) ? (m = M / 2) : (m = M / 2 + 1);//���� M ����� m ;
	Root = new Node;
}

Node* RTree::ChooseLeaf(Rectangle re)
{
	Node* T = Root;
	if (T->child.size()==0||T->child[0].child==NULL)//���T��Ҷ�ӽ�㣬��ֱ�ӷ���;
		return T;

	double area_suit;
	double area_current;
	Node* suit;
	while (T->child[0].child!=NULL)//û�к��ӽ��ʱ��ΪҶ�ӽ��;
	{
		suit = T->child[0].child;//��������Ŀǰ�ҵ������ʺϵĽ��ָ��,��ʼ����һ��������Ϊ���;
		area_suit = areaIncrease(suit->region, re);
		int te = (T->child).size();
		for (int i = 0; i <te; i++)
		{
			//[ѡ������] ���N����Ҷ�ӽ�㣬�����N�еĽ��
			//�ҳ����E.Iʱ������С�Ľ�㣬���Ѹý�㶨��ΪF��
			//����ж�������Ľ�㣬��ôѡ�������С�Ľ�㡣
			area_current = areaIncrease(T->child[i].region, re);
			if (area_suit > area_current)//;
			{
				suit = T->child[i].child;
				area_suit = areaIncrease(suit->region, re);
			}
			else if (area_suit == area_current)//������������һ������ѡ�������С��;
			{
				if (area_compute(suit->region, re) > area_compute(T->child[i].region, re))
				{
					suit = T->child[i].child;
					area_suit = areaIncrease(suit->region, re);
				}
			}//else;
		}//for;
		T = suit;
	}
	return T;
}

inline double RTree::areaIncrease(Rectangle r1, Rectangle r2)
{
	double old_area = (r1.rightPoint_x - r1.leftPoint_x)*(r2.rightPoint_y - r2.leftPoint_y);
	double new_area = area_compute(r1, r2);
	return (new_area - old_area);
}

inline double RTree::area_compute(Rectangle r1, Rectangle r2)
{
	double x1, x2, y1, y2;
	r1.leftPoint_x > r2.leftPoint_x ? (x1 = r2.leftPoint_x) : (x1 = r1.leftPoint_x);
	r1.leftPoint_y > r2.leftPoint_y ? (y1 = r2.leftPoint_y) : (y1 = r1.leftPoint_y);

	r1.rightPoint_x > r2.rightPoint_x ? (x2 = r1.rightPoint_x) : (x2 = r2.rightPoint_x);
	r1.rightPoint_y > r2.rightPoint_y ? (y2 = r1.rightPoint_y) : (y2 = r2.rightPoint_y);
	double area = (x2 - x1)*(y2 - y1);
	return area;
}

inline void RTree::changeRegion(Rectangle &r1, Rectangle r2)
{
	r1.leftPoint_x > r2.leftPoint_x ? (r1.leftPoint_x = r2.leftPoint_x) : (1);
	r1.leftPoint_y > r2.leftPoint_y ? (r1.leftPoint_y = r2.leftPoint_y) : (1);
	r1.rightPoint_x < r2.rightPoint_x ? (r1.rightPoint_x = r2.rightPoint_x) : (1);
	r1.rightPoint_y < r2.rightPoint_y ? (r1.rightPoint_y = r2.rightPoint_y) : (1);
}

void RTree::splitNode(Node* node)
{ 
	//	����ԭ��ʹ�ø��Ǹ��½��ľ�����С              �ص�ע�⣡�����������������������ؼ�
	//����д����˵�����ӽ���е����һ��Ϊ���²���Ľ�㣬��֤���½�㹹�ɵĴ���������С����;
	if (node->parent==NULL)//�����ǰ����Ǹ���㣬��Ҫ��������һ�������;
	{
		Node* newroot = new Node;
		Node* split = new Node;
		split->child.push_back(node->child.back());
		node->child.pop_back();
		changeRegion(split->region, split->child.back().region);
		if (split->child.back().child!=NULL)
		{
			split->child.back().child->parent = split;//�����ӽ��ĸ��׽��ָ���µĸ���;
		}
		childNode suit = node->child[0];
		while ((split->child.size()) < m) {
			int a=0;
			for (int i =0 ; i < m; i++) {
				if (area_compute(split->region,suit.region)>area_compute(split->region,node->child[i].region))
				{
					a = i;
					suit = node->child[i];
				}
			}//for;
			split->child.push_back(suit);
			changeRegion(split->region, split->child.back().region);
			if (split->child.back().child!=NULL)
			{
				split->child.back().child->parent = split;//�����ӽ��ĸ��׽��ָ���µĸ���;
			}
			node->child.erase(node->child.begin() + a);	//��node �е�suit ɾ��;
		}//while;
		node->parent = newroot;
		//����node ��regison ��
		node->region = node->child[0].region;
		for (int i = 1; i < node->child.size(); i++) {
			changeRegion(node->region, node->child[i].region);
		}

		//�����µĽ��;
		split->parent = newroot;
		node->parent = newroot;
		Root = newroot;
		newroot->region = node->region;
		childNode te;
		te.child = node;
		te.region = node->region;
		newroot->child.push_back(te);

		te.child = split;
		te.region = split->region;
		newroot->child.push_back(te);
		changeRegion(newroot->region, te.region);

	}//if;
	else//����ָ�Ľ�㲻�Ǹ����;
	{
		/*
		����ǰ���ָ�Ϊ������㣬
		������һ��split���;���ҽ�node �е����һ��Ԫ�أ����²����Ԫ�أ����뵽split��
		��split���뵽���׽����
		*/
		Node* split = new Node;
		split->child.push_back(node->child.back());
		node->child.pop_back();
		changeRegion(split->region, split->child.back().region);
		if (split->child.back().child!=NULL)
		{
			split->child.back().child->parent = split;
		}
		childNode suit;
		while (split->child.size()<m)
		{
			int a=0;
			suit = node->child[0];
			//for (int i = 0; i < m; i++)
			for (int i = 0; i < node->child.size(); i++)// i Ӧ��С�� node ����еĸ���
			{
				if (area_compute(split->region, suit.region) > area_compute(split->region, node->child[i].region))
				{
					a = i;
					suit = node->child[i];
				}
			}//for
			split->child.push_back(suit);
			changeRegion(split->region, split->child.back().region);
			if (split->child.back().child!=NULL)
			{
				split->child.back().child->parent = split;
			}
			node->child.erase(node->child.begin() + a);
		}//while;
		//����node regison��
		node->region = node->child[0].region;
		for (int i = 1; i < node->child.size(); i++)
		{
			changeRegion(node->region, node->child[i].region);
		}
		//��split�����뵽���׽��;
		suit.child = split;
		suit.region = split->region;
		node->parent->child.push_back(suit);
		split->parent = node->parent;
		changeRegion(node->parent->region, split->region);

		//���¸��׽��������С;
		updateRegion(node);
		updateRegion(split);

		//������֮����ɸ��׽���Ԫ�ظ������ӣ��Ƿ���Ҫ�ٽ��з���;
		if (node->parent->child.size()>M)
		{
			splitNode(node->parent);
		}
	}//else
}

void RTree::Insert(Rectangle re)
{
	Node* leafNode = ChooseLeaf(re);//�ҵ�Ҫ�����Ҷ�ӽ��;
	//���ҵ�˼·�����Ȳ���֮����ȥ�ж��ǲ����ƻ�������;
	childNode te;
	te.region = re;
	leafNode->child.push_back(te);
	//�޸�leafNode �� region ��;
	changeRegion(leafNode->region, re);
	if ((leafNode->child.size())>M)//����R���Ľ���֮��Ҫ���зָ�;
	{
		splitNode(leafNode);
	}
	else
	{
		updateRegion(leafNode);
	}
}

inline bool RTree::RectangleEqual(Rectangle r1, Rectangle r2)//�����ж����� ���� �ǲ�����ͬ;
{
	if (r1.leftPoint_x!=r2.leftPoint_x||r1.leftPoint_y!=r2.leftPoint_y||r1.rightPoint_x!=r2.rightPoint_x||r1.rightPoint_y!=r2.rightPoint_y)
	{
		return false;
	}
	else
		return true;
}

void RTree::updateRegion(Node* node)// ��һ�������С�ı�֮�����θ��¸��׽��������С;
{
	while (node!=NULL)
	{
		node->region = node->child[0].region;
		for (int i = 0; i < node->child.size(); i++)
		{
			changeRegion(node->region, node->child[i].region);
		}
		node = node->parent;
	}
}

void RTree::Condense(Node * LeafNode)
{
	if (LeafNode->child.size()<m)//�����ǰ��㺢�Ӹ���С���� m ;
	{
		if (LeafNode==Root)//������LeafNode �Ǹ���㣬Ҫִ���µ��жϱ�׼;
		{

		}//if
		else//�Ǹ���㣬�Һ��Ӹ���ҪС�� m ���� LeafNode������һ��ջQ��;
		{
			Q.push(LeafNode);//����ջQ ����ɾ���ڸ��׽���е�λ��;
			int i = 0;
			Node* parent = LeafNode->parent;
			while (parent->child[i].child!=LeafNode)
			{
				i++;
			}
			parent->child.erase(parent->child.begin()+i);

			Condense(parent);//��ΪLeafNode���Ǹ���㣬�����丸�׽����һ�����ڵ�;

			//�� parent �ĺ�����ѡ��һ����LeafNode����,�п��ܻ���ɷ���;
			childNode* temp=choseNodeToMerge(parent, Q.top());
			Q.pop();
			if (temp->child->child.size()>M)//�������֮��������� M �ˣ���Ҫ���N�����з��Ѳ���;
			{
				splitNode(temp->child);//;
			}
		}//else

	}//if

}

childNode * RTree::choseNodeToMerge(Node * Parent, Node * mergeNode)
{
	int num = Parent->child.size();
	childNode suit=Parent->child[0];
	double inc = areaIncrease(suit.region, mergeNode->region);
	for (int i = 0; i < num; i++)
	{
		if (areaIncrease(Parent->child[i].region,mergeNode->region)<inc)
		{
			suit = Parent->child[i];
			inc = areaIncrease(suit.region, mergeNode->region);
		}
		else if (areaIncrease(Parent->child[i].region, mergeNode->region)==inc)
		{
			//ȡһ�����С��
			if (area_compute(suit.region,mergeNode->region)>area_compute(Parent->child[i].region,mergeNode->region))
			{
				suit = Parent->child[i];
			}
		}//elseif
	}//for
	return &suit;
}

void RTree::Delete(Rectangle re) 
{
	Node* leafNode = ChooseLeaf(re);//�ҵ�re ���ڵ�Ҷ�ӽ��;
	//��ɾ�� re ��
	bool ifExist = false;
	for (int i = 0; i < leafNode->child.size(); i++)
	{
		if (RectangleEqual(re,leafNode->child[i].region))
		{
			//ɾ��re;
			ifExist = true;
			leafNode->child.erase(leafNode->child.begin() + i);
			updateRegion(leafNode);
			break;
		}
	}//for
	if (!ifExist)
	{
		cout << "can not find the re " << endl;
		return ;
	}

	//�Ѿ�ɾ�� re ����û�и��� region ��;
	if (leafNode->child.size()<m)//������ĸ���С����m֮����Ҫ��leafNode ʣ��Ľ�����²���;
	{
//			�ٻ����Ѿ���һ������
/*
		��������Ƚϸ���
		������ֺ��Ӹ���������R�����ʺ󣬻Ὣ��ǰ����R�������ߣ�����һ�������У�Ҫ��Ҫ���������أ�������һֱ�ҵ��������ʻ����ҵ������
		Ȼ�������еĽ����ԭ�����ڲ��еĽ��ϲ�
		���޺�����鷳������

			���������д
			����ͬ�����ߵͣ�����ɵX������
*/

	}


}


RTree::~RTree()
{
}
