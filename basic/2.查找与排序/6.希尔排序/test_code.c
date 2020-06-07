#include <stdio.h>

/*希尔排序, 递增排序*/
void shellsort_inc(int buf[],int len)
{
    int i, j, flag ,gap = len;
    int tmp;
    
    while(gap > 1)
    { 
        gap = gap/2;                /*增量缩小，每次减半*/
        do{                         /*子序列应用冒泡排序*/
            flag = 0;
            for(i = 0;i < len-gap ;i++)
            {
                j = i + gap;
                if(buf[i] > buf[j])
                {
                    tmp    = buf[i];
                    buf[i] = buf[j];
                    buf[j] = tmp;
                    flag   = 1;
                }
            }
        }while(flag != 0);
    }
}

/*希尔排序, 递减排序*/
void shellsort_dec(int buf[],int len)
{
    int i, j, flag ,gap = len;
    int tmp;
    
    while(gap > 1)
    { 
        gap = gap/2;                /*增量缩小，每次减半*/
        do{                         /*子序列应用冒泡排序*/
            flag = 0;
            for(i = 0;i < len-gap ;i++)
            {
                j = i + gap;
                if(buf[i] < buf[j])
                {
                    tmp    = buf[i];
                    buf[i] = buf[j];
                    buf[j] = tmp;
                    flag   = 1;
                }
            }
        }while(flag != 0);
    }
}

int main(int argc, char* argv[])
{ 
    int i, buf[10] = {2,5,6,3,-7,8,0,9,12,1};           /*初始化序列*/
    
    printf("The orginal data array is\n") ;
    for(i = 0; i < 10; i++)                             /*显示原序列之中的元素*/
        printf("%d ",buf[i]);
        
    shellsort_inc(buf, sizeof(buf)/sizeof(int));       /*执行希尔排序*/
    
    printf("\nThe result of Shell's sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    shellsort_dec(buf, sizeof(buf)/sizeof(int));       /*执行希尔排序*/
    
    printf("\nThe result of Shell's sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    return 0;
}