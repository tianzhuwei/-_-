#include "Graph.h"
#include <queue>
#include <vector>
#include <stack>
#include <time.h>
#include<cstdlib>
//�����������;����ʹ�õ���STL�е�queue��ʵ�ֵĶ��У���֪���᲻����ٶȲ���Ӱ�죬�����Զ���������Ƚ������Ƿ���ڲ���
  
void Graph::BFS(){
	clock_t time=clock();
	queue<int> qu;//�����洢���Ķ���;
	//vector<int> test;//�����洢������������ķ���˳��;
	//if (head!=NULL)
	for(int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)
			{
			qu.push(i);
			head[i].statu=true;
			Edge* temp;
			while(!qu.empty()){
				temp=head[qu.front()].next;//������Ҫ���Ǽ��������е��Ǹ�Ԫ��;
				qu.pop();
				//cout<<qu.back()<<endl;//.back()�������ص�ֵΪ�����е����һ��;
				//	cout<<qu.front()<<endl;
				while(temp!=NULL){
					if (head[temp->vName].statu==false)//��ǰ����û�б����ʹ����������;
					{
						qu.push(temp->vName);
						head[temp->vName].statu=true;
					}
					temp=temp->nextEdge;
				}
			//	test.push_back(qu.back());
			}//while;
		}//if;
	}//for;
	time=clock()-time;
	cout<<"Complate! use time : "<<time<<endl;
	for (int i=0;i<vex_num;++i)
	{
		if (head[i].statu==false)
		{
			cout<<"BFS�����⣡����"<<i<<endl;
			system("pause");
		}
	}
}

void Graph::BFS_self(){
	clock_t time=clock();
	int* qu;
	qu=new int[vex_num+2];
	for (int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)
		{
			Edge* temp;
			int j;//;
			int rear=0,front=0;
			rear=(rear+1)%vex_num;
			qu[rear]=i;
			head[i].statu=true;
			while(front!=rear){
				front=(front+1)%vex_num;
				j=qu[front];
				temp=head[j].next;
				while(temp!=NULL){
					if (!head[temp->vName].statu)
					{
						head[temp->vName].statu=true;
						rear=(rear+1)%vex_num;
						qu[rear]=temp->vName;
					}
					temp=temp->nextEdge;
				}
			}
	}
	}//for;
	delete[] qu;
	time=clock()-time;
	cout<<"BFS_self use time: "<<time<<endl;
	for (int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)
		{
			cout<<i<<endl;
		}
	}
}

  //������������ݹ�;
void Graph::DFS_Sin(int v){
	Edge* e;
	head[v].statu=true;
	e=head[v].next;
	while(e!=NULL){
		if (!head[e->vName].statu)
		{
			DFS_Sin(e->vName);
		}
		e=e->nextEdge;
	}
}

void Graph::DFS_digui(){
	clock_t time=clock();
	for(int i=0;i<vex_num;++i){
		if (!head[i].statu)
		{
			DFS_Sin(i);
		}
	}
	time=clock()-time;
	cout<<"use DFS_digui time: "<<time<<endl;
}

void Graph::DFS_self(){
	clock_t time=clock();
	int* st;
	long big=2*edge_num;
	st=new int[big];
	int top=-1;
	for (int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)
		{
			top++;
			st[top]=i;
			Edge * temp=NULL;
			while(top!=-1){
				if (!head[st[top]].statu)
				{
					head[st[top]].statu=true;
					temp=head[st[top]].next;
					top--;
					while(temp!=NULL){
						top++;
						st[top]=temp->vName;
						temp=temp->nextEdge;
					}//while
				}//if
				else{
					top--;
				}
			}//while
		}
	}
	time=clock()-time;
	cout<<"DFS�ǵݹ��Զ���ջ��ʽ��ʱ��"<<time<<endl;
}
//������������ǵݹ�;
void Graph::DFS(){
	clock_t time=clock();
	stack <int> st;
	for (int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)//���û�б����ʹ�;
		{
			st.push(i);
			//head[i].statu=true;
			Edge* temp;
			while(st.empty()){
				if (!head[st.top()].statu)
				{
					head[st.top()].statu=true;
					temp=head[st.top()].next;
					st.pop();
					while(temp!=NULL){
						st.push(temp->vName);
					}
				}else{
					st.pop();
				}
			}//while;
		}//if;
	}//for;
	time=clock()-time;
	cout<<"DFS�ǵݹ�STLջ��ʽ��ʱ��"<<time<<endl;
}

