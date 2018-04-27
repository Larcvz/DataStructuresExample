/*
方法一用了标签tag来记录情况然后来判断时左子树还是右子树
方法二则没有用标签而是记录了出栈是的栈顶元素来判断
*/
//方法一
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	int index;
	BinTree Left;
	BinTree Right;
};

typedef struct Stack
{
	BinTree node[40];
	int top;
}*Stack;

void Push(BinTree node,Stack S) {
	S->node[++S->top] = node;
}

BinTree Pop(Stack S) {
	return S->node[S->top--];
}

BinTree MakeEmpty() {
	BinTree Node = (BinTree)malloc(sizeof(struct TNode));
	Node->Left = NULL;
	Node->Right = NULL;
	return Node;
}

BinTree CreatBinTree(int N) {
	BinTree root, Top;
	Stack S = (Stack)malloc(sizeof(struct Stack));
	S->top = -1;
	int i, data, tag = 0;
	char str[5];
	scanf("%s%d", str, &data);
	root = MakeEmpty();
	root->index = data;
	Push(root, S);
	Top = root;
	for ( i = 1; i < 2*N; i++)
	{
		scanf("%s", str);
		if (!strcmp(str, "Push")) {
			scanf("%d", &data);
			BinTree node = MakeEmpty();
			node->index = data;
			if (tag) {
				Top->Right = node;
				tag = 0;
			}
			else
			{
				Top->Left = node;
			}
			Push(node, S);
			Top = node;
		}
		else
		{
			tag = 1;
			Top = Pop(S);
		}
	}
	return root;
}
void PrintTree(BinTree root) {
	static int tag = 0;
	if (root) {
		PrintTree(root->Left);
		PrintTree(root->Right);
		if (tag) {
			printf(" ");
		}
		printf("%d", root->index);
		tag = 1;
	}
}
int main()
{
	int N;
	scanf("%d", &N);
	BinTree Root = CreatBinTree(N);
	PrintTree(Root);
	printf("\n");
	return 0;
}
//方法二
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode *PtrNode;
typedef struct StackRecord *Stack;
typedef PtrNode Tree;
typedef int ElementType;

struct TNode
{
ElementType Element;
PtrNode Left;
PtrNode Right;
};

struct StackRecord
{
PtrNode *Array;
int Capacity;
int TopOfStack;
};

Stack createStack(int MaxElements)
{
Stack S = (Stack)malloc(sizeof(struct StackRecord));
S->Array = (PtrNode*)malloc(sizeof(PtrNode)*MaxElements);
S->Capacity = MaxElements;
S->TopOfStack = -1;
return S;
}

PtrNode MakeEmpty()
{
PtrNode p = (PtrNode)malloc(sizeof(struct TNode));
p->Left = NULL;
p->Right = NULL;
return p;
}

void Push(Stack S,PtrNode p)
{
if (S->TopOfStack == S->Capacity - 1)
exit(1);
S->Array[++S->TopOfStack] = p;
}

PtrNode Pop(Stack S)
{
if (S->TopOfStack < 0)
exit(1);
return S->Array[S->TopOfStack--];
}

Tree createTree(int N)
{
Stack S = createStack(N);
Tree root = MakeEmpty();
PtrNode tempRoot = NULL;
PtrNode last = root;
char str[5];
int data;
scanf("%s%d", str, &data);
root->Element = data;
Push(S, root);
while (N)
{
scanf("%s", str);
if (!strcmp(str, "Push"))
{
scanf("%d", &data);
PtrNode temp = MakeEmpty();
temp->Element = data;
Push(S, temp);
if (tempRoot)
{
tempRoot->Right = temp;
tempRoot = NULL;
}
else
{
last->Left = temp;
}
last = temp;
}
else
{
tempRoot = Pop(S);
N--;
}
}
return root;
}

void PrintTree(Tree root)
{
static int tag = 0;
if (root)
{
PrintTree(root->Left);
PrintTree(root->Right);
if (tag)
printf(" ");
printf("%d", root->Element);
tag = 1;
}
}

int main()
{
int N;
scanf("%d", &N);
Tree root = createTree(N);
PrintTree(root);
printf("\n");
return 0;
}
*/