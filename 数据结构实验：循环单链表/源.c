#include <stdio.h>
#include <stdlib.h>
typedef struct List Node;
struct List {
	int elm;
	Node *next;
};
Node* CreateLinkList(int n) {
	Node *head = (Node*)malloc(sizeof(Node)), *p, *last;
	last = head;
	while (n--)
	{
		p = (Node*)malloc(sizeof(Node));
		scanf("%d", &p->elm);
		last->next = p;
		last = p;
	}
	last->next = head->next;
	free(head);
	return last->next;
}
void Destroy(Node* head)
{
	Node *p;
	while (head->next != head)
	{
		p = head->next;
		head->next = p->next;
		free(p);
	}
	free(head);
}
Node* Find(Node *head, int x) {
	while (head->elm != x)
		head = head->next;
	return head;
}
void PrintLinkList(Node *head, int x) {
	Node *p = Find(head, x);
	head = p;
	printf("%d", p->elm);
	while (p->next != head) {
		p = p->next;
		printf(" %d", p->elm);
	}
	printf("\n");
}
int main()
{
	int n, x;
	scanf("%d", &n);
	Node *head = CreateLinkList(n);
	while (scanf("%d", &x) != EOF)
	{
		PrintLinkList(head, x);
	}
	Destroy(head);
	return 0;
}