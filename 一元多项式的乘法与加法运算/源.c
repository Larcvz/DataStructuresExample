#include <stdio.h>
#include <stdlib.h>
typedef struct Ptr {
	int Coefficient;
	int Exponent;
	struct Ptr *Next;
}Ptr;
void DeletList(Ptr *head) {
	Ptr *p = head;
	while (p) {
		Ptr *t = p;
		p = p->Next;
		free(t);
	}
}
void Zero(Ptr *p) {
	p->Coefficient = 0;
	p->Exponent = 0;
	p->Next = NULL;
}
Ptr* creat(int n) {
	Ptr *head, *p, *last;
	head = (Ptr*)malloc(sizeof(Ptr));
	Zero(head);
	last = head;
	while (n--){
		p = (Ptr*)malloc(sizeof(Ptr));
		scanf("%d%d", &p->Coefficient, &p->Exponent);
		last->Next = p;
		last = p;
	}
	last->Next = NULL;
	return head;
}
void Print(Ptr *head) {
	if (!head->Next) {
		printf("0 0");
		return;
	}
	Ptr *p = head->Next;
	printf("%d %d", p->Coefficient, p->Exponent);
	p = p->Next;
	while (p){
		printf(" %d %d", p->Coefficient, p->Exponent);
		p = p->Next;
	}
}
//void InverseList(Ptr *head) {
//	Ptr *p = head->Next, *q;
//	head->Next = NULL;
//	while (p){
//		q = p->Next;
//		p->Next = head->Next;
//		head->Next = p;
//		p = q;
//	}
//}
Ptr* Add(Ptr *p1, Ptr *p2) {
	Ptr *head = (Ptr*)malloc(sizeof(Ptr)), *p, *last, *pa = p1->Next, *pb = p2->Next;
	Zero(head);
	last = head;
	while (pa && pb)
	{
		if (pa->Exponent > pb->Exponent){
			p = (Ptr*)malloc(sizeof(Ptr));
			p->Coefficient = pa->Coefficient;
			p->Exponent = pa->Exponent;
//			p->Next = NULL;
			last->Next = p;
			last = p;
			pa = pa->Next;
		}
		else if (pa->Exponent == pb->Exponent) {
			p = (Ptr*)malloc(sizeof(Ptr));
			p->Coefficient = pa->Coefficient + pb->Coefficient;
			if (p->Coefficient) {
				p->Exponent = pa->Exponent;
//				p->Next = NULL;
				last->Next = p;
				last = p;
			}
			else{
				free(p);
			}
			pa = pa->Next;
			pb = pb->Next;
		}
		else{
			p = (Ptr*)malloc(sizeof(Ptr));
			p->Coefficient = pb->Coefficient;
			p->Exponent = pb->Exponent;
//			p->Next = NULL;
			last->Next = p;
			last = p;
			pb = pb->Next;
		}
	}
	last->Next = NULL;
	Ptr *t = pa > pb ? pa : pb;
	while (t){
		Ptr *p = (Ptr*)malloc(sizeof(Ptr));
		p->Coefficient = t->Coefficient;
		p->Exponent = t->Exponent;
		last->Next = p;
		last = p;
		t = t->Next;
	}
	last->Next = NULL;
	return head;
}
//Ptr* Mult(Ptr *head1, Ptr *head2) {
//	Ptr *head = (Ptr*)malloc(sizeof(Ptr)), *p1 = head1->Next, *p2 = head2->Next, *p, *last;
//	int exp_max, k, coe = 0;
//	Zero(head);
//	if (p1&&p2) {
//		exp_max = p1->Exponent + p2->Exponent;
//	}
//	else {
//		return head;
//	}
//	last = head;
//	InverseList(head2);
//	for (k = exp_max; k >= 0; k--)
//	{
//		p1 = head1->Next;
//		while (p1 && p1->Exponent > k){
//			p1 = p1->Next;
//		}
//		p2 = head2->Next;
//		while (p1 && p2 && p2->Exponent + p1->Exponent < k){
//			p2 = p2->Next;
//		}
//		while (p1 && p2) {
//			if (k == p1->Exponent + p2->Exponent) {
//				coe += p1->Coefficient * p2->Coefficient;
//				p1 = p1->Next;
//				p2 = p2->Next;
//			}
//			else{
//				if (k > p1->Exponent + p2->Exponent){
//					p2 = p2->Next;
//				}
//				else{
//					p1 = p1->Next;
//				}
//			}
//		}
//		if (coe){
//			p = (Ptr*)malloc(sizeof(Ptr));
//			p->Coefficient = coe;
//			p->Exponent = k;
//			p->Next = NULL;
//			last->Next = p;
//			last = p;
//			coe = 0;
//		}
//	}
//	InverseList(head2);
//	return head;
//}
Ptr* Mult(Ptr *head1, Ptr *head2) {
	Ptr *p2 = head1->Next, *p1 = head2->Next;
	Ptr *head = creat(0), *p, *temp, *last;
	if (!(p1&&p2))
		return head;
	while (p1) {
		temp = (Ptr*)malloc(sizeof(Ptr));
		last = temp;
		p2 = head1->Next;
		while (p2) {
			p = (Ptr*)malloc(sizeof(Ptr));
			p->Exponent = p1->Exponent + p2->Exponent;
			p->Coefficient = p1->Coefficient*p2->Coefficient;
			p2 = p2->Next;
			last->Next = p;
			last = p;
		}
		last->Next = NULL;
		head = Add(head, temp);
		DeletList(temp);
		p1 = p1->Next;
	}
	return head;
}
int main()
{
	Ptr *p[2], *p_sum, *p_mult;
	int n, i = 2;
	while (i--) {
		scanf("%d", &n);
		p[i] = creat(n);
	}
	p_sum = Add(p[0], p[1]);
	p_mult = Mult(p[0], p[1]);
	Print(p_mult);
	printf("\n");
	Print(p_sum);
	printf("\n");
	return 0;
}