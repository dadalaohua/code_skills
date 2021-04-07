#include <stdio.h>

/*冒泡排序, 递增排序*/
void bubblesort_inc(int buf[],int len)          /*冒泡排序*/
{
    int i,j,tmp ,flag = 1;
    
    for(i = 0;i < len-1 && flag == 1;i++)       /*执行n-1趟排序*/
    { 
        flag = 0;
        for(j = 0; j < (len-i-1); j++)
        {
            if(buf[j] > buf[j+1])               /*数据交换*/
            {
                tmp      = buf[j+1];
                buf[j+1] = buf[j];
                buf[j]   = tmp;
                flag     = 1;
            }
        }
    }
}

/*冒泡排序, 递减排序*/
void bubblesort_dec(int buf[],int len)          /*冒泡排序*/
{
    int i,j,tmp ,flag = 1;
    
    for(i = 0;i < len-1 && flag == 1;i++)       /*执行n-1趟排序*/
    { 
        flag = 0;
        for(j = 0; j < (len-i-1); j++)
        {
            if(buf[j] < buf[j+1])               /*数据交换*/
            {
                tmp      = buf[j+1];
                buf[j+1] = buf[j];
                buf[j]   = tmp;
                flag     = 1;
            }
        }
    }
}

int main(int argc, char* argv[])
{ 
    int i, buf[10] = {2,5,6,3,-7,8,0,9,12,1};           /*初始化序列*/
    
    printf("The orginal data array is\n") ;
    for(i = 0; i < 10; i++)                             /*显示原序列之中的元素*/
        printf("%d ",buf[i]);
        
    bubblesort_inc(buf, sizeof(buf)/sizeof(int));       /*冒泡排序*/
    
    printf("\nThe result of bubble sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    bubblesort_dec(buf, sizeof(buf)/sizeof(int));       /*冒泡排序*/
    
    printf("\nThe result of bubble sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    return 0;
}