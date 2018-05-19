#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxTableSize 100000

typedef int Index;
typedef Index Position;
typedef int ElementType;

enum KindOfEntry { Legitimate, Empty, Deleted };

struct HashEntry
{
	ElementType element;
	enum KindOfEntry info;
};

typedef struct HashEntry Cell;
typedef struct HashTable
{
	int tableSize;
	Cell *theCells;
}*HashTable;

int NextPrime(int tableSize)
{
	int i;
	if (!(tableSize & 1))tableSize++;
	while (tableSize < MaxTableSize)
	{
		for (i = (int)sqrt(tableSize); i >= 2; i--)
		{
			if (tableSize%i == 0)break;
		}
		if (i < 2)break;
		tableSize += 2;
	}

	return tableSize;
}

Position Hash(ElementType key, HashTable H)
{
	return key % H->tableSize;
}

HashTable InitializeTable(int tableSize)
{
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(struct HashTable));
	if (tableSize > 2)
		H->tableSize = NextPrime(tableSize);
	else
		H->tableSize = 2;
	H->theCells = (Cell*)malloc(sizeof(Cell)*H->tableSize);

	for ( i = 0; i < H->tableSize; i++)
	{
		H->theCells[i].info = Empty;
	}

	return H;
}

Position Find(ElementType key, HashTable H)
{
	Position currentPos, pos;
	int collisionNum;

	collisionNum = 0;
	pos = currentPos = Hash(key, H);
	while (H->theCells[currentPos].info!=Empty&&
		   H->theCells[currentPos].element!=key)
	{
		currentPos += 2 * (++collisionNum) - 1;
		if (currentPos >= H->tableSize)
			currentPos %= H->tableSize;
		if (pos == currentPos)
		{
			currentPos = -1;
			break;
		}
	}

	return currentPos;
}

void Insert(ElementType key, HashTable H)
{
	Position pos;

	pos = Find(key, H);
	if (pos == -1)
		printf("-");
	else
	{
		H->theCells[pos].info = Legitimate;
		H->theCells[pos].element = key;
		printf("%d", pos);
	}
}

void DestoryTable(HashTable H)
{
	free(H->theCells);
	free(H);
}

int main()
{
	int tableSize, N, i, tag;
	ElementType *elements;
	HashTable H;
	
	scanf("%d%d", &tableSize, &N);
	elements = (ElementType*)malloc(sizeof(ElementType)*N);
	H = InitializeTable(tableSize);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &elements[i]);
	}
	tag = 0;
	for ( i = 0; i < N; i++)
	{
		if (tag == 1)
			printf(" ");
		Insert(elements[i], H);
		tag = 1;
	}
	printf("\n");
	DestoryTable(H);

	return 0;
}