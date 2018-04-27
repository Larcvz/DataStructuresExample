#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100
char dic[50010][MAX];
typedef struct node{
	bool flag;
	struct node *next[26];
}node;
node root;
node* creat() {
	node *p = (node*)malloc(sizeof(node));
	p->flag = 0;
	int i;
	for (i = 0; i < 26; i++)
		p->next[i] = NULL;
	return p;
}
void insert(char *s) {
	node *p = &root;
	while (*s){
		int t = *s++ - 'a';
		if (!(p->next[t]))
			p->next[t] = creat();
		p = p->next[t];
	}
	p->flag = 1;
}
bool find(char *s) {
	node *p = &root;
	while (*s){
		if (!(p=p->next[*s++-'a'])){
			return false;
		}
	}
	if (p->flag)
		return true;
	return false;
}
void del(node *root)
{
	int i;
	if(root)
		for (i = 0; i<26; i++){
			if (root->next[i] != NULL)
				del(root->next[i]);
		}
	free(root);
}
int main()
{
	char s1[MAX], s2[MAX];
	int n = 0, i;
	while (scanf("%s",dic[n]) != EOF)
		insert(dic[n++]);
	for ( i = 0; i < n; i++){
		int l = strlen(dic[i]);
		int i1, j;
		for (i1 = 0; i1 < MAX; i1++)s1[i1] = 0;
		for (i1 = 0; i1 < l; i1++) {
			s1[i1] = dic[i][i1];
			for (j = 0; j < MAX; j++)s2[j] = 0;
			for (j = i1 + 1; j < l; j++)
				s2[j - i1 - 1] = dic[i][j];
			if (find(s1) && find(s2)){
				printf("%s\n", dic[i]);
				break;
			}
		}
	}
	for ( i = 0; i < 26; i++)
		del(root.next[i]);
	return 0;
}