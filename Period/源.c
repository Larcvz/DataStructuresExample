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
		if (k == -1 || str[j] == str[k])
		{
			++k;
			++j;
			next[j] = k;
		}
		else
			k = next[k];
	}
}

void show()
{
	int n, i;
	static int c = 1;
	
	printf("Test case #%d\n", c++);
	for  (i = 2; str[i-1]; i++)
	{
		n=i-next[i];
		if (i%n == 0 && i / n > 1)
		{
			printf("%d %d\n", i, i/n);
		}
	}
}

int main()
{
	int n;
	while (scanf("%d",&n),n)
	{
		scanf("%s", str);
		getNext(str, next);
		show();
		printf("\n");
	}
	return 0;
}