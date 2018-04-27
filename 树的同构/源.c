#include <stdio.h>
#include <stdlib.h>
typedef struct TNode *Tree;
typedef Tree Child;
struct TNode {
	char Word;
	Child Left;
	Child Right;
};
Tree CreatBinaryTree(int N) {
	Child *child = (Child*)malloc(sizeof(Child)*N);
	Tree Root = NULL;
	int tag[10] = { 0 };
	int i;
	for ( i = 0; i < N; i++){
		child[i] = (Child)malloc(sizeof(struct TNode));
	}
	for ( i = 0; i < N; i++)
	{
		char left, right;
		scanf(" %c %c %c", &child[i]->Word, &left, &right);
		if (left == '-') {
			child[i]->Left = NULL;
		}
		else {
			child[i]->Left = child[left - '0'];
			tag[left - '0'] = 1;
		}
		if (right == '-') {
			child[i]->Right = NULL;
		}
		else {
			child[i]->Right = child[right - '0'];
			tag[right - '0'] = 1;
		}
	}
	for ( i = 0; i < N; i++){
		if (!tag[i])Root = child[i];
	}
	return Root;
}
void Rev(Tree root) {
	Child t=root->Left;
	root->Left = root->Right;
	root->Right = t;
}
int CompTree(Tree root1, Tree root2) {
	if (!root1 && !root2) {
		return 1;
	}
	else if (!root1 || !root2) {
		return 0;
	}
	if (root1->Word == root2->Word) {
		if (CompTree(root1->Left, root2->Left) && CompTree(root1->Right, root2->Right)) {
			return 1;
		}
		else {
			Rev(root1);
			if (CompTree(root1->Left, root2->Left) && CompTree(root1->Right, root2->Right)) {
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	int N;
	Tree Root1, Root2;
	scanf("%d", &N);
	Root1 = CreatBinaryTree(N);
	scanf("%d", &N);
	Root2 = CreatBinaryTree(N);
	if (CompTree(Root1,Root2)) {
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}
	return 0;
}