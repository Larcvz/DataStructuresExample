#include <stdio.h>
#include <stdlib.h>

#define MaxNodeNum 1000
int tag = 0;

typedef struct BinaryTree *BiTNode;
typedef BiTNode BiTree;
typedef int ElementType;
struct BinaryTree
{
	ElementType Element;
	BiTNode Left, Right;
};

BiTree CreateBiTree()
{
	BiTree root;
	BiTNode *Queue[MaxNodeNum];
	int data, Front = 0, Rear = 0;

	root = NULL;
	Queue[Rear++] = &root;
	while (scanf("%d", &data), data != -1)
	{
		BiTNode *T = Queue[Front++];
		if (data != 0)
		{
			*T = (BiTNode)malloc(sizeof(struct BinaryTree));
			(*T)->Left = NULL;
			(*T)->Right = NULL;
			(*T)->Element = data;
			Queue[Rear++] = &(*T)->Left;
			Queue[Rear++] = &(*T)->Right;
		}
		else
		{
			Queue[Rear++] = NULL;
			Queue[Rear++] = NULL;
		}
	}

	return root;
}

void PreOrderTraverse(BiTree root)
{
	if (root != NULL)
	{
		printf(" %d", root->Element);
		tag = 1;
		PreOrderTraverse(root->Left);
		PreOrderTraverse(root->Right);
	}
}

void InOrderTraverse(BiTree root)
{
	if (root != NULL)
	{
		InOrderTraverse(root->Left);
		printf(" %d", root->Element);
		InOrderTraverse(root->Right);
	}
}

void PostOrderTraverse(BiTree root)
{
	if (root != NULL)
	{
		PostOrderTraverse(root->Left);
		PostOrderTraverse(root->Right);
		printf(" %d", root->Element);
	}
}

//void LevelOrderTraverse(BiTree root)
//{
//	BiTNode Queue[MaxNodeNum], T;
//	int Front = 0, Rear = 0;
//	int tag = 0;
//
//	Queue[Rear++] = root;
//	while (Front < Rear)
//	{
//		T = Queue[Front++];
//		if (T != NULL)
//		{
//			/*if (tag == 1)
//				printf(" ");*/
//			printf(" %d", T->Element);
//			Queue[Rear++] = T->Left;
//			Queue[Rear++] = T->Right;
//		}
//	}
//	printf("\n");
//}

void DestroyBiTree(BiTree T)
{
	if (T != NULL)
	{
		DestroyBiTree(T->Left);
		DestroyBiTree(T->Right);
		free(T);
	}
}

int main()
{
	BiTree Root;
	int n;

	scanf("%d", &n);
	while (n--)
	{
		Root = CreateBiTree();
		PreOrderTraverse(Root); printf("\n");
		InOrderTraverse(Root); printf("\n");
		PostOrderTraverse(Root); printf("\n");
		DestroyBiTree(Root);
	}

	return 0;
}