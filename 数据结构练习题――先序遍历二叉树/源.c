/*
后序遍历和中序遍历和本题就是换一个遍历方式而已就不重新建项目了
*/
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

void DestroyBiTree(BiTree T)
{
	if (T != NULL)
	{
		DestroyBiTree(T->Left);
		DestroyBiTree(T->Right);
		free(T);
	}
}

int GetDepth(BiTree T)
{
	if (T == NULL)
		return 0;
	else
	{
		int leftDepth = GetDepth(T->Left);
		int rightDepth = GetDepth(T->Right);
		return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
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
		int depth;

		depth = GetDepth(Root);
		printf("%d", depth);
		PreOrderTraverse(Root); printf("\n");
		//PostOrderTraverse(Root); printf("\n");
		//InOrderTraverse(Root); printf("\n");
		DestroyBiTree(Root);
	}

	return 0;
}