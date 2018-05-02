#include <stdio.h>
#include <stdlib.h>
struct Node
{
	int n;
	struct Node *Next;
};
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node head;
Position last;
void creatList(int n,List head) {
	int i;
	Position p;
	last = head;
	for ( i = 0; i < n; i++)
	{
		p = (struct Node*)malloc(sizeof(struct Node));
		scanf_s("%d", &p->n);
		last->Next = p;
		last = p;
	}
	last->Next = NULL;
}

Position find(int x) {
	Position p = &head;
	if (!x)return p;
	while (--x)
		p = p->Next;
	return p;
}

void insert(int pos) {
	Position p = find(pos);
	int m;
	scanf_s("%d", &m);
	struct Node temp;
	creatList(m, &temp);
	last->Next = p->Next;
	p->Next = temp.Next;
}

void delet(int pos) {
	int m;
	scanf_s("%d", &m);
	Position p = find(pos);
	while (m--&&p->Next != NULL)
	{
		struct Node *tp = p->Next;
		p->Next = tp->Next;
		free(tp);
	}
}

int main()
{
	int t, n, p, pos;
	char c[7];
	scanf_s("%d", &t);
	while (t--)
	{
		scanf_s("%d", &n);
		creatList(n, &head);
		scanf_s("%d", &p);
		while (p--)
		{
			scanf_s("%s%d", c, 7, &pos);
			if (c[0] == 'i')
				insert(pos);
			else
				delet(pos);
		}
		Position p = &head;
		struct Node *tp;
		p = p->Next;
		if (!p) {
			printf("\n");
			continue;
		}
		printf("%d", p->n);
		tp = p;
		p = p->Next;
		free(tp);
		while (p != NULL) {
			printf(" %d", p->n);
			tp = p;
			p = p->Next;
			free(tp);
		}
		printf("\n");
	}
	return 0;
}