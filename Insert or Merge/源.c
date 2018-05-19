#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
/* �鲢���� - ѭ��ʵ�� */
/* ����Merge�����ڵݹ�汾�и��� */
/* length = ��ǰ�������еĳ���*/
void Merge(ElementType A[], ElementType TmpA[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, NumElements, TmpPos;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	while (Lpos<=LeftEnd&&Rpos<=RightEnd)
	{
		if (A[Lpos] <= A[Rpos])
			TmpA[TmpPos++] = A[Lpos++];
		else
			TmpA[TmpPos++] = A[Rpos++];
	}
	while (Lpos <= LeftEnd)
		TmpA[TmpPos++] = A[Lpos++];
	while (Rpos <= RightEnd)
		TmpA[TmpPos++] = A[Rpos++];

	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd];
}

void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length) {
	/* �����鲢������������ */
	int i, j;
	for (i = 0; i <= N - 2 * length; i += 2 * length)
		Merge(A, TmpA, i, i + length, i + 2 * length - 1);
	if (i + length < N) /* �鲢���2������*/
		Merge(A, TmpA, i, i + length, N - 1);
	else /* ���ֻʣ1������*/
		for (j = i; j < N; j++)
			TmpA[j] = A[j];
}
int Merge_Sort(ElementType A[], int N,ElementType Iterates[]) {
	int length, flag, i, tag;
	ElementType *TmpA;
	length = 1; /* ��ʼ�������г���*/
	flag = 0;
	TmpA = malloc(N * sizeof(ElementType));
	if (TmpA != NULL) {
		while (length < N) {
			Merge_pass(A, TmpA, N, length);
			tag = 1;
			length *= 2;
			for (i = 0; i < N; i++)
			{
				if (TmpA[i] != Iterates[i])
					break;
			}
			if (flag == 1)
				break;
			if (i == N)
				flag = 1;
			Merge_pass(TmpA, A, N, length);
			tag = 0;
			length *= 2;
			//�������һ���ж���������˻�û����Ҫ���Ǿ��ǲ�������
			for (i = 0; i < N; i++)
			{
				if (A[i] != Iterates[i])
					break;
			}
			if (flag == 1)
				break;
			if (i == N)
				flag = 1;
		}
		if (tag == 1)
			for (i = 0; i < N; i++)
				A[i] = TmpA[i];

		free(TmpA);
	}
	return flag;
}

int main()
{
	ElementType *Array, *Iterates;
	int N, i;

	scanf("%d", &N);
	Array = (ElementType*)malloc(sizeof(ElementType)*N);
	Iterates = (ElementType*)malloc(sizeof(ElementType)*N);
	for ( i = 0; i < N; i++)
	{
		scanf("%d", &Array[i]);
	}
	for ( i = 0; i < N; i++)
	{
		scanf("%d", &Iterates[i]);
	}
	if (Merge_Sort(Array, N, Iterates))
	{
		int tag = 0;
		printf("Merge Sort\n");
		for ( i = 0; i < N; i++)
		{
			if (tag == 1)
				printf(" ");
			printf("%d", Array[i]);
			tag = 1;
		}
		printf("\n");
	}
	else
	{
		printf("Insertion Sort\n");
		int j, P, tag;

		ElementType tmp;
		tag = 0;
		for ( P = 1; P < N; P++)
		{
			tmp = Iterates[P];
			for (j = P; j > 0 && Iterates[j - 1] > tmp; j--)
			{
				tag = 1;
				Iterates[j] = Iterates[j - 1];
			}
			Iterates[j] = tmp;
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