#include <stdio.h>

/*******************************************************************************
* Function Name  : rabs
* Description    : 产生任意区间内均匀分布的随机整数序列
* Input          : int a: 随机整数所在的区间[a,b]
                   int b: 随机整数所在的区间[a,b]
                   int *r: 指向随机数种子,要求是大于零的奇数
                   int p[]:随机整数序列
                   int n: 随机整数序列长度
* Output         : None.
* Return         : None.
*******************************************************************************/
void rabs(int a, int b, int *r, int p[], int n)
{
    int k,l,m,i;
    
    k = b-a+1;
    l = 2;
    
    while (l<k)
        l=l+l;
    
    m = 4*l;
    k = *r;
    i = 0;
    
    while (i<=n-1)
    { 
        k = k+k+k+k+k;
        k = k%m;
        l = k/4+a;
        
        if (l<=b)
        {
            p[i]=l;
            i=i+1;
        }
      }
    *r=k;
    
    return;
}

/*******************************************************************************
* Function Name  : ibub
* Description    : 整数冒泡排序
* Input          : int p[]: 指向待排序序列(为顺序存储)的起始位置
                   int n：待排序序列的长度
* Output         : None.
* Return         : None.
*******************************************************************************/
void ibub(int p[], int n)
{
    int m,k,j,i,d;
    
    k = 0;
    m = n-1;
    
    while (k < m)
    { 
        j=m-1;
        m = 0;
        for (i = k; i <= j; i++)
            if (p[i]>p[i+1])
            {
                d = p[i];
                p[i] = p[i+1];
                p[i+1] = d;
                m = i;
            }
        
        j = k + 1;
        k = 0;
        
        for (i = m; i >= j; i--)
            if (p[i-1]>p[i])
            {
                d = p[i];
                p[i] = p[i-1];
                p[i-1] = d;
                k = i;
            }
    }
      
    return;
}

int main(int argc, char* argv[])
{ 
    int i,j,p[100],r0,*r,*s;
    
    r0 = 5;
    r  = &r0;
    s  = p+30;
    
    rabs(100, 300, r, p, 100);
    
    printf("\n");
    for (i=0; i<=9; i++)
    {
        for (j=0; j<=9; j++)
            printf("%d   ",p[10*i+j]);
        printf("\n");
    }
    printf("\n");
    
    ibub(s,50);
    
    for (i=0; i<=9; i++)
    { 
        for (j=0; j<=9; j++)
            printf("%d   ",p[10*i+j]);
        printf("\n");
    }
    printf("\n");
    
    return 0;
}