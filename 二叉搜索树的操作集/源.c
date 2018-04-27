#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
	BinTree BST, MinP, MaxP, Tmp;
	ElementType X;
	int N, i;

	BST = NULL;
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		BST = Insert(BST, X);
	}
	printf("Preorder:"); PreorderTraversal(BST); printf("\n");
	MinP = FindMin(BST);
	MaxP = FindMax(BST);
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		Tmp = Find(BST, X);
		if (Tmp == NULL) printf("%d is not found\n", X);
		else {
			printf("%d is found\n", Tmp->Data);
			if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
			if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
		}
	}
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		BST = Delete(BST, X);
	}
	printf("Inorder:"); InorderTraversal(BST); printf("\n");

	return 0;
}
/* 你的代码将被嵌在这里 */
BinTree Insert(BinTree BST, ElementType X) {
	if (BST == NULL) {
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else
	{
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);
		else if (X > BST->Data)
			BST->Right = Insert(BST->Right, X);
	}
	return BST;
}
BinTree DeleteMin(BinTree BST) {
	Position tmp;
	if (BST) {
		if (BST->Left) {
			if (BST->Left->Left) {
				BST->Left = DeleteMin(BST->Left);
			}
			tmp = BST->Left;
			BST->Left = tmp->Right;
			free(tmp);
			return BST;
		}
		Position tmp = BST;
		BST = BST->Right;
		free(tmp);
		return BST;
	}
	return NULL;
}
BinTree Delete(BinTree BST, ElementType X) {
	Position TmpCell;
	if (!BST) {
		printf("Not Found\n");
	}
	else if (X < BST->Data)
		BST->Left = Delete(BST->Left, X);
	else if (X > BST->Data)
		BST->Right = Delete(BST->Right, X);
	else if (BST->Left&&BST->Right)
	{
		TmpCell = FindMin(BST->Right);
		BST->Data = TmpCell->Data;
		BST->Right = DeleteMin(BST->Right);
	}
	else
	{
		TmpCell = BST;
		if (BST->Left)
			BST = BST->Left;
		else
			BST = BST->Right;
		free(TmpCell);
	}
	return BST;
}
/*
BinTree Delete(BinTree BST, ElementType X)
{
if (!BST)
printf("Not Found\n");
else
{
if (X < BST->Data)
{
BST->Left = Delete(BST->Left, X);
}
else if (X > BST->Data)
{
BST->Right = Delete(BST->Right, X);
}
else
{
if (BST->Left&&BST->Right)
{
BinTree Temp = FindMin(BST->Right);
BST->Data = Temp->Data;
BST->Right = Delete(BST->Right, Temp->Data);
}
else
{
BinTree Temp=BST;
if (BST->Left)
{
BST = BST->Left;
}
else
{
BST = BST->Right;
}
free(Temp);
}
}
}

return BST;
}
*/
Position Find(BinTree BST, ElementType X) {
	if (!BST) {
		return NULL;
	}
	else if (X < BST->Data)
		return Find(BST->Left, X);
	else if (X > BST->Data)
		return Find(BST->Right, X);
	return BST;
}
Position FindMin(BinTree BST) {
	if (BST) {
		while (BST->Left != NULL) {
			BST = BST->Left;
		}
	}
	return BST;
}
Position FindMax(BinTree BST) {
	if (BST) {
		while (BST->Right != NULL) {
			BST = BST->Right;
		}
	}
	return BST;
}

void PreorderTraversal(BinTree BT) /* 先序遍历，由裁判实现，细节不表 */
{
	if (BT) {
		printf("%d ", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}
void InorderTraversal(BinTree BT)  /* 中序遍历，由裁判实现，细节不表 */
{
	if (BT) {
		InorderTraversal(BT->Left);
		printf("%d ", BT->Data);
		InorderTraversal(BT->Right);
	}
}