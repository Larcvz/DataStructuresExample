#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack S);//检测是否为空栈
Stack CreateStack();
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(char x, Stack S);//入栈
char Pop(Stack S);//出栈

struct Node
{
	char Element;
	PtrToNode Next;
};

int IsEmpty(Stack S) {
	return S->Next == NULL;
}

Stack CreateStack() {
	Stack S;
	S = (Stack)malloc(sizeof(struct Node));
	if (S==NULL)
	{
		printf("Out of space!");
	}
	S->Next = NULL;
	MakeEmpty(S);
	return S;
}

void MakeEmpty(Stack S) {
	if (S == NULL)
		printf("Must use CreateStack first");
	else
		while (!IsEmpty(S))
			Pop(S);
}

void Push(char X, Stack S) {
	PtrToNode TmpCell;

	TmpCell = (Stack)malloc(sizeof(struct Node));
	if (TmpCell == NULL)
		printf("Out of space!");
	else
	{
		TmpCell->Element = X;
		TmpCell->Next = S->Next;
		S->Next = TmpCell;
	}
}

char Pop(Stack S) {
	PtrToNode FirstCell;
	char c;
	if (IsEmpty(S))
		printf("Empty stack");
	else
	{
		FirstCell = S->Next;
		S->Next = S->Next->Next;
		c = FirstCell->Element;
		free(FirstCell);
	}
	return c;
}

void DisposeStack(Stack S) {
	while (!IsEmpty(S))
	{
		Pop(S);
	}
	free(S);
}

bool isHigh(char top_op, char InfixExp_op)
{
	if ((top_op == '+') && (InfixExp_op == '+')) return true;
	if ((top_op == '+') && (InfixExp_op == '-')) return true;
	if ((top_op == '-') && (InfixExp_op == '+')) return true;
	if ((top_op == '-') && (InfixExp_op == '-')) return true;
	if (InfixExp_op == ')') return true;
	return false;
}

char* make(char *str) {
	Stack S = CreateStack();
	Push('#', S);
	char *str_c = (char*)malloc(sizeof(char) * 100);
	int i = 0, lable = 0;
	while (*str)
	{
		if (*str >= '0'&&*str <= '9')
		{
			str_c[i++] = *str;
			lable = 0;
		}
		else
		{
			while (!IsEmpty(S) && isHigh(S->Next->Element, *str))
			{
				if (S->Next->Element == '(') {
					Pop(S);
					break;
				}
				else
					str_c[i++] = Pop(S);
			}
			if (*str != ')') {
				if (S->Next->Element == '('&&*str == '-' && lable) {
					str_c[i++] = '0';
				}
				if (*str == '(')lable = 1;
				Push(*str, S);
			}
		}
		str++;
	}
	while (!IsEmpty(S))
	{
		str_c[i++] = Pop(S);
	}
	str_c[--i] = '\0';
	return str_c;
}

int Math(char *str)
{
	int sum[100] = { 0 };
	int i = 0, lable = 1;
	if (*(str + 1) == '-')lable = 0;
	while (*str)
	{
		if (*str >= '0'&&*str <= '9') {
			sum[++i] = *str - '0';
		}
		else
		{
			switch (*str)
			{
				case '-':sum[i - 1] = sum[i - 1] - sum[i], i--; break;
				case '+':sum[i - 1] = sum[i - 1] + sum[i], i--; break;
				default:printf("格式错误!"); break;
			}
		}
		str++;
	}
	return sum[lable];
}

int main()
{
	char str[41];
	int n;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", str);
		char *Tmp = make(str);
		printf("%d\n", Math(Tmp));
	}
	return 0;
}