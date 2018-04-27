#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef struct QNode *Queue;
typedef struct Data ElementType;

struct Data
{
	int x, y, z;
};

struct Node
{
	ElementType Data;
	PtrToNode Next;
};

struct QNode
{
	Position Front, Rear, Head;
	int Size;
};

Queue CreateQueue()
{
	Queue Q;

	Q = (Queue)malloc(sizeof(struct QNode));
	Q->Front = NULL;
	Q->Rear = NULL;
	Q->Head = NULL;
	Q->Size = 0;

	return Q;
}

int IsEmpty(Queue Q)
{
	return Q->Front == NULL;
}

void Enqueue(PtrToNode X,Queue Q)
{
	++Q->Size;
	X->Next = NULL;
	if (IsEmpty(Q))
		Q->Front = X;
	else
		Q->Rear->Next = X;
	Q->Rear = X;
}

void Dequeue(Queue Q)
{
	if (IsEmpty(Q))
		return;
	else
	{
		PtrToNode FrontCell;

		FrontCell = Q->Front;
		if (Q->Front == Q->Rear)
			Q->Front = Q->Rear = NULL;
		else
			Q->Front = FrontCell->Next;

		free(FrontCell);
	}
}

int Find(ElementType data, Queue Q)
{
	PtrToNode T;

	T = Q->Head;
	while (T)
	{
		if (T->Data.x == data.x&&T->Data.y == data.y&&T->Data.z == data.z)
			return 1;
		T = T->Next;
	}

	return 0;
}

void DisposeQueue(Queue Q)
{
	PtrToNode T;

	while (Q->Head)
	{
		T = Q->Head;
		Q->Head = T->Next;
		free(T);
	}
}

void Dis(int *from, int *to,int tfull)
{
	if (*from + *to > tfull)
	{
		 *from= *from - tfull + *to;
		*to = tfull;
	}
	else
	{
		*to += *from;
		*from = 0;
	}
}

int Judgment(Queue Q, int xfull, int yfull, int zfull, int targ)
{
	ElementType data;
	PtrToNode P;

	while (!IsEmpty(Q))
	{
		int i;
		if (Q->Front->Data.x == targ || Q->Front->Data.y == targ || Q->Front->Data.z == targ)
				return 1;
		for ( i = 0; i < 6; i++)
		{
			data = Q->Front->Data;
			switch (i)
			{
			case 0:
				if (data.x==0)
					break;
				Dis(&data.x, &data.y, yfull);
				if (Find(data, Q))
					break;
				P = (PtrToNode)malloc(sizeof(struct Node));
				P->Data = data;
				Enqueue(P, Q);
				break;
			case 1:
				if (data.x == 0)
					break;
				Dis(&data.x, &data.z, zfull);
				if (Find(data, Q))
					break;
				P = (PtrToNode)malloc(sizeof(struct Node));
				P->Data = data;
				Enqueue(P, Q);
				break;
			case 2:
				if (data.y == 0)
					break;
				Dis(&data.y, &data.x, xfull);
				if (Find(data, Q))
					break;
				P = (PtrToNode)malloc(sizeof(struct Node));
				P->Data = data;
				Enqueue(P, Q);
				break;
			case 3:
				if (data.y == 0)
					break;
				Dis(&data.y, &data.z, zfull);
				if (Find(data, Q))
					break;
				P = (PtrToNode)malloc(sizeof(struct Node));
				P->Data = data;
				Enqueue(P, Q);
				break;
			case 4:
				if (data.z == 0)
					break;
				Dis(&data.z, &data.x, xfull);
				if (Find(data, Q))
					break;
				P = (PtrToNode)malloc(sizeof(struct Node));
				P->Data = data;
				Enqueue(P, Q);
				break;
			case 5:
				if (data.z == 0)
					break;
				Dis(&data.z, &data.y, yfull);
				if (Find(data, Q))
					break;
				P = (PtrToNode)malloc(sizeof(struct Node));
				P->Data = data;
				Enqueue(P, Q);
				break;
			default:
				break;
			}
		}

		Q->Front = Q->Front->Next;
	}

	return 0;
}

void Run(int xfull,int yfull,int zfull,int targ)
{
	int x, y, z;
	Queue Q;
	PtrToNode P;

	
	x = xfull; y = z = 0;
	Q = CreateQueue();
	P = (PtrToNode)malloc(sizeof(struct Node));
	P->Data.x = x;
	P->Data.y = y;
	P->Data.z = z;

	Enqueue(P, Q);
	Q->Head = P;

	if (Judgment(Q, xfull, yfull, zfull, targ))
		printf("YES\n");
	else
		printf("NO\n");

	DisposeQueue(Q);
}

int main()
{
	int xfull, yfull, zfull, targ;

	while (scanf("%d%d%d%d", &xfull, &yfull, &zfull, &targ)!=EOF)
	{
		Run(xfull,yfull,zfull,targ);
	}

	return 0;
}