#include "Graph.h"

void Graph::readfile() {
	//string filename="E:\\new_data\\weightest.txt";
	string filename = "E:\\new_data\\OLRoad.txt";
	ifstream readfile(filename);
	if (!readfile)
	{
		cout << "Can not open the file ! " << endl;
		system("pause");
		exit(0);
	}
	int nodeNum, edgeNum;
	readfile >> nodeNum;//���Ȼ�ȡ ͼ��  �������  ��  ����;
	readfile >> edgeNum;
	GraphHead.reserve(nodeNum);//Ϊͷ���������� nodeNum ���ռ�;
	EdgeNode edgetemp;
	int start,outputdegree;
	char douhao;
	while (!readfile.eof())
	{
		readfile >> start;
		readfile >> outputdegree;
		if (readfile.fail())
			break;
		vector<EdgeNode>*vetemp=new vector<EdgeNode> ;
		for (int i = outputdegree; i >0 ; --i)
		{
			readfile >> edgetemp.end;
			readfile >> douhao;
			readfile >> edgetemp.weight;
			(*vetemp).push_back(edgetemp);
		}
		GraphHead.push_back(vetemp);
	}
}

Graph::Graph()
{
	cout << "Start read ..."<<endl;
	clock_t time = clock();
	readfile();
	time = clock() - time;
	cout << "Read Over ! use time "<<time<<" ms" << endl;
}

void Graph::Dijkstra() {
	int MAX = 99999;
	int S = 0;
	//cout<<"����Դ�� S ��� �� "<<endl;
	//cin>>S;
	double* dis		= new double[GraphHead.size()];//�����洢Դ��S���������±���ľ��룬��ʼ���Ϊ���S��Ϊ0;
	for (int i = 0; i < GraphHead.size(); ++i)
		dis[i] = MAX;
	int* path	= new int[GraphHead.size()];//�����洢Դ��S���������±����·����Ҳ������һ���������һ������ʼֵΪ -1 ;
	bool* set		= new bool[GraphHead.size()];//������Ǹ������±����Ƿ��Ѿ��������·������ʼΪ0��S��Ϊ1;
	vector<EdgeNode>* tem;
	for (int i = 0; i < GraphHead.size(); i++)
	{
		if (i==S)
		{
			tem = GraphHead.at(i);
			for (int j = 0; j < tem->size(); ++j) {
				dis[tem->at(j).end] = tem->at(j).weight;
				path[tem->at(i).end] = i;
			}
		}
		set[i]		= 0;
		path[i] = -1;
	}//for;
	set[S] = 1;
	dis[S] = 0;
	int u;//������¼��Сֵ;
	double min;
	for (int i = 0; i < GraphHead.size(); ++i) {
		min = MAX;
		
		for (int j = 0; j < GraphHead.size(); ++j) {
			if (set[j] == 0 && dis[j] < min)
			{
				u = j;
				min = dis[j];
			}//if;
		}
				set[u] = 1;
				tem = GraphHead.at(u);
				//for (int j = 0; j < GraphHead.size(); ++j) {
				for (int j = 0; j < tem->size(); j++)
				{
					if (dis[tem->at(j).end] > dis[u]+tem->at(j).weight)
					{
						dis[tem->at(j).end] = tem->at(j).weight;
						path[j] = i;
					}
				}
		}//for;
	}

void Graph::BellmanFord() {
	//��ʼ��;
	//�ɳڲ���;
	//��鸺Ȩ��·;
	int MAX = 99999;
	int S = 0;
	//cout << "����Դ�� S " << endl;
	//cin >> S;
	//��ʼ��;
	int *dis = new int[GraphHead.size()];
	for (int i = 0; i < GraphHead.size(); i++)
	{
		dis[i] = MAX;
	}
	dis[S] = 0;
	int *pre = new int[GraphHead.size()];
	memset(pre, -1, GraphHead.size());
	pre[S] = S;
	//�ɳڲ���;
	vector<EdgeNode>* tem;
	for (int i = 0; i < GraphHead.size(); i++)
	{
		tem=GraphHead.at(i);
		int end;
		double weight;
		for (int j = 0; j < (tem->size()); ++j) {
			end = (*tem).at(j).end;
			weight = (*tem).at(j).weight;
			if (dis[end]>dis[i]+weight)
			{
				dis[end] = dis[i] + weight;
				pre[end] = i;
			}
		}
	}//for;
	//��Ȩ��·���;
	for (int i = 0; i < GraphHead.size(); i++)
	{
		tem = GraphHead.at(i);
		int end;
		double weight;
		for (int j = 0; j < tem->size(); j++)
		{
			end = (*tem).at(j).end;
			weight = (*tem).at(j).weight;
			if (dis[end]>weight+dis[i])
			{
				cout << "��ͼ���ڸ�Ȩ��·��" << endl;
				break;
			}
		}
	}//for
	int path = 100;
//cout << "����Ŀ��� " << endl;
//	cin >> path;
	while (S!=pre[path])
	{
		cout << path << " ";
		path = pre[path];
	}
	if (S==pre[path])
	{
		cout << S << " ";
	}
}


Graph::~Graph()
{
	for (size_t i = 0; i < GraphHead.size(); i++)
	{
		GraphHead.at(i)->~vector();
	}
	GraphHead.~vector();
}
