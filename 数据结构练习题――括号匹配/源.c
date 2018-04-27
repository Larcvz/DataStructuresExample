#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 1000

typedef struct StackRecord *Stack;
typedef char ElementType;

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

void Pop(Stack S)
{
	if (IsEmpty(S))
		exit(1);
	S->Top--;
}

int Judgment(Stack S, char str[])	// 0:wrong 1:miss left 2:miss right 3:match
{
	while (*str)
	{
		if (!strchr("{[()]}",*str))
			++str;
		else if (*str == '{' || *str == '[' || *str == '(')
		{
			Push(*str, S);
			++str;
		}
		else
		{
			if (IsEmpty(S))
				return 1;
			if ((*str == '}'&&Top(S) == '{') || (*str == ']'&&Top(S) == '[') || (*str == ')'&&Top(S) == '(')) 	
			{
				++str;
				Pop(S);
			}
			else
				return 0;
		}
	}
	if (IsEmpty(S))
		return 3;
	return 2;
}

void Run()
{
	Stack S;
	int i, n, t;
	char str[MaxSize + 1];

	scanf("%d", &t);
	
	while (t--)
	{
		scanf("%s", str);

		n = strlen(str);
		S = CreateStack(n);

		switch (Judgment(S, str))
		{
		case 0:
			printf("wrong\n"); break;
		case 1:
			printf("miss left\n"); break;
		case 2:
			printf("miss right\n"); break;
		case 3:
			printf("match\n"); break;
		}
		free(S);
	}

}

int main()
{
	Run();
	return 0;
}