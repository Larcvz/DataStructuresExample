#include <stdio.h>
#define INF 0xffffff
int dis[110][110], dv[110], known[110];
void chushi() {
	int i, j;
	for (i = 0; i < 110; i++) {
		known[i] = 0;
		dv[i] = INF;
		for (j = 0; j < 110; j++)
			dis[i][j] = INF;
		dis[i][i] = 0;
	}	
}
int Dijkstra(int n)
{
	int i, j, cur = 1;
	dv[1] = 0;
	known[1] = 1;
	for ( i = 0; i < n; i++)
	{
		for ( j = 1; j <= n; j++)
		{
			if (!known[j] && dis[cur][j] + dv[cur] < dv[j])
			{
				dv[j] = dis[cur][j] + dv[cur];
			}
		}
		int min = INF;
		for ( j = 1; j <= n; j++)
		{
			if (!known[j] && min > dv[j])
			{
				min = dv[cur = j];
			}
		}
		known[cur] = 1;
	}
	return dv[n];
}
int main()
{
	int a, b, c, n, m;
	while (scanf("%d%d", &n, &m), n || m)
	{
		int i, j;
		chushi();
		for ( i = 0; i < m; i++)
		{
			scanf("%d%d%d", &a, &b, &c);
			dis[a][b] = c;
			dis[b][a] = c;
		}
		printf("%d\n", Dijkstra(n));
	}
	return 0;
}