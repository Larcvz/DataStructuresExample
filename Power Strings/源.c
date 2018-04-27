#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[1000001];
int next[1000001];

void getNext(char *str, int next[])
{
	int k = -1, j = 0;
	next[0] = -1;
	while (str[j]!='\0')
	{
		if (k == -1 || str[k] == str[j])
		{
			++k;
			++j;
			next[j] = k;
		}
		else
			k = next[k];
	}
}

void show(char *str, int next[])
{
	int lenth = strlen(str);
	int n = lenth - next[lenth];
	printf("%d\n", lenth / n);
}

int main()
{
	while (scanf("%s",str),*str!='.')
	{
		getNext(str, next);
		show(str, next);
	}
	return 0;
}