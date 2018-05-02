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
	int nu, mu, tu;
}TSMatrix;

void PrintTSMatrix(TSMatrix *M)
{
	int i;

	printf("%d %d\n", M->nu, M->mu);
	for ( i = 0; i < M->tu; i++)
	{
		printf("%d %d %d\n", M->Data[i].i, M->Data[i].j, M->Data[i].val);
	}
}

void PrintMatrix(TSMatrix *M)
{
	int i, j, k = 0;

	printf("%d %d\n", M->nu, M->mu);
	for ( i = 0; i < M->nu; i++)
	{
		int tag = 0;
		for ( j = 0; j < M->mu; j++)
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
	TSMatrix M;
	int n, m, i, j, t;
	double b;

	scanf("%d%d%lf", &n, &m, &b);

	M.mu = m, M.nu = n, M.tu = 0;
	M.Data = (Triple*)malloc(sizeof(Triple));

	for ( i = 0; i < n; i++)
	{
		for ( j = 0; j < m; j++)
		{
			scanf("%d", &t);
			if (t != 0)
			{
				M.Data = (Triple*)realloc(M.Data, sizeof(Triple)*(M.tu+1));
				M.Data[M.tu].i = i;
				M.Data[M.tu].j = j;
				M.Data[M.tu].val = t;
				++M.tu;
			}
		}
	}

	if (M.tu*1.0 / (m*n) < b)
		PrintTSMatrix(&M);
	else
		PrintMatrix(&M);

}

int main()
{
	Run();
	return 0;
}