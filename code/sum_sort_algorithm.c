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

int data[SIZE];

int main(void)
{
    struct timeval start, end;
    init(data, SIZE);
    sort_test(data, SIZE, BUBBLE_SORT, "bubble_sort");
    sort_test(data, SIZE, INSERT_SORT, "insert_sort");
    sort_test(data, SIZE, SELECT_SORT, "select_sort");
}

int init(int data[], int sum)
{
    int i = 0;
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
    for(; i < sum; i++)
    {
        for(j = sum - 2; j >= i; j--)      // O(n)
        {
            if(data[j] > data[j + 1])       // O(n^2)
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
    for(; i < sum; i++)
    {
        tmp = data[i];                  // O(n)
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
    for(; i < sum; i++)
    {
        tmp = data[i];                  // O(n)
        for(s = i, j = i + 1; j < sum; j++)    // O(n^2)
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
