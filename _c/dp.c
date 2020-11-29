#include<stdio.h>
#include<stdlib.h>

#define SUM 13

// _Bool rec_subset(int *arr, int i, int s)
// {
//     if(s == 0)
//         return 1;
//     else if(i == 0)
//         return arr[0] == s;
//     else if(arr[i] > s)
//         return rec_subset(arr, i - 1, s);
//     else
//         return rec_subset(arr, i - 1, s - arr[i]) | rec_subset(arr, i - 1, s);
// }

void dp_subset(int *arr, int dp[][SUM+1], int len)
{
    int i, j;
    for (i = 0; i < len; i++)
        dp[i][0] = 1;
    for (j = 0; j <= SUM; j++)
        dp[0][j] = 0;
    dp[0][arr[0]] = 1;
    for (i = 1; i < len; i++)
    {
        for (j = 1; j <= SUM; j++)
        {
            if(arr[i] > j)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j] | dp[i - 1][j - arr[i]];
        }
    }
}

int main()
{
    int arr[] = {3, 34, 4, 12, 5, 2};
    int len = sizeof(arr) / sizeof(arr[0]);
    int (*dp)[SUM+1] = (int (*)[SUM+1])malloc(sizeof(int[SUM+1]) * len);
    // _Bool ans;

    // ans = rec_subset(arr, len - 1, 1);
    // printf("%d", ans);

    dp_subset(arr, dp, len);
    printf("%d", dp[len - 1][SUM]);
    free(dp);

    return 0;
}