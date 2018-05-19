#include <stdio.h>
#include <stdlib.h>

#define MaxNumUsers 10001

typedef struct userStruct
{
	int partial_score[5];
	int user_id;
	int num_full_score;
	int total_score;
}*User;
User Users[MaxNumUsers];

typedef User ElementType;

void Swap(ElementType *A, ElementType *B)
{
	ElementType t = *A;
	*A = *B;
	*B = t;
}

void InsertionSort(ElementType A[], int N)
{
	int j, P;
	ElementType tmp;

	for (P = 1; P < N; P++)
	{
		tmp = A[P];
		for (j = P; j > 0; j--)
		{
			if (A[j - 1]->total_score > tmp->total_score)
				break;
			else if (A[j - 1]->total_score < tmp->total_score)
				A[j] = A[j - 1];
			else if (A[j - 1]->total_score == tmp->total_score
				&&A[j - 1]->num_full_score < tmp->num_full_score)
				A[j] = A[j - 1];
			else if (A[j - 1]->num_full_score == tmp->num_full_score
				&&A[j - 1]->user_id > tmp->user_id)
				A[j] = A[j - 1];
			else
				break;
		}
		A[j] = tmp;
	}
}

int main()
{
	int NumProblems, NumUsers, NumSubmissions;
	int full_score[5], i, j, user_id, problem_id, partial_score_obtained;

	scanf("%d%d%d", &NumUsers, &NumProblems, &NumSubmissions);
	for (i = 0; i < NumProblems; i++)
		scanf("%d", &full_score[i]);
	//初始化
	for ( i = 0; i < NumUsers; i++)
	{
		Users[i] = (User)malloc(sizeof(struct userStruct));
		Users[i]->user_id = i+1;
		Users[i]->total_score = 0;
		Users[i]->num_full_score = 0;
		for (j = 0; j < NumProblems; j++)
			Users[i]->partial_score[j] = -1;
	}
	//输入数据
	for ( i = 0; i < NumSubmissions; i++)
	{
		scanf("%d%d%d", &user_id, &problem_id, &partial_score_obtained);
		user_id--;
		problem_id--;
		if (partial_score_obtained == -1)
			partial_score_obtained = 0;
		if (Users[user_id]->partial_score[problem_id] < partial_score_obtained)
		{
			if(Users[user_id]->partial_score[problem_id]!=-1)
				Users[user_id]->total_score -= Users[user_id]->partial_score[problem_id];
			Users[user_id]->total_score += partial_score_obtained;
			Users[user_id]->partial_score[problem_id] = partial_score_obtained;
			if (partial_score_obtained == full_score[problem_id])
				Users[user_id]->num_full_score++;
		}
	}
	InsertionSort(Users, NumUsers);
	int rank = 1;
	for ( i = 0; i < NumUsers; i++)
	{
		for (j = 0; j < NumProblems; j++)
			if (Users[i]->partial_score[j] != -1)
				break;
		if (j == NumProblems)
			break;
		if (i == 0 || Users[i - 1]->total_score != Users[i]->total_score)
			rank = i + 1;
		printf("%d %05d %d", rank, Users[i]->user_id, Users[i]->total_score);
		for ( j = 0; j < NumProblems; j++)
		{
			printf(" ");
			if (Users[i]->partial_score[j] != -1)
				printf("%d", Users[i]->partial_score[j]);
			else
				printf("-");
		}
		printf("\n");
	}
	
	return 0;
}