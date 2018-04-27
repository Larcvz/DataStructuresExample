#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 10	//最大顶点数

bool Visited[MaxVertexNum];

/*图的邻接矩阵表示*/
typedef int Vertex;			//用顶点下标表示顶点
typedef int WeightType;		//边的权值 这题由于没有权重所以用0和1来表示
typedef char DataType;			//设置定点存储的数据类型  本题不需要

/*边的定义*/
typedef struct ENode *PtrToENode;
struct ENode
{
	int V1, V2;				/*有向边<V1,V2>*/
	WeightType Weight;		/*权重*/
};
typedef PtrToENode Edge;

/*图结点的定义*/
typedef struct GNode *PtrToGNode;
struct GNode
{
	int Nv;			//顶点数
	int Ne;			//边数
	WeightType G[MaxVertexNum][MaxVertexNum];
	/*DataType Data[MaxVertexNum];*/ //本题不需要保存数据所以注释掉。
};
typedef PtrToGNode Graph;


Graph CreateGraph(int VertexNum)
{
	//初始化一个有VertexNum个顶点的图但没有边
	Vertex V, M;
	Graph graph;

	graph = (Graph)malloc(sizeof(struct GNode));
	graph->Nv = VertexNum;
	graph->Ne = 0;
	//初始化邻接矩阵
	//顶点编号从0到(garph->Nv-1)
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
	//若是无向图所有还需要插入到<V2,V1>
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
		//读入边格式为起点 终点,插入邻接矩阵
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
