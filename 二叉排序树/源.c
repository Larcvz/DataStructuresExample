#include <stdio.h>
#include <stdlib.h>	

typedef struct TreeNode *Position;
typedef Position SearchTree;
typedef int ElementType;

struct TreeNode
{
	ElementType element;
	SearchTree left;
	SearchTree right;
};

SearchTree MakeEmpty(SearchTree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}

	return NULL;
}

SearchTree CreateTree()
{
	SearchTree T;

	T = (SearchTree)malloc(sizeof(struct TreeNode));
	T->left = NULL;
	T->right = NULL;

	return T;
}

SearchTree Insert(ElementType X,SearchTree T)
{
	if (T == NULL)
	{
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		T->element = X;
		T->left = NULL;
		T->right = NULL;
	}
	else if (X < T->element)
		T->left = Insert(X, T->left);
	else
		T->right = Insert(X, T->right);
	
	return T;
}

void InOrder(SearchTree T)
{
	if (T != NULL) 
	{
		InOrder(T->left);
		printf("%d ", T->element);
		InOrder(T->right);
	}
}

int main()
{
	int n;
	SearchTree T;

	while (scanf("%d", &n) != EOF)
	{
		T = CreateTree();

		scanf("%d", &T->element);
		while (--n)
		{
			int data;
			
			scanf("%d", &data);
			T = Insert(data, T);
		}
		InOrder(T);
		printf("\n");
		T = MakeEmpty(T);
	}

	return 0;
}