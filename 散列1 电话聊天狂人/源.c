#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MaxTableSize 1000000
#define MinTableSize 1
#define KEYLENGTH (11)

typedef int Index;
typedef char ElementType[KEYLENGTH + 1];
typedef struct ListNode *Position;
struct ListNode
{
	ElementType element;
	int count;
	Position next;
};
typedef Position List;

typedef struct HashTable *HashTable;
struct HashTable
{
	int tableSize;
	List *theLists;
};

Index Hash(ElementType key,int tableSize)
{
	int hashVal = 0;

	if (key != '\0')
		hashVal = atoi(key + 6);

	return hashVal % tableSize;
}

int NextPrime(int tableSize)
{
	int i;
	if (!(tableSize & 1))tableSize++;
	while (tableSize<MaxTableSize)
	{
		for ( i = (int)sqrt(tableSize); i >= 2; i--)
		{
			if (tableSize%i == 0)break;
		}
		if (i < 2)break;
		tableSize += 2;
	}

	return tableSize;
}

HashTable InitializeTable(int tableSize)
{
	HashTable H;
	int i;

	if (tableSize < MinTableSize)
		return NULL;

	H = (HashTable)malloc(sizeof(struct HashTable));
	H->tableSize = NextPrime(tableSize);
	H->theLists = (List*)malloc(sizeof(List)*H->tableSize);

	for ( i = 0; i < H->tableSize; i++)
	{
		H->theLists[i] = (List)malloc(sizeof(struct ListNode));
		H->theLists[i]->next = NULL;
	}

	return H;
}

Position Find(ElementType key, HashTable H, Index index)
{
	Position p;
	List L;
	
	L = H->theLists[index];
	p = L->next;
	while (p != NULL && strcmp(p->element, key) != 0)
	{
		p = p->next;
	}

	return p;
}

void Insert(ElementType key, HashTable H)
{
	Position pos, newCell;
	List L;
	Index index;

	index = Hash(key, H->tableSize);
	pos = Find(key, H, index);
	if (pos == NULL)
	{
		newCell = (Position)malloc(sizeof(struct ListNode));
		newCell->count = 1;
		strcpy(newCell->element, key);

		L = H->theLists[index];
		newCell->next = L->next;
		L->next = newCell;
	}
	else
		pos->count++;
}

void ScanTable(HashTable H)
{
	int maxCount, phoneNum, i;
	ElementType minPhone;

	phoneNum = 1;
	maxCount = 0;

	for ( i = 0; i < H->tableSize; i++)
	{
		Position p = H->theLists[i]->next;
		while (p != NULL)
		{
			if (p->count > maxCount)
			{
				maxCount = p->count;
				strcpy(minPhone, p->element);
				phoneNum = 1;
			}
			else if (p->count == maxCount)
			{
				if(strcmp(minPhone, p->element) > 0)
					strcpy(minPhone, p->element);
				phoneNum++;
			}
			p = p->next;
		}
	}
	printf("%s %d", minPhone, maxCount);
	if (phoneNum > 1)
		printf(" %d", phoneNum);
	printf("\n");
}

void DestroyTable(HashTable H)
{
	int i;

	for ( i = 0; i < H->tableSize; i++)
	{
		free(H->theLists[i]);
	}
	free(H->theLists);
	free(H);
}

int main()
{
	HashTable H;
	ElementType Key;
	int N;

	scanf("%d", &N);
	N <<= 1;
	H = InitializeTable(N);
	while (N--)
	{
		scanf("%s", Key);
		Insert(Key, H);
	}
	ScanTable(H);
	DestroyTable(H);

	return 0;
}