/*
void Graph::DFS(){
	clock_t time=clock();
	stack<int> st;
	for(int i=0;i<vex_num;++i){
		if (head[i].statu==false)
		{
			st.push(i);
			head[i].statu=true;
			Edge* temp;
			while(!st.empty()){
				//assert(st.top());	//ʹ��cstdlib��ͷ�ļ�;
				temp=head[st.top()].next;//����д����ʱ�����ıض�Ҫ��;
				///��Ҫ�Ǿ���Ϊ���Ǵ�ջ�г���֮���Ǵӵ�ǰ��������ĵ�һ���߿�ʼɨ��ģ�
				///Ҳ����˵ÿ�������Ƕ�Ҫ���ʶ�Σ���������һ�Σ�������ʵ���ܳ����ʱ�����ĵ�ʱ��Ҫ���Ķ��
				while(temp!=NULL && head[temp->vName].statu==true)
					temp=temp->nextEdge;
				if (temp==NULL)
				{
					st.pop();
				}else{
					head[temp->vName].statu=true;
					st.push(temp->vName);
				}
			}//while;
		}//if;
	}
	time=clock()-time;
	cout<<"DFS use time : "<<time<<endl;
	for(int i=0;i<vex_num;++i){
		if (!head[i].statu)
		{
			cout<<"DFS�����⣡��"<<endl;
			system("pause");
		}
	}
}
*/


//�������Զ�ȡtxt�ļ��ĺ������������������ԣ���������������ʱ��û��ʹ��;
void Graph::read(){
// 	FILE * fp=fopen("E:/xmark.txt","r");
// 	fscanf(fp,"%d",&vex_num);
// 	cout<<"���ĸ�����"<<vex_num<<endl;
// 	//ArcNode* te;
// 	head=new ArcNode[vex_num];
// 	for (int i=0;i<vex_num;++i)
// 	{
// 		head[i].next=NULL;
// 	}
// 	//createVertexArry();
// 	int start,end;
// 	while(fscanf(fp,"%d",&start)!=EOF){
// 		fscanf(fp,"%d",&end);
// //		cout<<flush;
// 		//cout<<start<<" "<<end<<endl;
// 		//addedge_direction(start,end,0);
// 		Edge *e;
// 		e=new Edge;
// 		e->weight=0;
// 		e->vName=end;
// 		e->nextEdge=head[start].next;
// 		head[start].next=e;
// 	}
}

//��������һ������ͼ;
void Graph::creat_Linklist_Nodirection(){
	//ifstream read("E:/test.txt");
	//ifstream read("E:/xmark.txt");
	edge_num=0;
	ifstream read("E:/uniprot150m.txt");
	if (!read)
	{
		system("pause");
	}
	string tem;
	getline(read,tem);
	istringstream iss(tem);
	iss >> vex_num;
	cout<<"���ĸ�����"<<vex_num<<endl;
	createVertexArry();
	int start,end;
	int weight=0;

	//for(int i=0 ; i<edge_num;++i){
	while(!read.eof()){
		getline(read,tem);
		if (tem=="#")
		{
			continue;
		}
		if (tem!="")
		{
			int pos=tem.find(" ",0);
			istringstream st(tem.substr(0,pos));
			st>>start;
			//cout<<start<<endl;
			istringstream stt(tem.substr(pos,tem.length()));
			stt>>end;
			//cout<<end<<endl;
			addedge_nodirection(start,end,weight);
			edge_num++;
		}

	}
	read.close();
	cout<<"����ͼ����洢��ɣ�"<<endl;
	//inputvexnum();
	//createVertexArry();
	//inputedgenum();
	//addedgeinfo_nodirection();
}


