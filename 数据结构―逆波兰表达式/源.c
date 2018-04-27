#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SNode *Stack;
typedef struct SNode SNode;
typedef struct SCNode *Stack_C;
Stack CreateStack(char *str);
double GetOutCome(Stack S);
void DisposeStack(Stack S);
void Push(char *X, Stack S);
char* Pop(Stack S);

struct SCNode
{
	double *Array;
	int Capacity;
	int TopOfStack;
};

struct SNode
{
	char *Data;
	SNode *Next;
};

int main()
{
	char str[101];
	
	while (gets_s(str,100))
	{
		Stack S = CreateStack(str);
		printf("%.2f\n", GetOutCome(S));
		DisposeStack(S);
	}
	return 0;
}

Stack CreateStack(char *str)
{
	int len = strlen(str);
	char *next = str, *end = str + len;
	while (*str)
	{
		if (*str == ' ')
			*str = '\0';
		str++;
	}
	Stack S = (Stack)malloc(sizeof(SNode));
	S->Next = NULL;
	while (next != end + 1)
	{
		Push(next, S);
		next += strlen(next) + 1;
	}
	return S;
}

void Push(char *X, Stack S)
{
	SNode *P = (SNode*)malloc(sizeof(SNode));
	P->Data = X;
	P->Next = S->Next;
	S->Next = P;
}

char* Pop(Stack S)
{
	char *p = S->Next->Data;
	S->Next = S->Next->Next;
	return p;
}

double GetOutCome(Stack S)
{
	Stack_C SC = (Stack_C)malloc(sizeof(struct SCNode));
	SC->Array = (double*)malloc(sizeof(double) * 10000);
	SC->Capacity = 100;
	SC->TopOfStack = -1;
	char *temp;
	double f1, f2;
	while (S->Next != NULL)
	{
		temp = Pop(S);
		switch (*temp)
		{
		case '+':
			f1 = SC->Array[SC->TopOfStack--];
			f2 = SC->Array[SC->TopOfStack--];
			SC->Array[++SC->TopOfStack] = f1 + f2;
			break;
		case '-':
			f1 = SC->Array[SC->TopOfStack--];
			f2 = SC->Array[SC->TopOfStack--];
			SC->Array[++SC->TopOfStack] = f1 - f2;
			break;
		case '*':
			f1 = SC->Array[SC->TopOfStack--];
			f2 = SC->Array[SC->TopOfStack--];
			SC->Array[++SC->TopOfStack] = f1 * f2;
			break;
		case '/':
			f1 = SC->Array[SC->TopOfStack--];
			f2 = SC->Array[SC->TopOfStack--];
			SC->Array[++SC->TopOfStack] = f1 / f2;
			break;
		default:
			SC->Array[++SC->TopOfStack] = atof(temp);
			break;
		}
	}
	double outcomt = SC->Array[SC->TopOfStack--];
	free(SC->Array);
	free(SC);
	return outcomt;
}

void DisposeStack(Stack S)
{
	if (S->Next)
	{
		Stack t = S->Next;
		S->Next = t->Next;
		free(t);
	}
}
