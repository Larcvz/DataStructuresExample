#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct
{
	ElementType val;
	int i, j;
}Triple;
typedef struct 
{
	Triple *Data;
	int mu, nu, tu;
}TSMatrix;

int FastTransposeSMatrix(TSMatrix *M, TSMatrix *T)
{
	int *num, *cpot, i, col, p;

	T->nu = M->mu; T->mu = M->nu; T->tu = M->tu;
	T->Data = (Triple*)malloc(sizeof(Triple)*M->tu);
	num = (int*)malloc(sizeof(int)*M->mu);
	cpot = (int*)malloc(sizeof(int)*M->mu);
	
	for (i = 0; i < M->mu; i++)//初始化数组
		num[i] = 0;
	for ( i = 0; i < M->tu; i++)//统计每一列中非0元的个数
		++num[M->Data[i].j];
	cpot[0] = 0;
	for ( i = 1; i < M->mu; i++)
		cpot[i] = cpot[i - 1] + num[i - 1];//求出第i列中第一个非0元在转置后的表中的序号
	for ( i = 0; i < M->tu; i++)
	{
		col = M->Data[i].j;
		p = cpot[col];
		T->Data[p].i = M->Data[i].j;
		T->Data[p].j = M->Data[i].i;
		T->Data[p].val = M->Data[i].val;
		++cpot[col];
	}

	return 1;
}

void PrintTSMatrix(TSMatrix *M)
{
	int i;

	printf("%d %d\n", M->nu, M->mu);
	for (i = 0; i < M->tu; i++)
	{
		printf("%d %d %d\n", M->Data[i].i, M->Data[i].j, M->Data[i].val);
	}
}

void PrintMatrix(TSMatrix *M)
{
	int i, j, k = 0;

	printf("%d %d\n", M->nu, M->mu);
	for (i = 0; i < M->nu; i++)
	{
		int tag = 0;
		for (j = 0; j < M->mu; j++)
		{
			if (tag)
				printf(" ");
			if (M->Data[k].i == i && M->Data[k].j == j)
				printf("%d", M->Data[k++].val);
			else
				printf("0");
			tag = 1;
		}
		printf("\n");
	}
}

void Run()
{
	TSMatrix M, T;
	int n, m, i, j, t;

	scanf("%d%d", &n, &m);

	M.mu = m, M.nu = n, M.tu = 0;
	M.Data = (Triple*)malloc(sizeof(Triple));

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			scanf("%d", &t);
			if (t != 0)
			{
				M.Data = (Triple*)realloc(M.Data, sizeof(Triple)*(M.tu + 1));
				M.Data[M.tu].i = i;
				M.Data[M.tu].j = j;
				M.Data[M.tu].val = t;
				++M.tu;
			}
		}
	}

	FastTransposeSMatrix(&M, &T);
	//PrintMatrix(&M);
	PrintMatrix(&T);
	free(T.Data);
	free(M.Data);
}

int main()
{
	Run();
	return 0;
}
