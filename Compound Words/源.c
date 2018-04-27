//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdbool.h>
//typedef struct Trie{
//	bool flag;
//	struct Trie *next[26];
//}trie;
//trie root;
//trie* creat() {
//	trie *p = (trie*)malloc(sizeof(trie));
//	p->flag = false;
//	int i;
//	for ( i = 0; i < 26; i++)
//	{
//		p->next[i] = NULL;
//	}
//	return p;
//}
//void insert(char *s) {
//	trie *p = &root;
//	while (*s)
//	{
//		int t = *s - 'a';
//		if (p->next[t])
//			p->next[t] = creat();
//		p = p->next[t];
//	}
//	p->flag = true;
//}
//void del(trie *p) {
//	int i;
//	if(p)
//		for (i = 0; i < 26; i++) {
//			if (p->next[i])
//				del(p->next[i]);
//		}
//	free(p);
//}
//int main()
//{
//
//	return 0;
//}
#include <stdio.h>
#include <string.h>	
#include <stdbool.h>
#define MAX 100
char dic[120000][100];
bool find(char *s,int n) {
	int last = 0, right = n - 1, la;
	while (last <= right)
	{
		la = (right + last) / 2;
		if (strcmp(s, dic[la]) > 0) {
			last = la+1;
		}
		else if (strcmp(s, dic[la]) < 0) {
			right = la-1;
		}
		else {
			return true;
		}		
	}
	return false;
}
int main()
{
	int n = 0, i, j, k;
	while (scanf("%s", dic[n++]) != EOF);
	for ( i = 0; i < n; i++)
	{
		char s1[100] = { 0 };
		int	l = strlen(dic[i]);
		for ( j = 0; j < l; j++)
		{
			s1[j] = dic[i][j];
			char s2[100] = { 0 };
			for ( k = j+1; k < l; k++)
			{
				s2[k - j - 1] = dic[i][k];
			}
			if (find(s1, n) && find(s2, n))
			{
				printf("%s\n", dic[i]);
				break;
			}
		}
	}
	return 0;
}