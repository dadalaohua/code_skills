#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int** test_function(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){

    //返回长度赋值
    *returnSize = numsSize;
    
    int** ret = malloc(sizeof(int *) * (*returnSize));
    
    //返回的数据列数
    (*returnColumnSizes) = malloc(sizeof(int) * (*returnSize));
    for(int i = 0; i < (*returnSize); i++) {
        (*returnColumnSizes)[i] = 2;
    }
    
    //数据赋值
    int *tmp;
    for(int i = 0; i < (*returnSize); i++) {
        tmp = malloc(sizeof(int) * 2);
        tmp[0] = i;
        tmp[1] = i+1;
        *(ret + i) = tmp;
    }
    
    return ret;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int nums[] = {1, 2, 3, 4, 5, 6};
    int returnSize;
    int* returnColumnSizes;
    int** val;
    
    val = test_function(nums, sizeof(nums)/sizeof(int), &returnSize, &returnColumnSizes);
    for(int i = 0; i < returnSize; i++) {
        for(int j = 0; j < *(returnColumnSizes + i); j++) {
            printf("%d ", *(*(val + i) + j));
        }
        printf("\n");
    }
    printf("\n");
    
    for(int i = 0; i < returnSize; i++) {
        for(int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", val[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    for(int i = 0; i < returnSize; i++) {
        for(int j = 0; j < *(returnColumnSizes + i); j++) {
            printf("%d ", (*(val + i))[j]);
        }
        printf("\n");
    }
    printf("\n");
    
    return 0;
}