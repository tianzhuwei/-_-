#include "Graph.h"

void Graph::Init() //��ȡ�ļ�����ʮ������;
{
	fstream readfile("E:\\���ݼ�\\��������ݼ�\\2.txt");
	if (!readfile)
	{
		cout << "Can not open the file !" << endl;
		system("pause");
		exit(0);
	}
	string firstlevel;
	int vex_num = 0;
//	readfile >> firstlevel;
	getline(readfile, firstlevel);
	cout << firstlevel << endl;
	cout << "input the number of vex:";
	cin >> vex_num;
	cout << "input the souce node: ";
	cin >> souce_node;
	cout << "input the sinks_node: ";
	cin >> sinks_node;
	GraphHead.reserve(vex_num);

	for (int i = 0; i < vex_num; i++)
	{
		VexNode temp;
		temp.firstin = NULL;
		temp.firstout = NULL;
		GraphHead.push_back(temp);
		//GraphHead.at(i).firstin = NULL;
		//GraphHead.at(i).firstout = NULL;
	}
	while (!readfile.eof())
	{
		EdgeNode* edge_temp = new EdgeNode;
		readfile>>edge_temp->start_id;
		readfile >> edge_temp->end_id;
		readfile >> edge_temp->c;
		edge_temp->f = 0;
		edge_temp->nextin = NULL;
		edge_temp->nextout = NULL;//�߽����Ϣ�������;

		if (readfile.fail())//�����ж�ĩβ�Ƿ��п���;
			break;

		edge_temp->nextout=GraphHead.at(edge_temp->start_id).firstout ;//�������Ӹ������;
		GraphHead.at(edge_temp->start_id).firstout = edge_temp;
		edge_temp->nextin=GraphHead.at(edge_temp->end_id).firstin ;
		GraphHead.at(edge_temp->end_id).firstin = edge_temp;
	}//while;

	cout << "Read Over !" << endl;
}

int Graph::ifend() {//������������еĽ���Ƿ��вд�����;
	for (int i = 0; i < GraphHead.size()-2; i++)
	{
		if (e[link[i]] != 0)
			return link[i];
	}
	return -1;
}

void Graph::fenfaliuliang(int i )
{
	EdgeNode* temp1 = GraphHead.at(i).firstout;
	EdgeNode* temp2 = GraphHead.at(i).firstin;
	int nodeid;//�����洢��i�Ž����ص������Ǹ����;
	while (e[i]!=0)//ֻҪ i�Ž������ʣ��������Ҫ���зַ�;
	{
		//����ʲô���Խ��зַ��أ�;
		//���ոߵ�˳����з��ţ�����͵Ŀ�ʼ;
		//��Ͳ��һ�����ͨ������;
		if (temp1==NULL&&temp2==NULL)
		{
			//��������i�Ž��ĸ߶�;
			Relable(i);
			temp1 = GraphHead.at(i).firstout;
			temp2 = GraphHead.at(i).firstin;
			break;
		}
		if (temp1 != NULL) {
			nodeid = temp1->end_id;
		}
		else if(temp2!=NULL){
			nodeid = temp2->start_id;
		}
		if (h[i] = h[nodeid] + 1) {
			if (temp1!=NULL)
			{
				Push(i,temp1);
				temp1 = temp1->nextout;
			}
			else if(temp2!=NULL)
			{
				Push(i,temp2);
				temp2 = temp2->nextin;
			}
		}
	}//while;
}

void Graph::Relable(int i)
{

}

void Graph::Push(int st,EdgeNode* edge)
{
	//�����ж�st �Ǳߵ���㻹���յ�;
	if (st==edge->start_id)//��������;
	{
		if (edge->c-edge->f>e[st])//�������һ��ͨ��e[st];
		{
			edge->f = edge->f + e[st];
			e[edge->end_id] = e[edge->end_id] + e[st];
			e[st] = 0;
		}
		else
		{
			e[edge->end_id] = e[edge->end_id] + edge->c - edge->f;
			e[st] = e[st] - edge->c + edge->f;
			edge->f = edge->c;
		}
	}
	else //������յ������;
	{
		if (edge->f>e[st])
		{
			edge->f = edge->f - e[st];
			e[edge->start_id] = e[edge->start_id] + e[st];
			e[st] = 0;
		}
		else
		{
			e[st] = e[st] - edge->f;
			e[edge->start_id] = e[edge->start_id] + edge->f;
			edge->f = 0;
		}
	}
}

