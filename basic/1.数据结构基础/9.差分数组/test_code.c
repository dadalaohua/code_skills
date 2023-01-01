#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//// 差分数组工具类
//class Difference {
//    // 差分数组
//    private int[] diff;
//
//    /* 输入一个初始数组，区间操作将在这个数组上进行 */
//    public Difference(int[] nums) {
//        assert nums.length > 0;
//        diff = new int[nums.length];
//        // 根据初始数组构造差分数组
//        diff[0] = nums[0];
//        for (int i = 1; i < nums.length; i++) {
//            diff[i] = nums[i] - nums[i - 1];
//        }
//    }
//
//    /* 给闭区间 [i,j] 增加 val（可以是负数）*/
//    public void increment(int i, int j, int val) {
//        diff[i] += val;
//        if (j + 1 < diff.length) {
//            diff[j + 1] -= val;
//        }
//    }
//
//    /* 返回结果数组 */
//    public int[] result() {
//        int[] res = new int[diff.length];
//        // 根据差分数组构造结果数组
//        res[0] = diff[0];
//        for (int i = 1; i < diff.length; i++) {
//            res[i] = res[i - 1] + diff[i];
//        }
//        return res;
//    }
//}

/* 输入一个初始数组，区间操作将在这个数组上进行 */
int* DifferenceCreate(int* nums, int numsSize) {
    int* diff = malloc(numsSize * sizeof(int));
    // 根据初始数组构造差分数组
    diff[0] = nums[0];
    for (int i = 1; i < numsSize; i++) {
        diff[i] = nums[i] - nums[i - 1];
    }
    return diff;
}

/* 给闭区间 [i,j] 增加 val（可以是负数）*/
void DifferenceIncrement(int* diff, int diffSize, int i, int j, int val) {
    diff[i] += val;
    if (j + 1 < diffSize) {
        diff[j + 1] -= val;
    }
}

/* 返回结果数组 */
int* DifferenceResult(int* diff, int diffSize) {
    int* res = malloc(diffSize * sizeof(int));
    // 根据差分数组构造结果数组
    res[0] = diff[0];
    for (int i = 1; i < diffSize; i++) {
        res[i] = res[i - 1] + diff[i];
    }
    return res;
}

/* 释放差分和结果数组 */
void DifferenceFree(int* diff, int* res) {
    if(diff != NULL) {
        free(diff);
    }
    
    if(res != NULL) {
        free(res);
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int nums[] = {0,1,2,3,4,5,6,7,8,9};
    int len = sizeof(nums)/sizeof(int);
    int* diff = DifferenceCreate(nums, len);
    
    DifferenceIncrement(diff, len, 0, len - 1, 5);
    DifferenceIncrement(diff, len, 0, len / 2, -5);
    DifferenceIncrement(diff, len, len / 2, len - 1, 3);
    
    int* res = DifferenceResult(diff, len);
    for(int i = 0; i < len; i++) {
        printf("%d,", res[i]);
    }
    printf("\n");
    
    DifferenceFree(diff, res);
    
    return 0;
}