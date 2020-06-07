#include <stdio.h>

/*选择排序, 递增排序*/
void selectsort_inc(int buf[],int len)  /*选择排序*/
{
    int i,j;
    int min;
    int tmp;
    
    for(i = 0; i < len; i++)
    {
        min = i;
        for(j = i+1; j < len; j++)      /*在后n-(i+1)个元素中找到最小的元素位置*/
        {
            if(buf[j] < buf[min])
                min = j;                /*用min记录下最小元素的位置*/
        }
        
        if(min != i){                   /*如果最小的元素不位于后n-(i+1)个元素档第1个*/
            tmp       = buf[min];       /*元素的交换*/
            buf[min]  = buf[i];
            buf[i]    = tmp;
        }
    }
}

/*选择排序, 递减排序*/
void selectsort_dec(int buf[],int len)  /*选择排序*/
{
    int i,j;
    int max;
    int tmp;
    
    for(i = 0; i < len; i++)
    {
        max = i;
        for(j = i+1; j < len; j++)      /*在后n-(i+1)个元素中找到最大的元素位置*/
        {
            if(buf[j] > buf[max])
                max = j;                /*用min记录下最大元素的位置*/
        }
        
        if(max != i){                   /*如果最大的元素不位于后n-(i+1)个元素档第1个*/
            tmp       = buf[max];       /*元素的交换*/
            buf[max]  = buf[i];
            buf[i]    = tmp;
        }
    }
}

int main(int argc, char* argv[])
{ 
    int i, buf[10] = {2,5,6,3,-7,8,0,9,12,1};           /*初始化序列*/
    
    printf("The orginal data array is\n") ;
    for(i = 0; i < 10; i++)                             /*显示原序列之中的元素*/
        printf("%d ",buf[i]);
        
    selectsort_inc(buf, sizeof(buf)/sizeof(int));       /*插入排序*/
    
    printf("\nThe result of selection sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    selectsort_dec(buf, sizeof(buf)/sizeof(int));       /*插入排序*/
    
    printf("\nThe result of selection sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    return 0;
}