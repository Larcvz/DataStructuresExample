#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int queue[1000];
	int front, rear;
}Queue;

void CreatQueue(Queue *QA,Queue *QB,int N) {
	while (N--)
	{
		int num;
		scanf("%d", &num);
		if (num & 1) 
			QA->queue[QA->rear++] = num;
		else
			QB->queue[QB->rear++] = num;
	}
}
void Print(Queue *QA, Queue *QB) {
	int tag = 0;
	while (QA->front < QA->rear&&QB->front < QB->rear) {
		if (tag)printf(" ");
		tag = 1;
		printf("%d", QA->queue[QA->front++]);
		if (QA->front == (QB->front + 1) << 1)
			printf(" %d", QB->queue[QB->front++]);
	}
	if (QA->front < QA->rear) {
		while (QA->front < QA->rear)
		{
			if (tag)printf(" ");
			tag = 1;
			printf("%d", QA->queue[QA->front++]);
		}
	}
	else
	{
		while (QB->front < QB->rear)
		{
			if (tag)printf(" ");
			tag = 1;
			printf("%d", QB->queue[QB->front++]);
		}
	}
}
int main()
{
	Queue q1, q2;
	q1.front = q1.rear = q2.front = q2.rear = 0;
	int N;
	scanf("%d", &N);
	CreatQueue(&q1, &q2, N);
	Print(&q1, &q2);
	return 0;
}