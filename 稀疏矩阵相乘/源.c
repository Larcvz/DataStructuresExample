#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct
{
	ElementType value;
	int row, col;
}Triple;
typedef struct
{
	Triple *data;
	int *rpos;
	int maxRow, maxCol, valueCount;
}RLSMatrix;

int MultiSMatrix(RLSMatrix *M, RLSMatrix *T, RLSMatrix *Q)
{
	ElementType *ctemp;
	int arow,brow;

	if (M->maxCol != T->maxRow)return 1;

	ctemp = (ElementType*)malloc(sizeof(ElementType)*M->maxRow);
	Q->maxRow = M->maxRow; Q->maxCol = T->maxCol; Q->valueCount = 0;
	Q->rpos = (int*)malloc(sizeof(int)*Q->maxRow);

	if (M->valueCount*T->valueCount != 0)
	{
		for (arow = 0; arow < M->maxRow; arow++)
		{
			int i, tp, ccol, t, p, q, brow;

			for (i = 0; i < M->maxRow; i++)
				ctemp[i] = 0;

			Q->rpos[arow] = Q->valueCount;

			if (arow < M->maxRow-1)
				tp = M->rpos[arow + 1];
			else 
				tp = M->valueCount;

			for ( p = M->rpos[arow]; p < tp; p++)
			{
				brow = M->data[p].col;

				if (brow < T->maxRow - 1)
					t = T->rpos[brow + 1];
				else
					t = T->valueCount;

				for ( q = T->rpos[brow]; q < t; q++)
				{
					ccol = T->data[q].col;
					ctemp[ccol] += T->data[q].value*M->data[p].value;
				}
			}
			for (ccol = 0; ccol < Q->maxRow; ++ccol)
			{
				if (ctemp[ccol])
				{
					Q->data = (Triple*)realloc(Q->data, sizeof(Triple)*(Q->valueCount + 1));
					Q->data[Q->valueCount].row = arow;
					Q->data[Q->valueCount].col = ccol;
					Q->data[Q->valueCount].value = ctemp[ccol];
					++Q->valueCount;
				}
			}
		}
	}
	return 0;
}

void PrintTSMatrix(RLSMatrix *M)
{
	int i;

	printf("%d %d\n", M->maxRow, M->maxCol);
	for ( i = 0; i < M->valueCount; i++)
	{
		printf("%d %d %d\n", M->data[i].row, M->data[i].col, M->data[i].value);
	}
}

void PrintMatrix(RLSMatrix *M)
{
	int i, j, k = 0;

	printf("行数：%d 列数：%d\n", M->maxRow, M->maxCol);
	for ( i = 0; i < M->maxRow; i++)
	{
		int tag = 0;
		for ( j = 0; j < M->maxCol; j++)
		{
			if (tag)
				printf(" ");
			if (M->data[k].row == i && M->data[k].col == j)
				printf("%d", M->data[k++].value);
			else
				printf("0");
			tag = 1;
		}
		printf("\n");
	}
}

RLSMatrix* CreateRLSMatrix()
{
	RLSMatrix *M;
	int n, m, i, j, t;

	scanf("%d%d", &n, &m);

	M = (RLSMatrix*)malloc(sizeof(RLSMatrix));
	M->maxCol = m, M->maxRow = n, M->valueCount = 0;
	M->rpos = (int*)malloc(sizeof(int)*M->maxRow);
	M->data = (Triple*)malloc(sizeof(Triple));

	for ( i = 0; i < n; i++)
	{
		for ( j = 0; j < m; j++)
		{
			scanf("%d", &t);
			if (t != 0)
			{
				M->data = (Triple*)realloc(M->data, sizeof(Triple)*(M->valueCount+1));
				M->data[M->valueCount].row = i;
				M->data[M->valueCount].col = j;
				M->data[M->valueCount].value = t;
				++M->valueCount;
			}
		}
	}

	int *num;

	num = (int*)malloc(sizeof(int)*M->maxRow);
	M->rpos[0] = 0;

	for (i = 0; i < M->maxRow; ++i)
		num[i] = 0;
	for (i = 0; i < M->valueCount; ++i)
		++num[M->data[i].row];	
	for (i = 1; i < M->maxRow; ++i)
		M->rpos[i] = M->rpos[i - 1] + num[i - 1];

	return M;
}
int main()
{
	RLSMatrix* M1 = CreateRLSMatrix();
	RLSMatrix* M2 = CreateRLSMatrix();
	RLSMatrix Q;

	Q.data = (Triple*)malloc(sizeof(Triple));

	MultiSMatrix(M1, M2, &Q);
	PrintMatrix(&Q);

	return 0;
}