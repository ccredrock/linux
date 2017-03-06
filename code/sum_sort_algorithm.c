// 排序算法
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#define SIZE 101
#define NAME 20

#define BUBBLE_SORT 1
#define INSERT_SORT 2
#define SELECT_SORT 3
#define MERGE_SORT  4
#define QUICK_SORT  5
#define HEAP_SORT   6
#define COUNT_SORT  7
#define BUCKET_SORT 8
#define RADIX_SORT  9

#define BUCKET_AMT 10
#define RADIX_BIT  10
#define radix_key(v, b) (v / b % RADIX_BIT);

int data[SIZE];

int main(void)
{
    struct timeval start, end;
    init(data, SIZE);
    sort_test(data, SIZE, BUBBLE_SORT, "bubble_sort");
    sort_test(data, SIZE, INSERT_SORT, "insert_sort");
    sort_test(data, SIZE, SELECT_SORT, "select_sort");
    sort_test(data, SIZE, MERGE_SORT,  "merge_sort");
    sort_test(data, SIZE, QUICK_SORT,  "quick_sort");
    sort_test(data, SIZE, HEAP_SORT,   "heap_sort");
    sort_test(data, SIZE, COUNT_SORT,  "count_sort");
    sort_test(data, SIZE, BUCKET_SORT, "bucket_sort");
    sort_test(data, SIZE, RADIX_SORT,  "radix_sort");
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
        case HEAP_SORT:
            heap_sort(tmp, sum);
            break;
        case COUNT_SORT:
            count_sort(tmp, sum);
            break;
        case BUCKET_SORT:
            bucket_sort(tmp, sum);
            break;
        case RADIX_SORT:
            radix_sort(tmp, sum);
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
                tmp = data[j], data[j] = data[j + 1], data[j + 1] = tmp;
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
        if(start[t] >= end[t])
        {
            t--;
        }else
        {
            mid = end[t];
            for(i = start[t], j = i; i < end[t]; i++)
            {
                if(data[i] < data[mid])
                {
                    tmp = data[i], data[i] = data[j], data[j++] = tmp;
                }
            }
            tmp = data[i], data[i] = data[j], data[j] = tmp;
            start[t + 1] = j + 1;
            end[t + 1] = end[t];
            end[t++] = j - 1;
        }
    }
}

int heap_sort(int data[], int sum)
{
    int index = 0, left = 0, right = 0, itmp = 0, tmp = 0;
    int i = 0;
    for(i = (sum - 1) / 2; i >= 0; i--)
    {
        index = i;
        while(!0)
        {
            itmp = index, left = 2 * index + 1, right = 2 * (index + 1);
            if (left < sum && data[itmp] < data[left]) itmp = left;
            if (right < sum && data[itmp] < data[right]) itmp = right;
            if (itmp == index) break;
            tmp = data[index], data[index] = data[itmp], data[itmp] = tmp;
            index = itmp;
        }
    }
    for(i = sum - 1; i > 0; i--)
    {
        tmp = data[0], data[0] = data[i], data[i] = tmp;
        index = 0;
        while(!0)
        {
            itmp = index, left = 2 * index + 1, right = 2 * (index + 1);
            if (left < i && data[itmp] < data[left]) itmp = left;
            if (right < i && data[itmp] < data[right]) itmp = right;
            if (itmp == index) break;
            tmp = data[index], data[index] = data[itmp], data[itmp] = tmp;
            index = itmp;
        }
    }
}

int count_sort(int data[], int sum)
{
    int i = 0, j = 0;
    int max = 0, tmp = 0;
    int tmp_data[sum];
    for(i = 0, max = data[0]; i < sum; i++)
    {
        if(data[i] > max)
        {
            max = data[i];
        }
    }
    int count_data[max + 1];
    memset(count_data, 0, sizeof(int) * (max + 1));
    for(i = 0; i < sum; i++)
    {
        count_data[data[i]]++;
    }
    for(i = 1; i <= max; i++)
    {
        count_data[i] += count_data[i - 1];
    }
    for(i = sum - 1; i >= 0; i--)
    {
        tmp = data[i];
        tmp_data[count_data[tmp] - 1] = tmp;
        count_data[tmp]--;
    }
    memcpy(data, tmp_data, sizeof(int) * sum);
}

int bucket_sort(int data[], int sum)
{
    int i = 0, j = 0;
    int max = 0;
    for(i = 0, max = data[0]; i < sum; i++)
    {
        if(data[i] > max)
        {
            max = data[i];
        }
    }
    int tmp_data[BUCKET_AMT][max]; // link_list
    int tmp_count[BUCKET_AMT];
    memset(tmp_count, 0, sizeof(int) * BUCKET_AMT);
    for(i = 0; i < sum; i++)
    {
        j = data[i] * BUCKET_AMT / (max + 1);
        tmp_data[j][tmp_count[j]++] = data[i];
    }
    for(i = 0, j = 0; j < BUCKET_AMT; j++)
    {
        int count = tmp_count[j];
        quick_sort(tmp_data[j], count);
        memcpy(&data[i], tmp_data[j], sizeof(int) * count);
        i += count;
    }
}

int radix_sort(int data[], int sum)
{
    int i = 0, j = 0, k = 0;
    int max = 0, max_key = 0, tmp = 0;
    for(i = 0, max = data[0]; i < sum; i++)
    {
        if(data[i] > max)
        {
            max = data[i];
        }
    }
    int tmp_data[BUCKET_AMT][max]; // link_list
    int tmp_count[BUCKET_AMT];
    for(k = 1; k <= max; k *= RADIX_BIT)
    {
        max_key = radix_key(data[0], k);
        for(i = 0; i < sum; i++)
        {
            tmp = radix_key(data[i], k);
            if(tmp > max_key)
            {
                max_key = tmp;
            }
        }
        memset(tmp_count, 0, sizeof(int) * BUCKET_AMT);
        for(i = 0; i < sum; i++)
        {
            tmp = radix_key(data[i], k);
            j = tmp * BUCKET_AMT / (max_key + 1);
            tmp_data[j][tmp_count[j]++] = data[i];
        }
        for(i = 0, j = 0; j < BUCKET_AMT; j++)
        {
            int count = tmp_count[j];
            if (count > 0)
            {
                count_sort(tmp_data[j], count);
                memcpy(&data[i], tmp_data[j], sizeof(int) * count);
                i += count;
            }
        }
    }
}

