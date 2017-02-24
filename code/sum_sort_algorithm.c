// 排序算法
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define SIZE 100

int data[SIZE];

int main(void)
{
    struct timeval start, end;
    init(data, SIZE);
    printf("before sort:\n");
    print(data, SIZE);
    gettimeofday(&start, NULL);
    bubble_sort(data, SIZE);
    gettimeofday(&end, NULL);
    printf("after sort %ld us:\n", 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec);
    print(data, SIZE);
}

int init(int data[], int sum)
{
    int i = 0;
    for(; i < sum; ++i)
        data[i] = rand()%sum;
}

int print(int data[], int sum)
{
    int i = 0;
    for(; i < sum; ++i)
        printf("%d ", data[i]);
    printf("\n");
}

int bubble_sort(int data[], int sum)
{
    int i = 0, j = 0;
    int did = 0, tmp = 0;
    for(; i < sum; i++)
    {
        for(j = sum - 2; j >= i; j--)
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
}
