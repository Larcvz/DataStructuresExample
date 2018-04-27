#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 100

typedef struct StackRecord *Stack;
typedef char *ElementType;

struct StackRecord
{
	int Capacity;
	int Top;
	ElementType Array[MaxSize];
};

Stack CreateStack()			//初始化一个空栈
{
	Stack S;

	S = (Stack)malloc(sizeof(struct StackRecord));

	S->Capacity = MaxSize;
	S->Top = -1;

	return S;
}

int IsFull(Stack S)
{
	return S->Top == S->Capacity - 1;
}

int IsEmpty(Stack S)
{
	return S->Top == -1;
}

void Push(ElementType X, Stack S)
{
	if (IsFull(S)) {
		return;
	}
	S->Array[++S->Top] = X;
}

ElementType Top(Stack S)
{
	return S->Array[S->Top];
}

ElementType Pop(Stack S)
{
	return S->Array[S->Top--];
}

int StringProcessing(char *str)
{
	switch (*str)
	{
	case 'V':return 1;
	case 'B':return 2;
	case 'F':return 3;
	case 'Q':return 0;
	}
	return -1;		//输入有误返回-1
}

void ClearStack(Stack S)
{
	while (!IsEmpty(S))
	{
		free(S->Array[S->Top--]);
	}
}

void Run()
{
	char command[8];
	ElementType url, CurrentURL;
	Stack ForwardStack;
	Stack BackwardStack;

	ForwardStack = CreateStack();
	BackwardStack = CreateStack();
	CurrentURL = (ElementType)malloc(sizeof(char) * 75);
	strcpy(CurrentURL, "http://www.acm.org/");

	while (1)
	{
		scanf("%s", command);
		url = (ElementType)malloc(sizeof(char) * 75);
		switch (StringProcessing(command))
		{
		case 0:	//Quit
			free(url);
			return;
			break;
		case 1:	//Visit
			scanf("%s", url);
			printf("%s\n", url);
			Push(CurrentURL, BackwardStack);
			CurrentURL = url;
			ClearStack(ForwardStack);
			break;
		case 2:	//Back
			free(url);
			if (!IsEmpty(BackwardStack))
			{
				Push(CurrentURL, ForwardStack);
				CurrentURL = Pop(BackwardStack);
				printf("%s\n", CurrentURL);
			}
			else
			{
				printf("Ignored\n");
			}
			break;
		case 3:	//Forward
			free(url);
			if (!IsEmpty(ForwardStack))
			{
				Push(CurrentURL, BackwardStack);
				CurrentURL = Pop(ForwardStack);
				printf("%s\n", CurrentURL);
			}
			else
			{
				printf("Ignored\n");
			}
			break;
		}
	}
}

int main()
{
	Run();
	return 0;
}



