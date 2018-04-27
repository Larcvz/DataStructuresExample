/*
Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2
Sample Output:
YES
NO
NO
YES
NO
�����ĵ�һ������˵���˸տ�ʼ��ջ�˼������֣�������дһ����ջ��������Ȼ���ٷ��صĽ�β���ǵ���Pop��ջһ�ν�
��һ�����ֵ�������һ�����������������ִ�����M��ֵҲ����ջ������Ȼ����Ǵ��ֱ�ӷ���һ��NULL���Stack S
��ֵΪ�վͱ�ʾ�Ǵ�ģ�����������ֱ����ڵ�ջ��ҪС��Ȼ���ǲ����ܵ����Ծ��Ǵ�ģ�Ȼ���ǵ����ֱ�֮ǰPush
��ֵҪ���ʱ���ʱ�͵���Push����������ѹ��ջ��(�����и������Ҫ��һ��Ԫ������¼��һ��Push�����ֵ)��ջ��
�ɺ�Ҫ�ǵý���¼�����ֵ���£����һ��else���ǵ�ǰ�����ֺ�ջ��Ԫ����ͬ��ʱ����ʱ��ֻҪPop���ɡ�
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct SNode *Stack;
typedef int ElementType;
typedef int Position;
struct SNode
{
	ElementType *Data;
	Position Top;
	int MaxSize;
};
void Pop(Stack S) {
	S->Top--;
}
Stack CreateStack(int last, int M) {
	if (last > M) {
		return NULL;
	}
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->MaxSize = M;
	S->Top = -1;
	S->Data = (ElementType*)malloc(sizeof(ElementType)*M);
	int i;
	for ( i = 1; i <= last; i++)
	{
		S->Data[++S->Top] = i;
	}
	Pop(S);
	return S;
}
ElementType Top(Stack S) {
	return S->Data[S->Top];
}
bool Push(ElementType X, Stack S, ElementType max) {
	ElementType tmp = max+1;
	for (; tmp <= X; tmp++) {
		if (S->Top < S->MaxSize - 1) {
			S->Data[++S->Top] = tmp;
		}
		else {
			return false;
		}
	}
	Pop(S);
	return true;
}
int Test(int *num, int M, int N) {
	int i, last = num[0];
	Stack S = CreateStack(last, M);
	if (!S) {
		return 0;
	}
	for ( i = 1; i < N; i++)
	{
		if (num[i] < Top(S)) {
			return 0;
		}
		if (last < num[i]) {
			if (!Push(num[i], S, last)) {
				return 0;
			}
			last = num[i];
		}
		else
		{
			Pop(S);
		}
	}
	return 1;
}
int main()
{
	int M, N, K;
	scanf("%d%d%d", &M, &N, &K);
	int *num = (int *)malloc(sizeof(int)*N);
	while (K--)
	{
		int i;
		for ( i = 0; i < N; i++)
		{
			scanf("%d", num + i);
		}
		if (Test(num, M, N))
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}