#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    在从小到大的排序数组中
    二分查找第一个大于或等于key的数值，找到返回该数值的地址，不存在则返回最后一个数值的下一个位置。
*/
int lower_bound(int* buf, int len, int key) {
    int l = 0, r = len;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (buf[mid] < key) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

/*
    在从小到大的排序数组中
    二分查找第一个大于key的数值，找到返回该数值的地址，不存在则返回最后一个数值的下一个位置。
*/
int upper_bound(int* buf, int len, int key) {
    int l = 0, r = len;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (buf[mid] <= key) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

/*
    在从大到小的排序数组中
    二分查找第一个小于或等于key的数值，找到返回该数值的地址，不存在则返回最后一个数值的下一个位置。
*/
int lower_bound_r(int* buf, int len, int key) {
    int l = 0, r = len;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (buf[mid] > key) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

/*
    在从大到小的排序数组中
    二分查找第一个小于key的数值，找到返回该数值的地址，不存在则返回最后一个数值的下一个位置。
*/
int upper_bound_r(int* buf, int len, int key) {
    int l = 0, r = len;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (buf[mid] >= key) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int buf[] = {0, 1, 3, 5, 6, 7, 8};
    
    printf("lower_bound test\n");
    for(int i = 0; i < 10; i++) {
        int id = lower_bound(buf, sizeof(buf)/sizeof(int), i);
        printf("%d %d %d\n", i, id, id < sizeof(buf)/sizeof(int) ? buf[id] : -1);
    }
    printf("\n");
    
    printf("upper_bound test\n");
    for(int i = 0; i < 10; i++) {
        int id = upper_bound(buf, sizeof(buf)/sizeof(int), i);
        printf("%d %d %d\n", i, id, id < sizeof(buf)/sizeof(int) ? buf[id] : -1);
    }
    printf("\n");
    
    int buf_r[] = {9, 8, 6, 5, 4, 3, 1};
    
    printf("lower_bound_r test\n");
    for(int i = 0; i < 10; i++) {
        int id = lower_bound_r(buf_r, sizeof(buf_r)/sizeof(int), i);
        printf("%d %d %d\n", i, id, id < sizeof(buf_r)/sizeof(int) ? buf_r[id] : -1);
    }
    printf("\n");
    
    printf("upper_bound_r test\n");
    for(int i = 0; i < 10; i++) {
        int id = upper_bound_r(buf_r, sizeof(buf_r)/sizeof(int), i);
        printf("%d %d %d\n", i, id, id < sizeof(buf_r)/sizeof(int) ? buf_r[id] : -1);
    }
    printf("\n");
    
    return 0;
}