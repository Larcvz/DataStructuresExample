#include <stdio.h>
#include <string.h>
int main()
{
	char list[1000];
	int n;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", list);
		int a[100] = { 0 }, loc = 0, max = 0, i, sum = 0;
		char *c = list;
		while (*c)
		{
			if (*c != '('&&*c != ')'&&*c != ',') {
				a[loc]++;
			}
			else if (*c=='('){
				loc++;
				max++;
			}
			else if (*c == ')') {
				loc--;
			}
			c++;
		}
		for ( i = 0; i <= max; i++)
		{
			sum += a[i] * i;
		}
		printf("%d\n", sum);
	}
	return 0;
}