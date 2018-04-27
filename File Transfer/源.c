#include <stdio.h>
#include <stdlib.h>

typedef int *DisjSet;
typedef int SetType;
typedef int ElementType;

void Initilialaize(DisjSet S,int N);
void SetUnion(DisjSet S, SetType Root1, SetType Root2);
SetType Find(ElementType X, DisjSet S);

int main()
{
	int N, count = 0;
	int c1, c2;
	char C;

	scanf("%d", &N);
	DisjSet S = (DisjSet)malloc(sizeof(int)*N + 1);
	Initilialaize(S, N);

	while (scanf(" %c", &C), C != 'S')
	{
		scanf("%d%d", &c1, &c2);
		if (C == 'C')
		{
			if (Find(c1, S) == Find(c2, S))
				printf("yes\n");
			else
				printf("no\n");
		}
		else
			SetUnion(S, Find(c1, S), Find(c2, S));
	}
	int i;
	for ( i = 1; i <= N; i++){
		if (S[i] < 0)
			count++;
	}
	if (count == 1)
		printf("The network is connected.\n");
	else
		printf("There are %d components.\n", count);
	return 0;
}

SetType Find(ElementType X, DisjSet S)
{
	if (S[X] <= 0)
		return X;
	else
		return S[X] = Find(S[X], S);
}

void Initilialaize(DisjSet S,int N)
{
	int i;
	
	for (i = N; i > 0; i--)
		S[i] = -1;
}

void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
	if (S[Root2] < S[Root1]) 
	{
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
	else
	{
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	}

}