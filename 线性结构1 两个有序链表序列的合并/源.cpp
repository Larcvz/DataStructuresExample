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
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
	List L1, L2, L;
	L1 = Read();
	L2 = Read();
	L = Merge(L1, L2);
	Print(L);
	Print(L1);
	Print(L2);
	return 0;
}

/* 你的代码将被嵌在这里 */
List Read() {
	PtrToNode head, last, p;
	head = (PtrToNode)malloc(sizeof(struct Node));
	last = head;
	int n;
	scanf("%d", &n);
	while (n--)
	{
		p = (PtrToNode)malloc(sizeof(struct Node));
		scanf("%d", &p->Data);
		last->Next = p;
		last = last->Next;
	}
	last->Next = NULL;
	return head;
}

List Merge(List L1, List L2) {
	List L = (PtrToNode)malloc(sizeof(struct Node)), last = L;
	while (L1->Next&&L2->Next)
	{
		if (L1->Next->Data < L2->Next->Data) 
		{
			last->Next = L1->Next;
			L1->Next = L1->Next->Next;
		}
		else if (L1->Next->Data > L2->Next->Data)
		{
			last->Next = L2->Next;
			L2->Next = L2->Next->Next;
		}
		else
		{
			last->Next = L1->Next;
			L1->Next = L1->Next->Next;
			last = last->Next;
			last->Next = L2->Next;	
			L2->Next = L2->Next->Next;
		}
		last = last->Next;
	}
	if (L1->Next)
	{
		last->Next = L1->Next;
		L1->Next = NULL;
	}
	else 
	{
		last->Next = L2->Next;
		L2->Next = NULL;
	}
	return L;
}

void Print(List L) {
	int tag = 0;
	if (!L->Next) 
	{
		printf("NULL\n");
		return;
	}
	while (L->Next)
	{
		if (tag)
			printf(" ");
		printf("%d", L->Next->Data);
		L = L->Next;
		tag = 1;
	}
	printf("\n");
}