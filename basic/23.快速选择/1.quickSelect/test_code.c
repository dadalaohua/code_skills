#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    https://www.jianshu.com/p/ba148b18974f
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
//用于数组两个位置之间数据交换
void swap(int* arr, int a, int b)
{
      int temp = arr[b];
      arr[b] = arr[a];
      arr[a] = temp;
}

//划分算法
//返回基数划分后所在的下标
int partition(int left, int right, int pivot_index, int* arr)
{
    int pivot = arr[pivot_index];
    swap(arr, pivot_index, right); //将基数放置最后
    int save = left;
    
    for(int i = left; i <= right; i++)
    {
        if(arr[i] < pivot)
        {
             swap(arr, save, i);
             save++;
        }
    }
    
    //将基数和save所指的数据交换
    swap(arr, save, right);
    return save;
}

//快速选择
int quickSelect(int left, int right, int k, int* arr)
{
    if(left == right)   //只有一个元素时
    {
        return arr[left]; //直接返回
    }
    int pivot_index = (right + left)/2;
    
    //进行划分
    pivot_index = partition(left, right, pivot_index, arr);
    
    if(k == pivot_index)
    {
        return arr[pivot_index];
    }
    if(k < pivot_index)
    {
        return quickSelect(left, pivot_index - 1, k, arr);
    }
    
    return quickSelect(pivot_index + 1, right, k, arr);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int buf[] = {9,5,4,1,2,8,6,7,3,0};
    int k;
    k = 5;
    printf("k %d is %d\n", k, quickSelect(0, sizeof(buf)/sizeof(int) - 1, k, buf));
    k = 1;
    printf("k %d is %d\n", k, quickSelect(0, sizeof(buf)/sizeof(int) - 1, k, buf));
    k = 8;
    printf("k %d is %d\n", k, quickSelect(0, sizeof(buf)/sizeof(int) - 1, k, buf));
    return 0;
}