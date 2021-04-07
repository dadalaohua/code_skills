#include <stdio.h>

/*直接插入排序, 递增排序*/
int insertsort_inc(int buf[],int len)               /*直接插入排序*/
{
    int i, j;
    int tmp;
    
    for(i = 1; i < len; i++)                  /*循环n-1次，执行n-1趟插入排序*/                      
    {
        tmp = buf[i];                         /*将buf[i]保存在临时变量中*/ 
        j = i - 1;
        while(j >= 0 && tmp < buf[j])         /*找到tmp的插入位置*/
            buf[j+1] = buf[j--];              /*将buf[j]后移，再将j减1*/
            
        buf[j+1] = tmp;                       /*将元素tmp插入指定位置，第i-1趟插入完成*/
    }
    
    return 0;
}

/*直接插入排序, 递减排序*/
int insertsort_dec(int buf[],int len)         /*直接插入排序*/
{
    int i, j;
    int tmp;
    
    for(i = 1; i < len; i++)                  /*循环n-1次，执行n-1趟插入排序*/                      
    {
        tmp = buf[i];                         /*将buf[i]保存在临时变量中*/ 
        j = i - 1;
        while(j >= 0 && tmp > buf[j])         /*找到tmp的插入位置*/
            buf[j+1] = buf[j--];              /*将buf[j]后移，再将j减1*/
            
        buf[j+1] = tmp;                       /*将元素tmp插入指定位置，第i-1趟插入完成*/
    }
    
    return 0;
}

int main(int argc, char* argv[])
{ 
    int i, buf[10] = {2,5,6,3,7,8,0,9,12,1};        /*初始化序列*/
    
    printf("The orginal data array is\n") ;
    for(i = 0; i < 10; i++)                         /*显示原序列之中的元素*/
        printf("%d ",buf[i]);
        
    insertsort_inc(buf, sizeof(buf)/sizeof(int));       /*插入排序*/
    
    printf("\nThe result of insertion sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    insertsort_dec(buf, sizeof(buf)/sizeof(int));       /*插入排序*/
    
    printf("\nThe result of insertion sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    return 0;
}