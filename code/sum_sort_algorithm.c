// 排序算法
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#define LEN 101

#define BUBBLE_SORT 1
#define INSERT_SORT 2
#define SELECT_SORT 3
#define MERGE_SORT  4
#define QUICK_SORT  5
#define HEAP_SORT   6
#define COUNT_SORT  7
#define BUCKET_SORT 8
#define RADIX_SORT  9
#define SHELL_SORT  10

#define BUCKET_AMT 10
#define RADIX_BIT  5
#define radix_key(v, b) (((v) / (b)) % RADIX_BIT);

int data[LEN];

int main(void)
{
    struct timeval start, end;
    init(data, LEN);
    sort_test(data, LEN, BUBBLE_SORT, "bubble_sort");
    sort_test(data, LEN, INSERT_SORT, "insert_sort");
    sort_test(data, LEN, SELECT_SORT, "select_sort");
    sort_test(data, LEN, MERGE_SORT,  "merge_sort");
    sort_test(data, LEN, QUICK_SORT,  "quick_sort");
    sort_test(data, LEN, HEAP_SORT,   "heap_sort");
    sort_test(data, LEN, COUNT_SORT,  "count_sort");
    sort_test(data, LEN, BUCKET_SORT, "bucket_sort");
    sort_test(data, LEN, RADIX_SORT,  "radix_sort");
    sort_test(data, LEN, SHELL_SORT,  "shell_sort");
}

int init(int data[], int len)
{
    int i = 0;
    srand((int)time(0));
    for(; i < len; ++i)
        data[i] = rand() % len;
    printf("init list size:%d\n", LEN);
    print(data, LEN);
}

int print(int data[], int len)
{
    int i = 0;
    for(; i < len; ++i)
        printf("%d ", data[i]);
    printf("\n");
}

sort_test(int data[], int len, int type, char name[])
{
    int tmp[len];
    memcpy(tmp, data, sizeof(int) * len);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    switch(type)
    {
        case BUBBLE_SORT:
            bubble_sort(tmp, len);
            break;
        case INSERT_SORT:
            insert_sort(tmp, len);
            break;
        case SELECT_SORT:
            select_sort(tmp, len);
            break;
        case MERGE_SORT:
            merge_sort(tmp, len);
            break;
        case QUICK_SORT:
            quick_sort(tmp, len);
            break;
        case HEAP_SORT:
            heap_sort(tmp, len);
            break;
        case COUNT_SORT:
            count_sort(tmp, len);
            break;
        case BUCKET_SORT:
            bucket_sort(tmp, len);
            break;
        case RADIX_SORT:
            radix_sort(tmp, len);
            break;
        case SHELL_SORT:
            shell_sort(tmp, len);
            break;
    }
    gettimeofday(&end, NULL);
    long int cost = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("%s cost %ld us\n", name, cost);
    print(tmp, LEN);
}