//��������һ������ͼ;
void Graph::creat_Linklist_Direction(){
	//ifstream read("E:/xmark.txt");
	edge_num=0;
	ifstream read("E:/uniprot150m.txt");
	if (!read)
	{
		return;
	}
	string tem;
	getline(read,tem);
	istringstream iss(tem);
	iss >> vex_num;
	cout<<"���ĸ�����"<<vex_num<<endl;
	createVertexArry();
	int start,end;
	int weight=0;
	while(!read.eof()){
		getline(read,tem);
		if (tem=="#")
		{
			continue;
		}
		if (tem!="")
		{
			int pos=tem.find(" ",0);
			istringstream st(tem.substr(0,pos));
			st>>start;
			//cout<<start<<endl;
			istringstream stt(tem.substr(pos,tem.length()));
			stt>>end;
			//cout<<end<<endl;
			addedge_direction(start,end,weight);
			edge_num++;
		}
	}
	read.close();
	cout<<"����ͼ����洢��ɣ�"<<endl;

// 	inputvexnum();
// 	createVertexArry();
// 	inputedgenum();
// 	addedgeinfo_direction();
}

void Graph::addedgeinfo_nodirection(){
	int start,end,weight;
	for (int i=0;i<edge_num;++i)
	{
		cout<<"please input the start:"<<endl;
		cin>>start;

		cout<<"please input the end:"<<endl;
		cin>>end;

		cout<<"please input the weight:"<<endl;
		cin>>weight;
		addedge_nodirection(start,end,weight);
	}

}

void Graph::addedgeinfo_direction(){
	int start,end,weight;
	for (int i=0;i<edge_num;++i)
	{
		cout<<"please input the start:"<<endl;
		cin>>start;

		cout<<"please input the end:"<<endl;
		cin>>end;

		cout<<"please input the weight:"<<endl;
		cin>>weight;
		addedge_direction(start,end,weight);
	}

}

void Graph::addedge_direction(int start,int end,int weight){
	Edge* edge1;
	edge1=new Edge;
	edge1->weight=0;
	edge1->nextEdge=NULL; 
	edge1->vName=end;
	edge1->nextEdge=head[start].next;
	head[start].next=edge1;//����ͷ�巨;
}

void Graph::addedge_nodirection(int start,int end,int weight){
	Edge* edge1;
	edge1=new Edge;
	edge1->weight=0;
	edge1->nextEdge=NULL; 
	edge1->vName=end;
	edge1->nextEdge=head[start].next;
	head[start].next=edge1;//����ͷ�巨;

	Edge* edge2;
	edge2=new Edge;
	edge2->weight=0;
	edge2->nextEdge=NULL; 
	edge2->vName=start;
	edge2->nextEdge=head[end].next;
	head[end].next=edge2;//����ͷ�巨;
}

void Graph::inputedgenum(){
	cout<<"please input the number of edge:"<<endl;
	cin>>edge_num;
}

void Graph::createVertexArry(){
	head=new ArcNode[vex_num];
	for (int i=0;i<vex_num;++i)
	{
		head[i].next=NULL;
		head[i].statu=false;
	}
}

void Graph::inputvexnum(){
	cout<<"please input the number of vex:"<<endl;
	cin>>vex_num;
}

Graph::Graph(void)
{
	head=new ArcNode;
	vex_num=0;
}

Graph::~Graph(void)
{
	for (int i=0;i<vex_num;++i)
	{
		Edge* tem;
		while(head[i].next!=NULL){
			tem=head[i].next;
			head[i].next=tem->nextEdge;
			delete tem;
		}
	}
	delete[] head;
}

