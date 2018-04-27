#include <stdio.h>
#include <stdlib.h>
int *num, *BST;

int cmpare(const void*a, const void*b) {
	return *(int*)a - *(int*)b;
}

int log(int n) {
	int a = 0;
	n++;
	while (n!=1)
	{
		n >>= 1;
		a++;
	}
	return a;
}
//Y叶节点的数量，D满二叉树的最大层数,N为节点数
int GetLeftLength(int N) {
	int D = log(N);
	int Y = N - (1 << D) + 1;
	if (Y > 1 << (D - 1))
		return (1 << D) - 1;
	else
		return (1 << (D - 1)) - 1 + Y;
}
void solve(int Left, int Right, int Troot) {
	int N = Right - Left + 1, L;
	if (N == 0)return;
	L = GetLeftLength(N);
	BST[Troot] = num[L + Left];
	int TrootLeft = 2 * Troot + 1;
	int TrootRight = TrootLeft + 1;
	solve(Left, Left + L - 1, TrootLeft);
	solve(Left + L + 1, Right, TrootRight);
}

int main()
{
	int N, i;
	scanf("%d", &N);
	num = (int*)malloc(sizeof(int)*N);
	BST = (int*)malloc(sizeof(int)*N);
	for ( i = 0; i < N; i++)
	{
		scanf("%d", &num[i]);
	}
	qsort(num, N, sizeof(int), cmpare);
	solve(0, N - 1, 0);
	printf("%d", BST[0]);
	for ( i = 1; i < N; i++)
	{
		printf(" %d", BST[i]);
	}
	printf("\n");
	return 0;
}