#include <stdio.h>
#include <stdlib.h>

typedef struct Ptr Ptr;
typedef struct Ptr *Ptrnoimal;
typedef struct Ptr *PtrNode;

struct Ptr 
{
	int coef;
	int expon;
	PtrNode Next;
};
//带头结点
Ptrnoimal creatPtr()
{
	Ptrnoimal ptr = (Ptrnoimal)malloc(sizeof(Ptr)),last=ptr;

	int n;
	scanf("%d", &n);
	while (n--)
	{
		PtrNode p = (PtrNode)malloc(sizeof(Ptr));
		scanf("%d%d", &p->coef, &p->expon);
		last->Next = p;
		last = last->Next;
	}
	last->Next = NULL;

	return ptr;
}

Ptrnoimal Delet(Ptrnoimal ptr)
{
	PtrNode t;
	while (ptr) {
		t = ptr;
		ptr= ptr->Next;
		free(t);
	}
	return NULL;
}

void Print(Ptrnoimal ptr)
{
	int tag = 0;
	if (!ptr->Next)
	{
		printf("0 0\n");
		return;
	}
	while (ptr->Next)
	{
		if (tag)
			printf(" ");
		printf("%d %d", ptr->Next->coef, ptr->Next->expon);
		ptr = ptr->Next;
		tag = 1;
	}
	printf("\n");
}

//加法
Ptrnoimal Add(Ptrnoimal Ptr1, Ptrnoimal Ptr2)
{
	Ptrnoimal ptr = (Ptrnoimal)malloc(sizeof(Ptr)), last = ptr;
	Ptrnoimal p1 = Ptr1->Next, p2 = Ptr2->Next;
	while (p1&&p2)
	{
		PtrNode p = (PtrNode)malloc(sizeof(Ptr));
		if (p1->expon > p2->expon)
		{
			p->coef = p1->coef;
			p->expon = p1->expon;
			last->Next = p;
			p1 = p1->Next;
		}
		else if (p1->expon < p2->expon)
		{
			p->coef = p2->coef;
			p->expon = p2->expon;
			last->Next = p;
			p2 = p2->Next;
		}
		else
		{
			if (p1->coef + p2->coef)
			{
				p->coef = p1->coef + p2->coef;
				p->expon = p1->expon;
				last->Next = p;
				p1 = p1->Next;
				p2 = p2->Next;
			}
			else
			{
				free(p);
				p1 = p1->Next;
				p2 = p2->Next;
				continue;
			}			
		}

		last = last->Next;
	}
	PtrNode t = p1 > p2 ? p1 : p2;
	while (t)
	{
		PtrNode p = (PtrNode)malloc(sizeof(Ptr));
		p->coef = t->coef;
		p->expon = t->expon;
		last->Next = p;
		last = last->Next;
		t = t->Next;
	}
	last->Next = NULL;
	return ptr;
}

//乘法
Ptrnoimal Mult(Ptrnoimal Ptr1, Ptrnoimal Ptr2) {
	Ptrnoimal ptr = (Ptrnoimal)malloc(sizeof(Ptr)), pLast = ptr;
	pLast->Next = NULL;
	PtrNode p1 = Ptr1->Next;
	while (p1)
	{
		PtrNode p2 = Ptr2->Next;
		Ptrnoimal temp = (Ptrnoimal)malloc(sizeof(Ptr)), last = temp;
		while (p2)
		{
			PtrNode p = (PtrNode)malloc(sizeof(Ptr));
			p->coef = p1->coef*p2->coef;
			p->expon = p1->expon + p2->expon;
			last->Next = p;
			last = last->Next;
			p2 = p2->Next;
		}
		last->Next = NULL;
		Ptrnoimal t = ptr;
		ptr = Add(ptr, temp);
		t=Delet(t);
		temp = Delet(temp);
		p1 = p1->Next;
	}
	return ptr;
}

int main()
{
	Ptrnoimal ptr1 = creatPtr();
	Ptrnoimal ptr2 = creatPtr();
	Ptrnoimal ptr_m = Mult(ptr1, ptr2);
	Ptrnoimal ptr_add = Add(ptr1, ptr2);
	Print(ptr_m);
	Print(ptr_add);
	return 0;
}