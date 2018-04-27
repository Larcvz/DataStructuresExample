/*
还不算是完成品，离实现和搞懂还差很远
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct StackRecord *Stack;
typedef struct TreeNode *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode Tree;
typedef int ELementType;

struct TreeNode
{
	ELementType Element;
	Tree Left;
	Tree Right;
};

struct StackRecord
{
	Position Array[100];
	int Capacity;
	int TopOfStack;
};

Stack CreatStack() {
	Stack S = (Stack)malloc(sizeof(struct StackRecord));
	S->Capacity = 100;
	S->TopOfStack = -1;
	return S;
}

int isEmptyStack(Stack S) {
	return S->TopOfStack == -1;
}

int isFullStack(Stack S) {
	return S->TopOfStack == S->Capacity - 1;
}

Position Pop(Stack S) {
	if (isEmptyStack(S))
	{
		printf("Error Empty Stack\n");
		return NULL;
	}
	else
	{
		return S->Array[S->TopOfStack--];
	}
}

Position Top(Stack S) {
	return S->Array[S->TopOfStack];
}

void Push(Stack S,Position X) {
	if (isFullStack(S))
	{
		printf("Error Full Stack");
	}
	else
	{
		S->Array[++S->TopOfStack] = X;
	}
}

Tree CreatBinTree() {
	Tree BT = (Tree)malloc(sizeof(struct TreeNode));
	scanf("%d", &BT->Element);
	BT->Left = NULL;
	BT->Right = NULL;
	return BT;
}

Tree Insert(Tree BT, ELementType X) {
	if (!BT)
	{
		BT = (Tree)malloc(sizeof(struct TreeNode));
		BT->Element = X;
		BT->Left = NULL;
		BT->Right = NULL;
	}
	else {
		if (X < BT->Element)
		{
			BT->Left = Insert(BT->Left, X);
		}
		else
		{
			BT->Right = Insert(BT->Right, X);
		}
	}
	return BT;
}

void PostOrderTraversal(Tree BT) {
	Stack S = CreatStack();
	Stack Cmp = CreatStack();
	Tree T = BT, TR, temp = NULL;
	while (T||!isEmptyStack(S))
	{
		while (T&&T != temp)
		{
			Push(S, T);
			TR = T->Right;
			T = T->Left;
		}
		if (TR) {
			T = TR;
		}
		else
		{
			T = Pop(S);
			printf("%d ", T->Element);
			if (isEmptyStack(S))
				return;
			if (Top(Cmp) != Top(S)) {
				Push(Cmp, Top(S));
				T = Top(S)->Right;
			}
			else
			{	
				temp = Pop(Cmp);
				T = Top(S);
			}
		}
		
	}
}

int main()
{
	Tree BT = CreatBinTree();
	int n;
	scanf("%d", &n);
	while (n--)
	{
		ELementType temp;
		scanf("%d", &temp);
		BT = Insert(BT, temp);
	}
	PostOrderTraversal(BT);
	return 0;
}