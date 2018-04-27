#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int data;
	struct node *next;
}Node;

Node*  CreateLinkList(int n) {
	Node *head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	Node *last = head, *p;
	while (n--){
		p = (Node*)malloc(sizeof(Node));
		p->next = NULL;
		scanf("%d", &p->data);
		last->next = p;
		last = p;
	}
	return head;
}
Node* Find(Node *head, int x) {
	Node *p = head->next, *t = head;
	while (p && p->data != x){
		t = p;
		p = p->next;
	}
	return t;
}
void Delete(Node *p) {
	Node *t = p->next;
	p->next = t->next;
	free(t);
}
void PrintLinkList(Node *head)
{
	int flag = 0;
	Node *p = head->next, *q;
	while (p)
	{
		if (flag)
			printf(" ");
		flag = 1;
		printf("%d", p->data);
		q = p;
		p = p->next;
		free(q);
	}
	free(head);
}

int main()
{
	int n, x;
	scanf("%d", &n);
	Node *head = CreateLinkList(n);
	scanf("%d", &x);
	Node *p = Find(head, x);
	Delete(p);
	PrintLinkList(head);
	return 0;
}