void Graph::Relabel_To_Front()
{
	//��h��ʼ��;
	h = new int[GraphHead.size()];
//	memset(h, 0, GraphHead.size() * sizeof(int));
	e = new float[GraphHead.size()];//��ǰ��ŵ�������ֵ�Ƕ���;
//	memset(h, 0, GraphHead.size() * sizeof(float));
	for (int i = 0; i < GraphHead.size(); i++)
	{
		h[i] = 0;
		e[i] = 0;
	}
	h[souce_node] = GraphHead.size() - 1;//Դ��ĸ߶�;
	link = new int[GraphHead.size() - 2];//��ʼ��link��������ų�ȥ ����Դ��֮������е�;
	for (int i = 0,j=0; i < GraphHead.size(); ++i) 
		if (i!=souce_node&&i!=sinks_node)
			link[j++] = i;

	EdgeNode* temp1= GraphHead[souce_node].firstout;
	while (temp1!=NULL)//Ԥ����;��Դ��ĳ���ȫ�����ͣ�
	{
		temp1->f = temp1->c;
		e[temp1->end_id] = (temp1->c);
		temp1 = temp1->nextout;
	}
	temp1 = NULL;
	int i;

	while (1) {//���Link���滹�вд��������ifend()���ض���;

		i = ifend();
		if (i==-1)
		{
			break;
		}
			//��λ�ڶ���i�Ĳд������ַ���ȥ,��ȫ���ַ���ȥ��һ��Ҳ��ʣ;
			int old = h[i];//i �Ŷ���ĵ�ǰ�߶�;
			EdgeNode* edge_temp=NULL;


			while (e[i] != 0) //ֻҪ�߻��вд�����;
			{
				EdgeNode* temp2 = GraphHead.at(i).firstout;
				EdgeNode* temp3 = GraphHead.at(i).firstin;
				int min_high =-1;//���������С�߶ȵĶ���;        ��ɾ��
				while(temp2!=NULL&&e[i]!=0)
				{
					int endid = temp2->end_id;
					if (h[endid]<h[i]&&temp2->f<temp2->c)
					{
						Push(i, temp2);//��endid�Ž������;
					}
					temp2 = temp2->nextout;
					//if ((temp2->f) < (temp2->c ))
					//{
					//	min_high = temp2->end_id;
					//	break;
					//}
				}
				while (temp3!=NULL&&e[i]!=0)
				{
					int startid = temp3->start_id;
					if (h[startid]<h[i]&&temp3->f>0)
					{
						Push(i, temp3);
					}
					temp3 = temp3->nextin;
				}
				if (e[i]!=0)
				{
					h[i]++;
				}
				/*
				while (temp2!=NULL)
				{
					if (temp2->f < temp2->c  && h[min_high]>=h[temp2->end_id])
					{
						min_high = temp2->end_id;
						edge_temp = temp2;
					}
					temp2 = temp2->nextout;
				}
				if (min_high==-1 && (temp3!=NULL))
				{
					while (temp3->f <= 0)
					{
						temp3 = temp3->nextin;
					}
					min_high = temp3->start_id;
					while (temp3!=NULL)
					{
						if (temp3->f > 0 && h[min_high]>=h[temp3->start_id] )
						{
							min_high = temp3->start_id;
							edge_temp = temp3;
						}
						temp3 = temp3->nextin;
					}
				}
				//Ŀǰ�ҵ����Դ��͵���͵�;
					h[i] = h[min_high] + 1;
					if (i==edge_temp->start_id)//��������� i -> min_high ����;
					{
						if (e[i]>(edge_temp->c - edge_temp->f))
						{
							e[i] = e[i] - (edge_temp->c - edge_temp->f);
							e[edge_temp->end_id] = e[edge_temp->end_id] + (edge_temp->c - edge_temp->f);
							edge_temp->f = edge_temp->c;
						}
						else
						{
							edge_temp->f += e[i];
							e[edge_temp->end_id] += e[i];
							e[i] = 0;
						}
					}
					else// ������ min_high -> i ���� ;
					{
						if (e[i]>edge_temp->f)
						{
							e[i] = e[i] - edge_temp->f ;
							e[edge_temp->start_id] = edge_temp->f;
							edge_temp->f = 0;
						}
						else
						{
							edge_temp->f = edge_temp->f - e[i];
							e[edge_temp->start_id] = e[i];
							e[i] = 0;
						}
					}
			*/	
			}		
			
			//�޸�������Ϊǰ��������ǩ����;
			if (old!=h[i])//�߶ȷ����ı�;
			{
				int j=0;
				while (link[j]!=i)//�ҵ�i �Ž���������е�λ��;
					j++;
				int tt = link[0];
				link[0] = link[j];
				link[j] = tt;
			}
	}//while(1);

	std::cout << "The maximum flow is " << e[sinks_node] << endl;
}

Graph::Graph()
{
	Init();
}


Graph::~Graph()
{
}
