#include <stdio.h>

void adjust_inc(int k[], int i, int n)
{
    int j;
    int tmp;
    tmp = k[i];
    
    j = 2 * i;      /*j为i的左孩子结点序号*/
    while(j <= n)
    {
        if(j < n && k[j] < k[j+1])
        {
            j++;      /*j为i的左右孩子中较大孩子的序号*/
        }
        if(tmp >= k[j])
        {
            break;     /*不需要再调整了*/ 
        }
        k[j/2] = k[j];     /*子结点与父结点交换位置*/ 
        j = 2 * j;     /*继续往下调整*/ 
    }
    k[j/2] = tmp;
}

/*堆排序, 递增排序*/
void heapsort_inc(int k[], int n)
{
    int i;
    int tmp;
    
    for(i = n/2; i >= 1; i--)
    {
        adjust_inc(k, i, n);        /*将原始序列初始化为一个堆*/
    }
    
    for(i = n-1; i >= 1; i--)
    {                           /*交换第1个和第n个元素，再将根结点向下调整*/
        tmp    = k[i+1];
        k[i+1] = k[1];          /*交换第1个和第n个元素*/
        k[1]   = tmp;
        adjust_inc(k, 1, i);        /*将根结点向下调整*/
    }
}

void adjust_dec(int k[], int i, int n)
{
    int j;
    int tmp;
    tmp = k[i];
    
    j = 2 * i;      /*j为i的左孩子结点序号*/
    while(j <= n)
    {
        if(j < n && k[j] > k[j+1])
        {
            j++;      /*j为i的左右孩子中较大孩子的序号*/
        }
        if(tmp <= k[j])
        {
            break;     /*不需要再调整了*/ 
        }
        k[j/2] = k[j];     /*子结点与父结点交换位置*/ 
        j = 2 * j;     /*继续往下调整*/ 
    }
    k[j/2] = tmp;
}

/*堆排序, 递减排序*/
void heapsort_dec(int k[], int n)
{
    int i;
    int tmp;
    
    for(i = n/2; i >= 1; i--)
    {
        adjust_dec(k, i, n);        /*将原始序列初始化为一个堆*/
    }
    
    for(i = n-1; i >= 1; i--)
    {                               /*交换第1个和第n个元素，再将根结点向下调整*/
        tmp    = k[i+1];
        k[i+1] = k[1];              /*交换第1个和第n个元素*/
        k[1]   = tmp;
        adjust_dec(k, 1, i);        /*将根结点向下调整*/
    }
}

int main(int argc, char* argv[])
{ 
    int i, buf[10] = {2,5,6,3,-7,8,0,9,12,1};           /*初始化序列*/
    int buf_tmp[11];           /*初始化序列*/
    
    printf("The orginal data array is\n") ;
    for(i = 0; i < 10; i++)                             /*显示原序列之中的元素*/
        printf("%d ",buf[i]);
        
    memcpy(&buf_tmp[1], buf, sizeof(buf));
    heapsort_inc(buf_tmp, sizeof(buf)/sizeof(int));         /*堆排序*/
    
    memcpy(buf, &buf_tmp[1], sizeof(buf));
    printf("\nThe result of heap sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    memcpy(&buf_tmp[1], buf, sizeof(buf));
    heapsort_dec(buf_tmp, sizeof(buf)/sizeof(int));         /*堆排序*/
    
    memcpy(buf, &buf_tmp[1], sizeof(buf));
    printf("\nThe result of heap sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    return 0;
}