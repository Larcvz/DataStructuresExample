#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node {
	union 
	{
		char name[5];
		int stu_total;
	};
	Position Next;
};

List Creat(int K) {
	List *Class = (List*)malloc(sizeof(List)*K);
	int i;
	for (i = 0; i < K; i++)
	{

	}
	return Class;
}

void Insert()
{

}

void CreatClassList(List Class, int N) {
	int C, name[5];
}

int main()
{
	int N, K;
	scanf("%d%d", &N, &K);
	List Class = Creat(K);

	return 0;
}