#include <stdio.h>
int main()
{
	int num[100000], k, sum, i, max;
	while (scanf("%d", &k) != EOF)
	{
		max = sum = 0;
		for (i = 0; i < k; i++) {
			scanf("%d", &num[i]);
			sum += num[i];
			if (sum < 0)sum = 0;
			else if (sum > max)max = sum;
		}
		printf("%d\n", max);
	}
	return 0;
}