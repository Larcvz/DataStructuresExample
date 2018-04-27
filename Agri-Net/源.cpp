#include <stdio.h>
#include <math.h>
int nongm[100], dis[100][100];
int prime(int n)
{
	int sum = 0, min, t = n;
	int i, x;
	for ( i = 0; i < n; i++)
		nongm[i] = dis[0][i];
	while (--t)
	{
		int min = 1000001;
		for ( i = 0; i < n; i++)
		{
			if (nongm[i] && min > nongm[i])
			{
				min = nongm[i];
				x = i;
			}
		}
		sum += min;
		nongm[x] = 0;
		for ( i = 0; i < n; i++)
		{
			if (nongm[i] > dis[x][i])
				nongm[i] = dis[x][i];
		}
	}
	return sum;
}
int main()
{
	int n, i, j;
	while (scanf("%d", &n) != EOF)
	{
		for ( i = 0; i < n; i++)
			for ( j = 0; j < n; j++)
				scanf("%d", &dis[i][j]);
		printf("%d\n", prime(n));
	}
	return 0;
}
