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
遇到的第一个数字说明了刚开始入栈了几个数字，所以先写一个入栈函数即可然后再返回的结尾处记得先Pop出栈一次将
第一个数字弹出，第一次里面如果输入的数字大于了M的值也就是栈满了显然这就是错的直接返回一个NULL如果Stack S
的值为空就表示是错的，后面如果数字比现在的栈顶要小显然这是不可能的所以就是错的，然后考虑当数字比之前Push
的值要大的时候此时就调用Push函数将数字压入栈中(这里有个点就是要用一个元素来记录上一次Push的最大值)入栈完
成后要记得将记录的最大值更新，最后一个else就是当前的数字和栈顶元素相同的时候这时就只要Pop即可。
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