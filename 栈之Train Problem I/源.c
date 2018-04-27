#include <stdio.h>
#include <stdlib.h>

#define MaxSize 9

typedef struct StackRecord *Stack;
typedef int ElementType;

struct StackRecord
{
	int Capacity;
	int Top;
	ElementType Array[MaxSize];
};

Stack CreateStack(int n)
{
	Stack S;
	
	S = (Stack)malloc(sizeof(struct StackRecord));
	S->Capacity = n;
	S->Top = -1;

	return S;
}

int IsEmpty(Stack S)
{
	return S->Top == -1;
}

int IsFull(Stack S)
{
	return S->Top == S->Capacity - 1;
}

void Push(ElementType X, Stack S)
{
	if (IsFull(S))
		exit(1);
	S->Array[++S->Top] = X;
}

ElementType Top(Stack S)
{
	if (IsEmpty(S))
		exit(1);
	return S->Array[S->Top];
}

ElementType Pop(Stack S)
{
	if (IsEmpty(S))
		exit(1);
	return S->Array[S->Top--];
}

int Judgment(Stack S,char inorder[],char outorder[],int log[])
{
	int i = 0;
	while (*outorder)
	{
		if (!IsEmpty(S)&&Top(S)==*outorder-'0')
		{
			Pop(S);
			log[i] = 0;
			++i;
			++outorder;
		}
		else
		{
			while (*inorder&&*inorder != *outorder)	//����outorder��һ�������η���ջ��������*inorderΪ'\0'���ʾ�����԰���outorder��ջ
			{
				Push(*inorder - '0', S);
				log[i] = 1;
				++i;
				++inorder;
			}
			if (*inorder == '\0')
				return 0;
			log[i] = 1;
			++i;
			log[i] = 0;			//������ջ���жϵ�������ͬʱ���˳������ԣ���ͬ������Ԫ�ز�û����ջ��Ҫ������������Ƴ�ջ�Ĳ���
			++inorder;
			++outorder;
			++i;
		}

	}

	return 1;
}

void Run(int n)
{
	
	Stack S;
	char inorder[MaxSize], outorder[MaxSize];
	int log[MaxSize * 2];	//������¼Push��Pop�Ĳ��� PushΪ1��PopΪ0
	int i;

	scanf("%s%s", inorder, outorder);

	S = CreateStack(n);

	if (Judgment(S,inorder, outorder, log))
	{
		printf("Yes.\n");
		for ( i = 0; i < n*2; i++)
		{
			if (log[i])
				printf("in\n");
			else
				printf("out\n");
		}
	}
	else
	{
		printf("No.\n");
	}
	printf("FINISH\n");
	free(S);
}

int main()
{
	int n;

	while (scanf("%d",&n) != EOF)
	{
		Run(n);
	}
	return 0;
}