int bubble_sort(int data[], int len)
{
    int i = 0, j = 0;
    int did = 0, tmp = 0;
    for(; i < len; i++)                 // O(n)
    {
        for(j = len - 2; j >= i; j--)   // O(n^2)
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

int insert_sort(int data[], int len)
{
    int i = 0, j = 0;
    int tmp = 0;
    for(; i < len; i++)                 // O(n)
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

int select_sort(int data[], int len)
{
    int i = 0, j = 0, s = 0;
    int tmp = 0;
    for(; i < len; i++)                       // O(n)
    {
        tmp = data[i];
        for(s = i, j = i + 1; j < len; j++)   // O(n^2)
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
int merge_sort(int data[], int len)
{
    int tmp_data[len];
    int *src_data = data, *dst_data = tmp_data;
    int d = 0, k = 0, i = 0, j = 0, mi = 0, mj = 0, t = 0;
    for(d = 1; d < len; d *= 2)         // O(log2n)
    {
        for(k = 0; k < len; k += d * 2) // O(nlog2n)
        {
            i = k, j = k + d, t = k;
            mi = k + d < len ? k + d : len;
            mj = k + d * 2 < len ? k + d * 2 : len;
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
    if(dst_data == data) memcpy(data, tmp_data, sizeof(int) * len);
}

int quick_sort(int data[], int len)
{
    int start[len / 2], end[len / 2];
    int t = 0;
    int i = 0, j = 0;
    int tmp = 0, mid;
    for(start[t] = 0, end[t] = len - 1; t >= 0;)
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

int heap_sort(int data[], int len)
{
    int index = 0, left = 0, right = 0, itmp = 0, tmp = 0;
    int i = 0;
    for(i = (len - 1) / 2; i >= 0; i--)
    {
        index = i;
        while(!0)
        {
            itmp = index, left = 2 * index + 1, right = 2 * (index + 1);
            if (left < len && data[itmp] < data[left]) itmp = left;
            if (right < len && data[itmp] < data[right]) itmp = right;
            if (itmp == index) break;
            tmp = data[index], data[index] = data[itmp], data[itmp] = tmp;
            index = itmp;
        }
    }
    for(i = len - 1; i > 0; i--)
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

int count_sort(int data[], int len)
{
    int i = 0, j = 0;
    int max = 0, tmp = 0;
    int tmp_data[len];
    for(i = 0, max = data[0]; i < len; i++)
    {
        if(data[i] > max)
        {
            max = data[i];
        }
    }
    int count_data[max + 1];
    memset(count_data, 0, sizeof(int) * (max + 1));
    for(i = 0; i < len; i++)
    {
        count_data[data[i]]++;
    }
    for(i = 1; i <= max; i++)
    {
        count_data[i] += count_data[i - 1];
    }
    for(i = len - 1; i >= 0; i--)
    {
        tmp = data[i];
        tmp_data[count_data[tmp]-- - 1] = tmp;
    }
    memcpy(data, tmp_data, sizeof(int) * len);
}

int bucket_sort(int data[], int len)
{
    int i = 0, j = 0;
    int max = 0;
    for(i = 0, max = data[0]; i < len; i++)
    {
        if(data[i] > max)
        {
            max = data[i];
        }
    }
    int tmp_data[BUCKET_AMT][max]; // link_list
    int tmp_count[BUCKET_AMT];
    memset(tmp_count, 0, sizeof(int) * BUCKET_AMT);
    for(i = 0; i < len; i++)
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

int radix_sort(int data[], int len)
{
    int i = 0, j = 0, k = 0;
    int max = 0, max_key = 0, tmp = 0;
    int tmp_data[len];
    for(i = 0, max = data[0]; i < len; i++)
    {
        if(data[i] > max)
        {
            max = data[i];
        }
    }
    int *src_data = data, *dst_data = tmp_data;
    for(k = 1; k <= max; k *= RADIX_BIT)
    {
        int bucket[RADIX_BIT] = {0};
        max_key = radix_key(src_data[0], k);
        for(i = 0; i < len; i++)
        {
            tmp = radix_key(src_data[i], k);
            if(tmp > max_key)
            {
                max_key = tmp;
            }
        }
        for(i = 0; i < len; i++)
        {
            tmp = radix_key(src_data[i], k);
            bucket[tmp]++;
        }
        for(i = 1; i <= max_key; i++)
        {
            bucket[i] += bucket[i - 1];
        }
        for(i = len - 1; i >= 0; i--)
        {
            tmp = radix_key(src_data[i], k);
            dst_data[bucket[tmp]-- - 1] = src_data[i];
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
    if(dst_data == data) memcpy(data, tmp_data, sizeof(int) * len);
}

int shell_sort(int data[], int len)
{
    int i = 0, j = 0, k = 0;
    int tmp = 0;
    for(k = len >> 1; k > 0; k >>= len)
    {
        for(i = 0; i < len; i += k)
        {
            tmp = data[i];
            for(j = i; j > 0; j -= k)
            {
                if(tmp < data[j - k])
                {
                    data[j] = data[j - k];
                } else
                {
                    data[j] = tmp;
                    break;
                }
            }
            if (j == 0) data[0] = tmp;
        }
    }
}

