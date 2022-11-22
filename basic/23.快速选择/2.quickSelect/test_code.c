#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
https://leetcode.cn/problems/find-kth-largest-xor-coordinate-value/solution/zhao-chu-di-k-da-de-yi-huo-zuo-biao-zhi-mgick/
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
static inline int partition(int* arr, int left, int right) {
    int pivot = arr[right], pos = left;
    for (int i = left; i < right; ++i) {
        if (arr[i] <= pivot) {
            int tmp = arr[pos];
            arr[pos] = arr[i];
            arr[i] = tmp;
            pos++;
        }
    }
    int tmp = arr[pos];
    arr[pos] = arr[right];
    arr[right] = tmp;
    return pos;
}

static inline int randomPartition(int* arr, int left, int right) {
    int pivot = rand() % (right - left + 1) + left;
    int tmp = arr[pivot];
    arr[pivot] = arr[right];
    arr[right] = tmp;
    return partition(arr, left, right);
}

int quickSelect(int* arr, int left, int right, int index) {
    int q = randomPartition(arr, left, right);
    if (q == index) {
        return arr[q];
    } else {
        return q < index ? quickSelect(arr, q + 1, right, index)
                         : quickSelect(arr, left, q - 1, index);
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int buf[] = {9,5,4,1,2,8,6,7,3,0};
    int k;
    srand(time(0));
    k = 5;
    printf("k %d is %d\n", k, quickSelect(buf, 0, sizeof(buf)/sizeof(int) - 1, k));
    k = 1;
    printf("k %d is %d\n", k, quickSelect(buf, 0, sizeof(buf)/sizeof(int) - 1, k));
    k = 8;
    printf("k %d is %d\n", k, quickSelect(buf, 0, sizeof(buf)/sizeof(int) - 1, k));
    return 0;
}