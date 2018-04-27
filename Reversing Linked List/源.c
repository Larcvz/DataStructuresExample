#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100000
#define Null -1
typedef struct Node ElementType;
typedef int Position;
struct Node
{
	int data;
	int next;
};

struct list
{
	ElementType Data[MAXSIZE];
	Position Head;
}List;

void CreateList(int N) {
	int address;
	while (N--){
		scanf("%d", &address);
		scanf("%d%d", &List.Data[address].data, &List.Data[address].next);
	}
}

Position ReversingList(int K, Position head, int N) {
	if (N < K) {
		return head;
	}
	Position Last = head;
	Position P = List.Data[head].next;
	Position Q = Last;
	int i;
	for (i = 1; i < K; i++) {
		Q = P;
		P = List.Data[P].next;
		List.Data[Q].next = Last;
		Last = Q;
	}

	List.Data[head].next = ReversingList(K, P, N - K);
	return Last;
}

void PrintList() {
	Position P = List.Head;
	while (P!=Null)
	{
		printf("%05d %d", P, List.Data[P].data);
		if (List.Data[P].next != Null) 
			printf(" %05d\n", List.Data[P].next);
		else 
			printf(" %d\n", List.Data[P].next);
		P = List.Data[P].next;
	}
}
int listlen(){
	Position p = List.Head;
	int len = 0;
	while (p != Null) {
		len++;
		p = List.Data[p].next;
	}
	return len;
}
int main()
{
	int K, N, len;
	scanf("%d%d%d", &List.Head, &N, &K);
	CreateList(N);
	len = listlen();
	List.Head = ReversingList(K, List.Head, len);
	PrintList();
	return 0;
}