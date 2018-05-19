#include <stdio.h>
#include <stdlib.h>

int main()
{
	int age[51], N, i;

	scanf("%d", &N);
	for (i = 0; i < 51; i++)
		age[i] = 0;
	while (N--)
	{
		scanf("%d", &i);
		age[i]++;
	}		
	for ( i = 0; i < 51; i++)
	{
		if (age[i] != 0)
			printf("%d:%d\n", i, age[i]);
	}

	return 0;
}