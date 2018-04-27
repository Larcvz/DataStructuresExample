#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MaxVertexNum 110
#define INFINITY 65536;

bool Visted[MaxVertexNum];
int distance;	//跳跃的距离

typedef int Vertex;
typedef double WeightType;

//图中点保存的数据定义
typedef struct Data DataType;	//保存坐标点<X,Y>
struct Data
{
	int x;
	int y;
};

//边的定义
typedef struct ENode *PtrToENode;
struct ENode
{
	int V1, V2;		//有向边<V1,V2>
	WeightType Weight;
};
typedef PtrToENode Edge;

//图结点的定义
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
	Graph = CreateGraph(VertexNum+1);	//因为要保存Bond在<0,0>的数据所以要多一个

	//边数就是最大边数这样好算一点总节数N 最大边数为N(N-1)/2
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
				//由于bond在<0,0>有一个半径为15的圆盘所以算出距离后得减去15
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