/*
 线索化的规则是将左线索指针指向当前结点的前驱结点，右线索指针指向后继结点，利用中序遍历的顺序
 将二叉树线索化，需要用到一个指向前驱结点的指针pre和当前结点的指针p，显然第一个结点是没有前驱结点的
 于是开始的第一步应该写为InThread(p,NULL);按照中序遍历当访问过结点p后，如果p的左子树为空即左线索
 存在将其设置为pre，如果pre的右线索存在就将其设置为p，然后将pre设为当前结点p然后再中序遍历p的右子树
 即InThread(p->Right,pre);最后在遍历结束后pre会指向最后一个结点该结点必定有右线索所以将右线索设置为
 NULL。
 遍历中序线索二叉树
 中序遍历的第一个结点实际为所给二叉树的最左端的结点，然后如果该结点有右线索则直接访问右线索所
 指向的结点，如果没有就访问该节点右子树的最左端的结点直到遍历玩所有的结点。
*/
#include <stdio.h>
#include <stdlib.h>

#define MaxNodeNum 1000

typedef struct Node *TBTNode;
typedef TBTNode TBTree;
struct Node
{
	int data;
	int ltag, rtag;
	TBTNode Left, Right;
};
//中序遍历构造二叉树
TBTree CreateTree()
{
	TBTree root;
	TBTNode *Queue[MaxNodeNum];
	int data, Front = 0, Rear = 0;

	root = NULL;
	Queue[Rear++] = &root;
	while (scanf("%d", &data), data != -1)
	{
		TBTNode *T = Queue[Front++];
		if (data != 0)
		{
			*T = (TBTNode)malloc(sizeof(struct Node));
			(*T)->Left = NULL;
			(*T)->Right = NULL;
			(*T)->ltag = 0;
			(*T)->rtag = 0;
			(*T)->data = data;
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

void InThread(TBTree P, TBTNode *pre)
{
	if (P != NULL)
	{
		InThread(P->Left, pre);
		if (P->Left == NULL)
		{
			P->Left = *pre;
			P->ltag = 1;
		}
		if ((*pre) != NULL && (*pre)->Right == NULL)
		{
			(*pre)->Right = P;
			(*pre)->rtag = 1;
		}
		*pre = P;
		InThread(P->Right, pre);
	}
}

TBTNode First(TBTree p)
{
	while (p->ltag == 0)
		p = p->Left;
	return p;
}

TBTNode Next(TBTree p)
{
	if (p->rtag == 0)
		return First(p->Right);
	else
		return p->Right;
}

void Inorder(TBTree Root)
{
	TBTNode p;
	for (p = First(Root); p != NULL; p = Next(p))
	{
		printf("%d ", p->data);
	}
	printf("\n");
}

int main()
{
	TBTree Root;
	TBTNode pre;

	pre = NULL;
	Root = CreateTree();
	if (Root != NULL)
	{
		InThread(Root, &pre);
		pre->Right = NULL;		//处理中序的最后一个结点
		pre->rtag = 1;
		Inorder(Root);
	}
	return 0;
}