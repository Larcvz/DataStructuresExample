#include <stdio.h>
#include <stdlib.h>
int m[30], f[30], n;
struct TreeNode;
typedef struct TreeNode Treenode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
struct TreeNode
{
	int Element;
	SearchTree Left;
	SearchTree right;
};
SearchTree Creatleft(int m_left, int m_right, int f_left, int f_right);
SearchTree Creatright(int m_left, int m_right, int f_left, int f_right);
SearchTree Creatleft(int m_left, int m_right, int f_left, int f_right)
{
	if (f_left >= f_right)
		return NULL;
	else
	{
		SearchTree tree = (SearchTree)malloc(sizeof(Treenode));
		tree->Element = f[f_left];
		int i;
		for (i = m_left; i < m_right; i++) {
			if (m[i] == tree->Element)break;
		}
		tree->Left = Creatleft(m_left, i, f_left + 1, f_left + i + 1 - m_left);
		tree->right = Creatright(i + 1, m_right, f_left + i + 1 - m_left, f_right);
		return tree;
	}
}
SearchTree Creatright(int m_left, int m_right, int f_left, int f_right)
{
	if (f_left >= f_right)
		return NULL;
	else
	{
		SearchTree tree = (SearchTree)malloc(sizeof(Treenode));
		tree->Element = f[f_left];
		int i;
		for (i = m_left; i < m_right; i++) {
			if (m[i] == tree->Element)break;
		}
		tree->Left = Creatleft(m_left, i, f_left + 1, f_left + i + 1 - m_left);
		tree->right = Creatright(i + 1, m_right, f_left + i + 1 - m_left, f_right);
		return tree;
	}
}
SearchTree Creat(int n)
{
	SearchTree tree = (SearchTree)malloc(sizeof(Treenode));
	tree->Element = f[0];
	int i;
	for (i = 0; i < n; i++) {
		if (m[i] == f[0])break;
	}
	tree->Left = Creatleft(0, i, 0+1, 0+i+1);
	tree->right = Creatright(i+1, n, 0 + i + 1, n);
	return tree;
}
void Reverse(SearchTree T)
{
	if (T)
	{
		SearchTree p = T->Left;
		T->Left = T->right;
		T->right = p;
		Reverse(T->Left);
		Reverse(T->right);
	}
}
void Print(SearchTree T)
{
	Position p[300];
	int in = 0, out = 0, flag = 0;
	p[in++] = T;
	while (in > out)
	{
		if (p[out])
		{
			if (flag)printf(" ");
			printf("%d", p[out]->Element);
			flag = 1;
			p[in++] = p[out]->Left;
			p[in++] = p[out]->right;
		}
		out++;
	}
}
int main()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d", &m[i]);
	for (i = 0; i < n; i++) scanf("%d", &f[i]);
	SearchTree tree = Creat(n);
	Reverse(tree);
	Print(tree);
	printf("\n");
	return 0;
}