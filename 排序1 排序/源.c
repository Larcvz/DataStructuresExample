#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

void Swap(ElementType *A, ElementType *B)
{
	ElementType temp=*A;
	*A = *B;
	*B = temp;
}
//冒泡排序
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
//插入排序
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
//希尔排序
void Shell_Sort(ElementType A[], int N)
{
	int i, j, Increment;
	ElementType tmp;

	for ( Increment = N/2; Increment > 0; Increment/=2)
	{
		for ( i = Increment; i < N; i++)
		{
			tmp = A[i];
			for ( j = i; j >= Increment&&tmp<A[j-Increment]; j-=Increment)
			{
					A[j] = A[j - Increment];
			}
			A[j] = tmp;
		}
	}
}
void ShellSort(ElementType A[], int N) { 
	/* 希尔排序 - 用Sedgewick增量序列 */
	int Si, D, P, i;
	ElementType Tmp;
	/* 这里只列出一小部分增量 */
	int Sedgewick[] = { 929, 505, 209, 109, 41, 19, 5, 1, 0 };
	for (Si = 0; Sedgewick[Si] >= N; Si++);
	/* 初始的增量Sedgewick[Si]不能超过待排序列长度 */
	for (D = Sedgewick[Si]; D>0; D = Sedgewick[++Si])
		for (P = D; P<N; P++) {
			/* 插入排序*/
			Tmp = A[P];
			for (i = P; i >= D && A[i - D]>Tmp; i -= D)
				A[i] = A[i - D];
			A[i] = Tmp;
		}
}
//堆排序
#define LeftChild(i) (2*(i)+1)

void PercDown(ElementType A[],int i, int N)
{
	int Child;
	ElementType tmp;

	for (tmp = A[i]; LeftChild(i) < N; i = Child)
	{
		Child = LeftChild(i);
		if (Child != N - 1 && A[Child + 1] > A[Child])
			Child++;
		if (tmp < A[Child])
			A[i] = A[Child];
		else
			break;
	}
	A[i] = tmp;
}

void HeapSort(ElementType A[], int N)
{
	int i;
	for ( i = N/2; i >= 0; i--)
	{
		PercDown(A, i, N);
	}
	for ( i = N-1; i > 0; i--)
	{
		Swap(A, A + i);
		PercDown(A, 0, i);
	}
}
//归并排序
void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, NumElements, TmpPos;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	while (Lpos<=LeftEnd&&Rpos<=RightEnd)
	{
		if (A[Lpos]<=A[Rpos])
		{
			TmpArray[TmpPos++] = A[Lpos++];
		}
		else
		{
			TmpArray[TmpPos++] = A[Rpos++];
		}
	}
	while (Lpos <= LeftEnd)
		TmpArray[TmpPos++] = A[Lpos++];
	while (Rpos <= RightEnd)
		TmpArray[TmpPos++] = A[Rpos++];

	for ( i = 0; i < NumElements; i++,RightEnd--)
	{
		A[RightEnd] = TmpArray[RightEnd];
	}
}

void MSort(ElementType A[],ElementType TmpArray[],int Left,int Right)
{
	int Center;

	if (Left < Right)
	{
		Center = (Left + Right) / 2;
		MSort(A, TmpArray, Left, Center);
		MSort(A, TmpArray, Center + 1, Right);
		Merge(A, TmpArray, Left, Center + 1, Right);
	}
}

void MergeSort(ElementType A[], int N)
{
	ElementType *TmpArray;

	TmpArray = (ElementType*)malloc(sizeof(ElementType)*N);
	if (TmpArray != NULL)
	{
		MSort(A, TmpArray, 0, N - 1);
		free(TmpArray);
	}
	else
		exit(1);
}
//快速排序
ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (A[Left] > A[Center])
		Swap(A + Left, A + Center);
	if (A[Left] > A[Right])
		Swap(A + Left, A + Right);
	if (A[Center] > A[Right])
		Swap(A + Center, A + Right);

	Swap(A + Center, A + Right - 1);
	return A[Right - 1];
}
#define Cutoff (3)
void Qsort(ElementType A[], int Left, int Right)
{
	int i, j;
	ElementType Pivot;
	
	if (Left+Cutoff<=Right)
	{
		Pivot = Median3(A, Left, Right);
		i = Left; j = Right - 1;
		for (; ;)
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)
				Swap(A + i, A + j);
			else
				break;
		}
		Swap(A + i, A + Right - 1);
		
		Qsort(A, Left, i - 1);
		Qsort(A, i + 1, Right);
	}
	else
	{
		Insertion_Sort(A + Left, Right - Left + 1);
	}
}

void QuickSort(ElementType A[], int N)
{
	Qsort(A, 0, N - 1);
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
	QuickSort(A, N);
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