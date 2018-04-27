#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 10	//��󶥵���

bool Visited[MaxVertexNum];

/*ͼ���ڽӾ����ʾ*/
typedef int Vertex;			//�ö����±��ʾ����
typedef int WeightType;		//�ߵ�Ȩֵ ��������û��Ȩ��������0��1����ʾ
typedef char DataType;			//���ö���洢����������  ���ⲻ��Ҫ

/*�ߵĶ���*/
typedef struct ENode *PtrToENode;
struct ENode
{
	int V1, V2;				/*�����<V1,V2>*/
	WeightType Weight;		/*Ȩ��*/
};
typedef PtrToENode Edge;

/*ͼ���Ķ���*/
typedef struct GNode *PtrToGNode;
struct GNode
{
	int Nv;			//������
	int Ne;			//����
	WeightType G[MaxVertexNum][MaxVertexNum];
	/*DataType Data[MaxVertexNum];*/ //���ⲻ��Ҫ������������ע�͵���
};
typedef PtrToGNode Graph;


Graph CreateGraph(int VertexNum)
{
	//��ʼ��һ����VertexNum�������ͼ��û�б�
	Vertex V, M;
	Graph graph;

	graph = (Graph)malloc(sizeof(struct GNode));
	graph->Nv = VertexNum;
	graph->Ne = 0;
	//��ʼ���ڽӾ���
	//�����Ŵ�0��(garph->Nv-1)
	for (V = 0; V < graph->Nv; V++)
	{
		for ( M = 0; M < graph->Nv; M++)
		{
			graph->G[V][M] = 0;
		}
	}

	return graph;
}

void InsertEdge(Graph G, Edge E)
{
	G->G[E->V1][E->V2] = E->Weight;
	//��������ͼ���л���Ҫ���뵽<V2,V1>
	G->G[E->V2][E->V1] = E->Weight;
}

Graph BuildGraph()
{
	Graph graph;
	Edge E;
	int VertexNum, i;

	scanf("%d", &VertexNum);
	graph = CreateGraph(VertexNum);

	scanf("%d", &(graph->Ne));
	if (graph->Ne!=0)
	{
		E = (Edge)malloc(sizeof(struct ENode));
		//����߸�ʽΪ��� �յ�,�����ڽӾ���
		for (i = 0; i < graph->Ne; i++)
		{
			scanf("%d%d", &E->V1, &E->V2);
			E->Weight = 1;
			InsertEdge(graph, E);
		}
	}

	return graph;
}

bool IsEdge(Graph G, Vertex V, Vertex W)
{
	return G->G[V][W];
}

void DFS(Graph graph, Vertex V)
{
	Visited[V] = true;
	printf(" %d", V);
	Vertex W;
	for (W = 0; W < graph->Nv; W++)
	{
		if (!Visited[W] && IsEdge(graph, V, W))
			DFS(graph, W);
	}
}

void BFS(Graph graph, Vertex V)
{
	Vertex Q[MaxVertexNum];
	int front = 0, near = 0;
	Q[near++] = V;
	Visited[V] = true;
	while (front < near)
	{
		
		printf(" %d", Q[front]);
		Vertex W;
		for ( W = 0; W < graph->Nv; W++)
		{
			if (!Visited[W] && IsEdge(graph, W, Q[front]))
			{
				Q[near++] = W;
				Visited[W] = true;
			}
		}
		front++;
	}
}

int main()
{
	Graph G = BuildGraph();
	Vertex V;
	int i;
	for ( V = 0; V < G->Nv; V++)
	{
		if (!Visited[V])
		{
			printf("{");
			DFS(G, V);
			printf(" }\n");
		}
	}
	for ( i = 0; i < MaxVertexNum; i++)
	{
		Visited[i] = false;
	}
	for ( V = 0; V < G->Nv; V++)
	{
		if (!Visited[V])
		{
			printf("{");
			BFS(G, V);
			printf(" }\n");
		}
	}
	return 0;
}
