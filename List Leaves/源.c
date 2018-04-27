#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	int index;
	BinTree Left;
	BinTree Right;
};

BinTree CreatTree(int N) {
	Position *child = (Position*)malloc(sizeof(Position)*N);
	int i, tag[10] = { 0 };
	for (i = 0; i < N; i++)
	{
		child[i] = (Position)malloc(sizeof(struct TNode));
		child[i]->index = i;
	}
	for (i = 0; i < N; i++)
	{
		char left, right;
		scanf(" %c %c", &left, &right);
		if (left == '-')
		{
			child[i]->Left = NULL;
		}
		else
		{
			child[i]->Left = child[left - '0'];
			tag[left - '0'] = 1;
		}
		if (right == '-')
		{
			child[i]->Right = NULL;
		}
		else
		{
			child[i]->Right = child[right - '0'];
			tag[right - '0'] = 1;
		}
	}
	for (i = 0; i < N; i++)
	{
		if (!tag[i])return child[i];
	}
	return NULL;
}

void PrintLeaf(BinTree root) {
	int front, rear, tag = 0;
	Position que[30];
	front = rear = 0;
	que[rear++] = root;
	while (front < rear)
	{
		if (que[front]) {
			if (que[front]->Left == NULL && que[front]->Right == NULL) {
				if (tag) {
					printf(" ");
				}
				tag = 1;
				printf("%d", que[front]->index);
			}
			que[rear++] = que[front]->Left;
			que[rear++] = que[front]->Right;
		}
		front++;
	}
}

int main()
{
	int N;
	BinTree root;
	scanf("%d", &N);
	root = CreatTree(N);
	PrintLeaf(root);
	printf("\n");
	return 0;
}