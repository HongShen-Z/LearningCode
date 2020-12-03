#include<stdio.h>

int dp_max_sum(int *arr, int n, int *result)
{
    int cur_sum = 0, max_sum = 0, i;

    for (i = 0; i < n; i++)
    {
        if(cur_sum + arr[i] > 0)
            cur_sum += arr[i];
        else
        {
            cur_sum = 0;
            if(i <= result[1])
                result[0] = i + 1;
        }
        if(cur_sum > max_sum)
        {
            max_sum = cur_sum;
            result[1] = i;
        }
    }
    return max_sum;
}

int main()
{
    int arr[] = {-2, 11, -4, 13, -5, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result[2] = {0};

    printf("%d\n", dp_max_sum(arr, n, result));
    for (int i = result[0]; i <= result[1]; i++)
        printf("%d ", arr[i]);

    return 0;
}