#include <stdio.h>

int main()
{
	int k, num[10000], i, lable = 0;
	scanf("%d", &k);
	for (i = 0; i < k; i++) {
		scanf("%d", &num[i]);
		if (num[i] > 0)lable = 1;
	}
	int maxsum = 0, sum = 0, max_left = 0, max_right = k - 1, left = 0, right = 0;
	for ( i = 0; i < k; i++)
	{
		sum += num[i];
		if (!lable && !num[i]) { 
			max_left = max_right = i;
			break;
		}
		right = i;
		if (sum > maxsum) {
			max_left = left;
			max_right = right;
			maxsum = sum;
		}
		else if (sum < 0) {
			sum = 0;
			left = right = i + 1;
		}
	}
	printf("%d %d %d\n", maxsum, num[max_left], num[max_right]);
	return 0;
}