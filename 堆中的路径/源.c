#include <stdio.h>
#include <stdlib.h>

struct HeapStruct;
typedef struct HeapStruct *Heap;
typedef Heap MaxHeap;
typedef Heap MinHeap;
typedef int ElementType;

Heap Initialize(int MaxSize);
//void Destroy(Heap H);
//void MakeEmpty(Heap H);
void Insert(ElementType X, Heap H);
void PercolateDown(Heap H, int P);
void BuildHeap(Heap H);
//ElementType DeleteMin(Heap H);
//ElementType FindMin(Heap H);
int IsEmpty(Heap H);
int IsFull(Heap H);
void Print(Heap H, int p);

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

int main()
{
	int N, M, d;
	scanf("%d%d", &N, &M);
	Heap H = Initialize(N);
	while (!IsFull(H))
	{
		scanf("%d", &d);
		Insert(d, H);
	}
	//BuildHeap(H);
	int i;
	while (M--)
	{
		scanf("%d", &i);
		Print(H, i);
	}
	return 0;
}

void Print(Heap H, int P)
{
	int tag = 0;
	while (P)
	{
		if (tag)
			printf(" ");
		printf("%d", H->Elements[P]);
		tag = 1;
		P /= 2;
	}
	printf("\n");
}

Heap Initialize(int MaxSize)
{
	Heap H;
	if (MaxSize <= 0)
		return NULL;
	
	H = (Heap)malloc(sizeof(struct HeapStruct));
	H->Capacity = MaxSize;
	H->Elements = (ElementType*)malloc(sizeof(ElementType)*(MaxSize+1));
	
	H->Elements[0] = -10001;
	H->Size = 0;

	return H;
}

void Insert(ElementType X, Heap H)
{
	if (IsFull(H))
	{
		printf("Heap is Full");
		return;
	}
	int i = ++H->Size;
	for (; X < H->Elements[i / 2]; i /= 2)
	{
		H->Elements[i] = H->Elements[i / 2];
	}
	H->Elements[i] = X;
}

void BuildHeap(Heap H)
{
	int i;
	for ( i = H->Size/2; i >0 ; i--)
	{
		PercolateDown(H, i);
	}
}

void PercolateDown(Heap H, int P)
{
	int i, child;
	ElementType LastElement;

	if (IsEmpty(H))
	{
		printf("Heap is Empty");
		return;
	}

	LastElement = H->Elements[P];

	for (i = P; i * 2 <= H->Size; i = child)
	{
		child = 2 * i;
		if (child != H->Size&&H->Elements[child + 1] < H->Elements[child])
			child++;
		if (LastElement > H->Elements[child])
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
}

int IsFull(Heap H)
{
	return H->Capacity == H->Size;
}

int IsEmpty(Heap H)
{
	return H->Size == 0;
}