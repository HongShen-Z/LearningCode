#include<stdio.h>

int dp_max_sum(int *arr, int n)
{
    int cur_sum = 0, max_sum = 0, i;

    for (i = 0; i < n; i++)
    {
        if(cur_sum + arr[i] > 0)
            cur_sum += arr[i];
        else
            cur_sum = 0;
        if(cur_sum > max_sum)
            max_sum = cur_sum;
    }
    return max_sum;
}

int main()
{
    int arr[] = {-2, 11 - 4, 13, -5, -2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d", dp_max_sum(arr, n));

    return 0;
}