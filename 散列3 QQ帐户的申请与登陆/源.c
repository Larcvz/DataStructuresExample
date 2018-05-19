#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MaxTableSize 1000000
#define MinTableSize 1
#define KEYLENTH 10
#define PASSWORDLENTH 16

//error函数 密码错误为1，账号不存在为2，账号已存在为3
void Error(int status)
{
	switch (status)
	{
	case 1:printf("ERROR: Wrong PW\n"); break;
	case 2:printf("ERROR: Not Exist\n"); break;
	case 3:printf("ERROR: Exist\n"); break;
	}
}
//message函数 注册成功为1，登录成功为0
void Message(int status)
{
	switch (status)
	{
	case 0:printf("Login: OK\n"); break;
	case 1:printf("New: OK\n"); break;
	}
}

typedef int Index;
typedef char ElementType[KEYLENTH + 1];

typedef struct ListNode *Position;
typedef Position List;
struct ListNode
{
	ElementType QQnumber;
	char passWord[PASSWORDLENTH + 1];
	Position next;
};

typedef struct HashTable *HashTable;
struct HashTable
{
	int tableSize;
	List *theLists;
};

int NextPrime(int tableSize)
{
	int i;

	if (tableSize <= 2)
		return 2;
	if (!(tableSize & 1))
		tableSize++;
	while (tableSize < MaxTableSize)
	{
		for (i = sqrt(tableSize); i >= 2; i--)
		{
			if (tableSize%i == 0)
				break;
		}
		if (i < 2)break;
		tableSize += 2;
	}

	return tableSize;
}
//获取QQ号码的长度然后取最后的末尾5位
Index Hash(const ElementType key, int tableSize)
{
	int lenth = strlen(key);
	int keyNum = atoi(key + lenth - 5);

	return keyNum % tableSize;
}

HashTable InitializeTable(int tableSize)
{
	HashTable H;
	int i;

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

Position Find(ElementType key, HashTable H)
{
	Position p;
	List L;

	L = H->theLists[Hash(key, H->tableSize)];
	p = L->next;
	while (p != NULL && strcmp(p->QQnumber, key))
	{
		p = p->next;
	}

	return p;
}

void Insert(ElementType key, HashTable H)
{
	Position p, newCell;
	char temp[PASSWORDLENTH + 1];
	List L;

	p = Find(key, H);
	if (p == NULL)
	{
		newCell = (Position)malloc(sizeof(struct ListNode));
		scanf("%s", newCell->passWord);
		strcpy(newCell->QQnumber, key);

		L = H->theLists[Hash(key, H->tableSize)];
		newCell->next = L->next;
		L->next = newCell;
		Message(1);
	}
	else
	{
		scanf("%s", temp);
		Error(3);
	}
}

void Login(ElementType key, HashTable H)
{
	Position p;
	char passWord[PASSWORDLENTH + 1];

	scanf("%s", passWord);
	p = Find(key, H);
	if (p == NULL)
	{
		Error(2);
	}
	else if (strcmp(p->passWord, passWord) == 0)
	{
		Message(0);
	}
	else
	{
		Error(1);
	}
}

void Registered(ElementType key,HashTable H)
{
	Insert(key, H);
}

int main()
{
	HashTable H;
	ElementType QQnumber;
	char cmd;
	int N;

	scanf("%d", &N);
	H = InitializeTable(N);
	while (N--)
	{
		scanf(" %c%s", &cmd, QQnumber);
		switch (cmd)
		{
		case 'N':Registered(QQnumber, H); break;
		case 'L':Login(QQnumber, H); break;
		default:
			printf("ERROR:input %c\n", cmd); break;
		}
	}
	//最后忘记写了一个销毁HashTable的函数
	return 0;
}