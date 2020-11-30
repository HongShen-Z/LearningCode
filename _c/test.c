#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
// #include<Windows.h>

#define Len 10000000

void merge(int arr[], int *temp, int start, int mid, int end)
{
    int i = start, j = mid + 1, k = start;
    while(i <= mid && j <= end)
    {
        if(arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }
    while (j <= end)
    {
        temp[k++] = arr[j++];
    }

    memcpy(arr + start, temp + start, sizeof(int) * (end - start + 1));
}

void merge_sort(int arr[], int *temp, int start, int end)
{
    int mid;
    if(start < end)
    {
        mid = (end + start) / 2;
        merge_sort(arr, temp, start, mid);
        merge_sort(arr, temp, mid + 1, end);
        merge(arr, temp, start, mid, end);
    }
}


// int random_partion(int *arr, int low, int high)
// {
//     int r, mid = low - 1, piv, temp;
//     srand((unsigned int)time(NULL));
//     r = rand() % (high - low) + low;
//     piv = arr[r];
//     arr[r] = arr[high];
//     arr[high] = piv;
//     for (int i = low; i < high; i++)
//     {
//         if(arr[i] < piv)
//         {
//             mid++;
//             temp = arr[i];
//             arr[i] = arr[mid];
//             arr[mid] = temp;
//         }
//     }
//     arr[high] = arr[++mid];
//     arr[mid] = piv;

//     return mid;
// }

// void quick_sort(int *arr, int low, int high)
// {
//     int mid;
//     if(low < high)
//     {
//         mid = random_partion(arr, low, high);
//         quick_sort(arr, low, mid - 1);
//         quick_sort(arr, mid + 1, high);
//     }
// }

void quick_sort(int s[], int l, int r)
{
    int i = l, j = r, x = s[l];
    
    if (l < r)
    {
        // srand((unsigned int)time(NULL));
        // ran = rand() % (r - l) + l;
        // x = s[ran];
        // s[ran] = s[l];
        // s[l] = x;
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;  
            if(i < j) 
                s[i++] = s[j];
            
            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                i++;  
            if(i < j) 
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用 
        quick_sort(s, i + 1, r);
    }
}


void max_heapify(int *arr, int i, int heap_size)
{
    int left = (i << 1) + 1, right = (i << 1) + 2, max, temp;
    if(left < heap_size && arr[i] < arr[left])
        max = left;
    else
        max = i;
    if(right < heap_size && arr[right] > arr[max])
        max = right;
    if(max != i)
    {
        temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;
        max_heapify(arr, max, heap_size);
    }
}

int modify_heap(int *arr, int heap_size)
{
    int i = 0;
    while ((i << 1) + 2 < heap_size)
    {
        if (arr[(i << 1) + 1] > arr[(i << 1) + 2])
        {
            arr[i] = arr[(i << 1) + 1];
            i = (i << 1) + 1;
        }
        else
        {
            arr[i] = arr[(i << 1) + 2];
            i = (i << 1) + 2;
        }
    }
    if ((i << 1) + 1 < heap_size)
    {
        arr[i] = arr[(i << 1) + 1];
        i = (i << 1) + 1;
    }

    return i;
}

void check_up(int *arr, int i)
{
    int j = (i - 1) >> 1, temp;
    if(j >= 0 && arr[i] > arr[j])
    {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        check_up(arr, j);
    }
}

void heap_sort_modified(int *arr, int len)
{
    int i, temp, heap_size = len, empty;
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, heap_size);
    for (i = len - 1; i > 0; i--)
    {
        temp = arr[i];
        arr[i] = arr[0];
        empty = modify_heap(arr, --heap_size);
        arr[empty] = temp;
        check_up(arr, empty);
    }
}

void heap_sort(int *arr, int len)
{
    int i, temp, heap_size = len;
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, heap_size);
    for (i = len - 1; i > 0; i--)
    {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        max_heapify(arr, 0, --heap_size);
    }
}

int main()
{
    int i;
    clock_t start, end;
    // double run_time;
	// LARGE_INTEGER time_start;	//开始时间
	// LARGE_INTEGER time_over;	//结束时间
	// double dqFreq;		//计时器频率
	// LARGE_INTEGER f;	//计时器频率
    int *a = (int*)malloc(sizeof(int) * Len);
    int *b = (int*)malloc(sizeof(int) * Len);
    int *c = (int*)malloc(sizeof(int) * Len);
    int *d = (int*)malloc(sizeof(int) * Len);
    int *temp = (int *)malloc(sizeof(int) * Len);

    for (i = 0; i < Len; i++)
        d[i] = c[i] = b[i] = a[i] = rand() % 2000;

    start = clock();
    heap_sort(a, Len);
    end = clock();
    printf("heap_sort  : %ld\n", end - start);

    start = clock();
    heap_sort_modified(b, Len);
    end = clock();
    printf("heap_sort_m: %ld\n", end - start);

    start = clock();
    quick_sort(c, 0, Len - 1);
    end = clock();
    printf("quick_sort : %ld\n", end - start);

    start = clock();
    merge_sort(d, temp, 0, Len - 1);
    end = clock();
    printf("merge_sort : %ld\n", end - start);

	// QueryPerformanceFrequency(&f);
	// dqFreq=(double)f.QuadPart;

	// QueryPerformanceCounter(&time_start);	//计时开始
    // heap_sort(a, Len);
    // QueryPerformanceCounter(&time_over);	//计时结束
    // run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    // printf("heap_sort  : %.1f\n", run_time);

    // QueryPerformanceCounter(&time_start);	//计时开始
    // heap_sort_modified(b, Len);
    // QueryPerformanceCounter(&time_over);	//计时结束
    // run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    // printf("heap_sort_m: %.1f\n", run_time);

    // QueryPerformanceCounter(&time_start);	//计时开始
    // quick_sort(c, 0, Len - 1);
    // QueryPerformanceCounter(&time_over);	//计时结束
    // run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    // printf("quick_sort : %.1f\n", run_time);

    // QueryPerformanceCounter(&time_start);	//计时开始
    // merge_sort(d, temp, 0, Len - 1);
    // QueryPerformanceCounter(&time_over);	//计时结束
    // run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    // printf("merge_sort : %.1f\n", run_time);

    // heap_sort(a, Len);
    // heap_sort_modified(b, Len);
    // quick_sort(c, 0, Len - 1);
    // merge_sort(d, temp, 0, Len - 1);
    // for (i = 0; i < Len; i++)
    //     printf("%d ", d[i]);

    free(d);
    free(c);
    free(b);
    free(a);

    return 0;
}