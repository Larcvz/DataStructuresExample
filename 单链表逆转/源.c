#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print(List L); /* 细节在此不表 */

List Reverse(List L);

int main()
{
	List L1, L2;
	L1 = Read();
	L2 = Reverse(L1);
	Print(L1);
	Print(L2);
	return 0;
}

/* 你的代码将被嵌在这里 */
List Reverse(List L)
{
	List P = L, t = NULL, last = P;
	while (P != NULL)
	{
		last = P;
		P = P->Next;
		last->Next = t;
		t = last;		
	}
	return last;
}
List Read()
{
	int n;
	List L, last, p;
	scanf("%d", &n);
	if (n)
	{
		L = (List)malloc(sizeof(struct Node));
		last = L;
		while (n--)
		{
			p = (List)malloc(sizeof(struct Node));
			scanf("%d", &p->Data);
			last->Next = p;
			last = p;
		}
		last->Next = NULL;
		last = L;
		L = L->Next;
		free(last);
		return L;
	}
	else
		return NULL;
}

void Print(List L)
{
	int tag = 0;
	while (L != NULL)
	{
		if (tag)
			printf(" ");
		tag = 1;
		printf("%d", L->Data);
		L = L->Next;
	}
	printf("\n");
}