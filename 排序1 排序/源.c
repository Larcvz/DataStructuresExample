#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

void Swap(ElementType *A, ElementType *B)
{
	ElementType temp=*A;
	*A = *B;
	*B = temp;
}
//√∞≈›≈≈–Ú
void Bubble_Sort(ElementType A[], int N)
{
	int i, j;
	int flag;
	for ( i = N-1; i >= 0; i--)
	{
		flag = 0;
		for ( j = 0; j < i; j++)
		{
			if (A[j] > A[j + 1])
			{
				Swap(A + j, A + j + 1);
				flag = 1;
			}
		}
		if (flag == 0)break;
	}
}
//≤Â»Î≈≈–Ú
void Insertion_Sort(ElementType A[],int N)
{
	int j, P;

	ElementType tmp;
	for ( P = 1; P < N; P++)
	{
		tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > tmp; j--)
		{
			A[j] = A[j - 1];
		}
		A[j] = tmp;
	}
}

int main()
{
	int N, i, tag;
	ElementType *A;
	
	scanf("%d", &N);
	A = (ElementType*)malloc(sizeof(ElementType)*N);
	for ( i = 0; i < N; i++)
	{
		scanf("%d", A + i);
	}
	Insertion_Sort(A, N);
	tag = 0;
	for ( i = 0; i < N; i++)
	{
		if (tag)
			printf(" ");
		printf("%d", A[i]);
		tag = 1;
	}

	return 0;
}