#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MaxVertexNum 110
#define INFINITY 65536;

bool Visted[MaxVertexNum];
int distance;	//��Ծ�ľ���

typedef int Vertex;
typedef double WeightType;

//ͼ�е㱣������ݶ���
typedef struct Data DataType;	//���������<X,Y>
struct Data
{
	int x;
	int y;
};

//�ߵĶ���
typedef struct ENode *PtrToENode;
struct ENode
{
	int V1, V2;		//�����<V1,V2>
	WeightType Weight;
};
typedef PtrToENode Edge;

//ͼ���Ķ���
typedef struct GNode *PtrToGNode;
struct GNode
{
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
	DataType Data[MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph(int VertexNum)
{
	MGraph Graph;
	Vertex V, W;

	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for ( V = 0; V < Graph->Nv; V++)
	{
		for ( W = 0; W < Graph->Nv; W++)
		{
			Graph->G[V][W] = INFINITY;
		}
	}

	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	Graph->G[E->V1][E->V2] = E->Weight;
	Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	int VertexNum, i, j;

	scanf("%d%d", &VertexNum,&distance);
	Graph = CreateGraph(VertexNum+1);	//��ΪҪ����Bond��<0,0>����������Ҫ��һ��

	//����������������������һ���ܽ���N ������ΪN(N-1)/2
	Graph->Ne = VertexNum * (VertexNum + 1) / 2;
	Graph->Data[0].x = 0;
	Graph->Data[0].y = 0;

	if (Graph->Ne != 0)
	{
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 1; i < VertexNum+1; i++)
		{
			scanf("%d%d", &Graph->Data[i].x, &Graph->Data[i].y);
			E->V1 = i;
			for ( j = 0; j < i; j++)
			{
				E->V2 = j;
				int a = (Graph->Data[i].x) - (Graph->Data[j].x);
				int b = (Graph->Data[i].y) - (Graph->Data[j].y);
				E->Weight = sqrt((double)(a*a + b * b));
				//����bond��<0,0>��һ���뾶Ϊ15��Բ��������������ü�ȥ15
				if (j == 0)
					E->Weight -= 7.5;
				InsertEdge(Graph, E);
			}
		}
	}

	return Graph;
}

bool IsEdge(MGraph Graph, Vertex V, Vertex W)
{
	return Graph->G[V][W] <= distance;
}

bool IsSurvive(MGraph Graph, Vertex V)
{
	int x = Graph->Data[V].x;
	int y = Graph->Data[V].y;
	if (x + distance >= 50 || x - distance <= -50 || y + distance >= 50 || y - distance <= -50)
		return true;
	return false;
}

void DFS(MGraph Graph, Vertex V)
{
	Visted[V] = true;
	Vertex W;
	
	for (W = 0; W < Graph->Nv; W++)
	{
		if (!Visted[W] && IsEdge(Graph, V, W))
		{
			if (IsSurvive(Graph, W))
			{
				printf("Yes\n");
				exit(0);
			}
			DFS(Graph, W);
		}
	}
}

int main()
{
	MGraph Graph = BuildGraph();
	DFS(Graph, 0);
	printf("No\n");
	return 0;
}