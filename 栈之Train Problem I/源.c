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
			while (*inorder&&*inorder != *outorder)	//将与outorder不一样的依次放入栈中如果最后*inorder为'\0'则表示不可以按照outorder出栈
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
			log[i] = 0;			//由于入栈在判断到两个相同时就退出了所以，相同的两个元素并没有入栈需要在这里完成类似出栈的操作
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
	int log[MaxSize * 2];	//用来记录Push和Pop的操作 Push为1，Pop为0
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