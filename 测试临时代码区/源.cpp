#include <stdio.h>
#include <stdlib.h>

int main()
{
	int stack[32];
	int top, n, r;

	while (scanf("%d%d", &n, &r) != EOF)
	{
		top = -1;
		if (n == 0)
		{
			printf("0\n");
			continue;
		}
		if (n < 0)
		{
			printf("-");
			n = -n;
		}
		while (n)
		{
			stack[++top] = n % r;
			n /= r;
		}
		while (top != -1)
		{
			printf("%X", stack[top--]);
		}
		printf("\n");
	}
	return 0;
}