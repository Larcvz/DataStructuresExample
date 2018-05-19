#include <stdio.h>
#include <stdlib.h>

int CircleTest(int A[], int index[], int circle[], int N)
{
	int head, i, P, tag, n;
	int *visit, tmp;

	n = 0;
	visit = (int*)malloc(sizeof(int)*N);
	for ( i = 0; i < N; i++)
		visit[i] = 0;
	for ( i = 0; i < N; i++)
	{
		if (visit[A[i]] == 0)
		{
			head = A[i];
			visit[head] = 1;
			tag = 0;
			if (head == 0)
				tag = 1;
			P = index[head];
			if (head == A[index[P]])
				continue;
			while (head != A[index[P]])
			{
				tmp = A[index[P]];
				visit[tmp] = 1;
				if (tmp == 0)
					tag = 1;
				P = index[tmp];
				circle[n]++;
			}
			if (tag == 0)
				circle[n]+=2;
			n++;
		}
	}

	return n;
}

void Solve()
{
	int numMove, N, i, *A, *index,*circle;

	scanf("%d", &N);
	A = (int*)malloc(sizeof(int)*N);
	index = (int*)malloc(sizeof(int)*N);
	circle = (int*)malloc(sizeof(int)*N);
	for ( i = 0; i < N; i++)
	{
		scanf("%d", &A[i]);
		index[A[i]] = i;
		circle[i] = 0;
	}
	
	i = CircleTest(A, index, circle, N);
	numMove = 0;
	for (i--; i >= 0; --i)
	{
		numMove += circle[i];
	}
	
	printf("%d\n", numMove);
	free(A);
}

int main()
{
	Solve();

	return 0;
}