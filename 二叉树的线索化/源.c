/*
 �������Ĺ����ǽ�������ָ��ָ��ǰ����ǰ����㣬������ָ��ָ���̽�㣬�������������˳��
 ������������������Ҫ�õ�һ��ָ��ǰ������ָ��pre�͵�ǰ����ָ��p����Ȼ��һ�������û��ǰ������
 ���ǿ�ʼ�ĵ�һ��Ӧ��дΪInThread(p,NULL);����������������ʹ����p�����p��������Ϊ�ռ�������
 ���ڽ�������Ϊpre�����pre�����������ھͽ�������Ϊp��Ȼ��pre��Ϊ��ǰ���pȻ�����������p��������
 ��InThread(p->Right,pre);����ڱ���������pre��ָ�����һ�����ý��ض������������Խ�����������Ϊ
 NULL��
 ������������������
 ��������ĵ�һ�����ʵ��Ϊ����������������˵Ľ�㣬Ȼ������ý������������ֱ�ӷ�����������
 ָ��Ľ�㣬���û�оͷ��ʸýڵ�������������˵Ľ��ֱ�����������еĽ�㡣
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
//����������������
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
		pre->Right = NULL;		//������������һ�����
		pre->rtag = 1;
		Inorder(Root);
	}
	return 0;
}