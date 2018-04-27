//#include <stdio.h>
//int maze[5][5], d[4][2] = { 1,0,-1,0,0,1,0,-1 }, que[25],zou[25][2];
//void bfs(int x, int y)
//{
//	int n = x * 5 + y, last = 0, next = 0;
//	int vis[5][5] = { 1 }, dis[5][5] = { 0 };
//	que[next++] = n;
//	while (last < next)
//	{
//		x = que[last] / 5;
//		y = que[last++] % 5;
//		int i;
//		for ( i = 0; i < 4; i++)
//		{
//			int nx = x + d[i][0];
//			int ny = y + d[i][1];
//			if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5 && !vis[nx][ny] && !maze[nx][ny])
//			{
//				que[next++] = nx * 5 + ny;
//				dis[nx][ny] = dis[x][y] + 1;
//				vis[nx][ny] = 1;
//			}
//		}
//	}
//	x = y = 4;
//	int c = 0, i;
//	zou[c][0] = zou[c++][1] = 4;
//	while (dis[x][y] != 1) {
//		for ( i = 0; i < 4; i++)
//		{
//			int nx = x + d[i][0];
//			int ny = y + d[i][1];
//			if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5 && dis[nx][ny] && dis[nx][ny] < dis[x][y])
//			{
//				zou[c][0] = nx;
//				zou[c++][1] = ny;
//				x = nx, y = ny;
//				break;
//			}
//		}
//	}
//	zou[c][0] = 0, zou[c][1] = 0;
//	for ( i = c; i >= 0; i--)
//	{
//		printf("(%d, %d)\n", zou[i][0], zou[i][1]);
//	}
//}
//int main()
//{
//	int i, j;
//	while (1)
//	{
//		for (i = 0; i < 5; i++)
//			for (j = 0; j < 5; j++)
//				scanf_s("%d", &maze[i][j]);
//		bfs(0, 0);
//	}
//	return 0;
//}
#include <stdio.h>
struct node
{
	int pre;
	int x;
	int y;
}path[100];
int maze[5][5], dis[5][5];
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
void print(int n) {
	if (path[n].pre != -1)
	{
		print(path[n].pre);
		printf("(%d, %d)\n", path[n].x, path[n].y);
	}
	else
	{
		printf("(%d, %d)\n", path[n].x, path[n].y);
	}
}
void bfs() {
	int first = 0, next = 0;
	int i, x = 0, y = 0;
	path[next].x = x;
	path[next].y = y;
	path[next++].pre = -1;
	while (first < next)
	{
		for (i = 0; i < 4; i++)
		{
			int nx = path[first].x + dx[i], ny = path[first].y + dy[i];
			if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5 && !maze[nx][ny])
			{
				dis[nx][ny] = dis[x][y] + 1;
				maze[nx][ny] = 1;
				path[next].x = nx;
				path[next].y = ny;
				path[next++].pre = first;
			}
			if (nx == 4 && ny == 4)
			{
				print(next - 1);
				return;
			}
		}
		first++;
	}
}
int main()
{
	int i, j;
	for ( i = 0; i < 5; i++)
	{
		for ( j = 0; j < 5; j++)
		{
			scanf_s("%d", &maze[i][j]);
		}
	}
	bfs();
	return 0;
}