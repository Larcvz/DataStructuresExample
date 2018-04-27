/*
1.根据输入建堆
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ch[256];

struct TreeNode;
struct Node;
struct HeapStruct;
struct InputNode;

typedef struct TreeNode TreeNode;
typedef TreeNode *HuffmanTree;
typedef struct InputNode *TestCase;
typedef struct HeapStruct *Heap;
typedef struct Node ElementType;
Heap Initialize(int MaxElements);
void PercolateDown(Heap H, int P);
void BuildHeap(Heap H);
void Insert(HuffmanTree X,Heap H);
HuffmanTree DeleteMin(Heap H);

HuffmanTree Huffman(Heap H);

struct Node
{
	char code;
	int weight;
};

struct HeapStruct
{
	int Capacity;
	int Size;
	HuffmanTree *Elements;
};

struct TreeNode
{
	ElementType Data;
	HuffmanTree Left, Right;
};

struct InputNode
{
	char ch;
	char code[9];
};

int getWpl(HuffmanTree T,int len)
{
	int sum = 0;
	if (T->Left)
		sum += getWpl(T->Left, len + 1) + getWpl(T->Right, len + 1);
	else
		return len * ch[T->Data.code];
	return sum;
}

int isPrefix(char *s1, char *s2) {      //判断两个字符串是否属于前缀码关系  
	while (*s1 && *s2 && *s1 == *s2)      //循环至第一个不相同的字母或结束位置  
		++s1, ++s2;
	if (*s1 == '\0' || *s2 == '\0')     //如果此时有一个到达结束位置，说明这个字符串一定是另一个字符串的前缀  
		return 1;
	else
		return 0;
}

int hasPrefixCode(TestCase T, int n) {//判断n个字符串是否含有前缀码  
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (isPrefix(T[i].code, T[j].code))   //两两做对比  
				return 1;
	return 0;
}

int main()
{
	int N, M, i;

	scanf("%d", &N);

	Heap H = Initialize(N);

	for ( i = 1; i <= H->Capacity; i++)
	{
		H->Elements[i] = (HuffmanTree)malloc(sizeof(struct TreeNode));
		H->Elements[i]->Left = NULL;
		H->Elements[i]->Right = NULL;
		scanf(" %c%d", &H->Elements[i]->Data.code, &H->Elements[i]->Data.weight);
		ch[H->Elements[i]->Data.code] = H->Elements[i]->Data.weight;
		H->Size++;
	}

	HuffmanTree huffman = Huffman(H);
	scanf("%d", &M);
	TestCase testcase = (TestCase)malloc(sizeof(struct InputNode)*N);
	int wpl = getWpl(huffman, 0);
	while (M--)
	{
		int thisWPL = 0;
		for ( i = 0; i < N; i++)
		{
			scanf(" %c%s", &testcase[i].ch, testcase[i].code);
			thisWPL += ch[testcase[i].ch] * strlen(testcase[i].code);
		}
		if (wpl == thisWPL && !hasPrefixCode(testcase, N))
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
//堆的函数
Heap Initialize(int MaxElements)
{
	Heap H = (Heap)malloc(sizeof(struct HeapStruct));
	H->Capacity = MaxElements;
	H->Elements = (HuffmanTree*)malloc(sizeof(HuffmanTree)*(MaxElements + 1));
	H->Size = 0;
	H->Elements[0] = (HuffmanTree)malloc(sizeof(struct TreeNode));
	H->Elements[0]->Left = NULL;
	H->Elements[0]->Right = NULL;
	H->Elements[0]->Data.weight = -1;
	H->Elements[0]->Data.code = '\0';

	return H;
}

void BuildHeap(Heap H)
{
	int i;
	for (i = H->Size / 2; i > 0; i--)
	{
		PercolateDown(H, i);
	}
}

void PercolateDown(Heap H, int P)
{
	int i, child;
	HuffmanTree LastElement;

	LastElement = H->Elements[P];

	for (i = P; i * 2 <= H->Size; i = child)
	{
		child = 2 * i;
		if (child < H->Size&&H->Elements[child + 1]->Data.weight < H->Elements[child]->Data.weight)
			child++;
		if (H->Elements[child]->Data.weight < LastElement->Data.weight)
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
}

HuffmanTree DeleteMin(Heap H)
{
	int i, child;
	HuffmanTree MinElement, LastElement;

	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for ( i = 1; i*2 <= H->Size; i=child)
	{
		child = 2 * i;
		if (child < H->Size&&H->Elements[child + 1]->Data.weight < H->Elements[child]->Data.weight)
			child++;
		if (H->Elements[child]->Data.weight < LastElement->Data.weight)
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

void Insert(HuffmanTree X, Heap H)
{
	int i;
	
	for ( i = ++H->Size; H->Elements[i/2]->Data.weight > X->Data.weight; i/=2)
	{
		H->Elements[i] = H->Elements[i / 2];
	}
	H->Elements[i] = X;
}
//哈夫曼码的函数
HuffmanTree Huffman(Heap H)
{
	int i, t;
	HuffmanTree T;
	BuildHeap(H);
	t = H->Capacity;
	for ( i = 1; i < t; i++)
	{
		T = (HuffmanTree)malloc(sizeof(struct TreeNode));
		T->Data.code = '\0';
		T->Left = DeleteMin(H);
		T->Right = DeleteMin(H);
		T->Data.weight = T->Left->Data.weight + T->Right->Data.weight;
		Insert(T, H);
	}
	T = DeleteMin(H);
	return T;
}