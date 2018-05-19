#include <stdio.h>
#include <stdlib.h>

#define LeftChild(i) (2*(i)+1)

typedef int ElementType;

void Swap(ElementType *A, ElementType *B)
{
	ElementType tmp;

	tmp = *A;
	*A = *B;
	*B = tmp;
}
//∂—≈≈–Ú
void PercDown(ElementType A[], int i, int N)
{
	int Child;
	ElementType Tmp;

	for (Tmp = A[i]; LeftChild(i) < N; i = Child)
	{
		Child = LeftChild(i);
		if (Child != N - 1 && A[Child + 1] > A[Child])
			Child++;
		if (Tmp < A[Child])
			A[i] = A[Child];
		else
			break;
	}
	A[i] = Tmp;
}

int HeapSort(ElementType A[100], int N, ElementType Iterates[100])
{
	int i, flag, j;

	for ( i = N/2; i >= 0; i--)
		PercDown(A, i, N);
	flag = 0;
	for ( i = N-1; i > 0; i--)
	{
		Swap(&A[0], &A[i]);
		PercDown(A, 0, i);
		if (flag == 1)
			break;
		for (j = N - 1; j >= 0; j--)
		{
			if (A[j] != Iterates[j])
				break;
		}
		if (j < 0)
			flag = 1;
	}

	return flag;
}

int main()
{
	ElementType A[100], Iterates[100];
	int N, i;

	scanf("%d", &N);
	
	for ( i = 0; i < N; i++)
		scanf("%d", &A[i]);
	for (i = 0; i < N; i++)
		scanf("%d", &Iterates[i]);

	if (HeapSort(A, N, Iterates))
	{
		printf("Heap Sort\n");

		int tag = 0;
		for ( i = 0; i < N; i++)
		{
			if (tag == 1)
				printf(" ");
			printf("%d", A[i]);
			tag = 1;
		}
		printf("\n");
	}
	else
	{
		printf("Insertion Sort\n");

		int j, P, tag;
		ElementType Tmp;

		tag = 0;
		for ( P = 1; P < N; P++)
		{
			Tmp = Iterates[P];
			for (j = P; j > 0 && Iterates[j - 1] > Tmp; j--)
			{
				tag = 1;
				Iterates[j] = Iterates[j - 1];
			}
			Iterates[j] = Tmp;
			if (tag == 1)
				break;
		}
		tag = 0;
		for ( i = 0; i < N; i++)
		{
			if (tag == 1)
				printf(" ");
			printf("%d", Iterates[i]);
			tag = 1;
		}
		printf("\n");
	}

	return 0;
}