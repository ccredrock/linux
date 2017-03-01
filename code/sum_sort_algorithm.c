// 排序算法
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#define SIZE 100
#define NAME 20

#define BUBBLE_SORT 1
#define INSERT_SORT 2
#define SELECT_SORT 3
#define MERGE_SORT  4
#define QUICK_SORT  5

int data[SIZE];

int main(void)
{
    struct timeval start, end;
    init(data, SIZE);
    sort_test(data, SIZE, BUBBLE_SORT, "bubble_sort");
    sort_test(data, SIZE, INSERT_SORT, "insert_sort");
    sort_test(data, SIZE, SELECT_SORT, "select_sort");
    sort_test(data, SIZE, MERGE_SORT, "merge_sort");
    sort_test(data, SIZE, QUICK_SORT, "quick_sort");
}

int init(int data[], int sum)
{
    int i = 0;
    srand((int)time(0));
    for(; i < sum; ++i)
        data[i] = rand() % sum;
    printf("init list size:%d\n", SIZE);
    print(data, SIZE);
}

int print(int data[], int sum)
{
    int i = 0;
    for(; i < sum; ++i)
        printf("%d ", data[i]);
    printf("\n");
}

sort_test(int data[], int sum, int type, char name[])
{
    int tmp[sum];
    memcpy(tmp, data, sizeof(int) * sum);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    switch(type)
    {
        case BUBBLE_SORT:
            bubble_sort(tmp, sum);
            break;
        case INSERT_SORT:
            insert_sort(tmp, sum);
            break;
        case SELECT_SORT:
            select_sort(tmp, sum);
            break;
        case MERGE_SORT:
            merge_sort(tmp, sum);
            break;
        case QUICK_SORT:
            quick_sort(tmp, sum);
            break;
    }
    gettimeofday(&end, NULL);
    long int cost = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("%s cost %ld us\n", name, cost);
    print(tmp, SIZE);
}

int bubble_sort(int data[], int sum)
{
    int i = 0, j = 0;
    int did = 0, tmp = 0;
    for(; i < sum; i++)                 // O(n)
    {
        for(j = sum - 2; j >= i; j--)   // O(n^2)
        {
            if(data[j] > data[j + 1])
            {
                did = !0;
                tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
        if(!did) return;
    }
}

int insert_sort(int data[], int sum)
{
    int i = 0, j = 0;
    int tmp = 0;
    for(; i < sum; i++)                 // O(n)
    {
        tmp = data[i];
        for(j = i; j > 0; j--)          // O(n^2)
        {
            if(tmp < data[j - 1])
            {
                data[j] = data[j - 1];
            } else
            {
                data[j] = tmp;
                break;
            }
        }
        if (j == 0) data[0] = tmp;
    }
}

int select_sort(int data[], int sum)
{
    int i = 0, j = 0, s = 0;
    int tmp = 0;
    for(; i < sum; i++)                       // O(n)
    {
        tmp = data[i];
        for(s = i, j = i + 1; j < sum; j++)   // O(n^2)
        {
            if(data[j] < tmp)
            {
                tmp = data[j];
                s = j;
            }
        }
        if (i != s)
        {
            data[s] = data[i];
            data[i] = tmp;
        }
    }
}

// [1,4,2,3] -> [1,4], [2,3]
int merge_sort(int data[], int sum)
{
    int tmp_data[sum];
    int *src_data = data, *dst_data = tmp_data;
    int d = 0, k = 0, i = 0, j = 0, mi = 0, mj = 0, t = 0;
    for(d = 1; d < sum; d *= 2)         // O(log2n)
    {
        for(k = 0; k < sum; k += d * 2) // O(nlog2n)
        {
            i = k, j = k + d, t = k;
            mi = k + d < sum ? k + d : sum;
            mj = k + d * 2 < sum ? k + d * 2 : sum;
            while(i < mi && j < mj)
            {
                if(src_data[i] < src_data[j])
                {
                    dst_data[t++] = src_data[i++];
                } else
                {
                    dst_data[t++] = src_data[j++];
                }
            }
            while(i < mi) dst_data[t++] = src_data[i++];
            while(j < mj) dst_data[t++] = src_data[j++];
        }
        if(src_data == data)
        {
            src_data = tmp_data;
            dst_data = data;
        } else
        {
            src_data = data;
            dst_data = tmp_data;
        }
    }
    if(dst_data == data) memcpy(data, tmp_data, sizeof(int) * sum);
}

int quick_sort(int data[], int sum)
{
    int start[sum / 2], end[sum / 2];
    int t = 0;
    int i = 0, j = 0;
    int tmp = 0, mid;
    for(start[t] = 0, end[t] = sum - 1; t >= 0;)
    {
        if(start[t] >= end[t] - 1)
        {
            t--;
        }else
        {
            mid = end[t];
            for(i = start[t], j = i; i < end[t]; i++)
            {
                if(data[i] < data[mid])
                {
                    tmp = data[i];
                    data[i] = data[j];
                    data[j++] = tmp;
                }
            }
            tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
            start[t + 1] = j + 1;
            end[t + 1] = end[t];
            end[t++] = j - 1;
        }
    }
}

