//不一定是连续的
#include<stdio.h>
#include<stdlib.h>

#define max(a,b) a>b?a:b

void dp_LIS(int *arr, int *dp, int n)
{
    int i, j, cur_max;
    dp[0] = 1;
    for (i = 1; i < n; i++)
    {
        cur_max = 1;
        for (j = 0; j < i; j++)
        {
            if(arr[i] > arr[j])
                cur_max = max(cur_max, dp[j] + 1);
        }
        dp[i] = cur_max;
    }
}

int main()
{
    int arr[] = {4 ,2, 3, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *dp = (int *)malloc(sizeof(int) * n);

    dp_LIS(arr, dp, n);
    printf("%d", dp[n - 1]);

    free(dp);
    return 0;
}