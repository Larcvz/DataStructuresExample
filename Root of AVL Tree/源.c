#include <stdio.h>
#include <stdlib.h>
struct AvlNode;
typedef struct AvlNode *Position;
typedef Position AvlTree;
typedef int ElementType;

AvlTree MakeEmpty();
AvlTree Insert(ElementType X, AvlTree T);
AvlTree SingleRotateWithLeft(AvlTree T);
AvlTree DoubleRotateWithLeft(AvlTree T);
AvlTree SingleRotateWithRight(AvlTree T);
AvlTree DoubleRotateWithRight(AvlTree T);

struct AvlNode
{
	ElementType Data;
	AvlTree Left;
	AvlTree Right;
	int		Height;
};

int Max(int a, int b) {
	return a > b ? a : b;
}

int Height(AvlTree T) {
	if (!T) {
		return -1;
	}
	return T->Height;
}

AvlTree MakeEmpty() {
	AvlTree T = (AvlTree)malloc(sizeof(struct AvlNode));
	T->Left = NULL;
	T->Right = NULL;
	T->Height = 0;
	return T;
}

AvlTree Insert(ElementType X, AvlTree T) {
	if (!T) {
		T = MakeEmpty();
		if (!T) {
			printf("Out of space!");
		}
		else {
			T->Data = X;
		}
	}
	else
	{
		if (X < T->Data) {
			T->Left = Insert(X, T->Left);
			if (Height(T->Left) - Height(T->Right) == 2) {
				if (X < T->Left->Data)
					T = SingleRotateWithLeft(T);
				else
					T = DoubleRotateWithLeft(T);
			}
		}
		else if (X > T->Data) {
			T->Right = Insert(X, T->Right);
			if (Height(T->Right) - Height(T->Left) == 2)
			{
				if (X > T->Right->Data)
					T = SingleRotateWithRight(T);
				else
					T = DoubleRotateWithRight(T);
			}
		}
	}
	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

AvlTree SingleRotateWithLeft(AvlTree K2) {
	Position K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Left), K2->Height) + 1;
	return K1;
}

AvlTree SingleRotateWithRight(AvlTree K2) {
	Position K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Right), K2->Height) + 1;
	return K1;
}

AvlTree DoubleRotateWithLeft(AvlTree K3) {
	K3->Left = SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

AvlTree DoubleRotateWithRight(AvlTree K3) {
	K3->Right = SingleRotateWithLeft(K3->Right);
	return SingleRotateWithRight(K3);
}

AvlTree Create(int N) {
	AvlTree root = NULL;
	while (N--)
	{
		int x;
		scanf("%d", &x);
		root = Insert(x, root);
	}
	return root;
}

int main()
{
	int N;
	scanf("%d", &N);
	AvlTree root = Create(N);
	printf("%d\n", root->Data);
	return 0;
}