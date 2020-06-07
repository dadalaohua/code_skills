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

int main(int argc, char* argv[])
{ 
    int i,j,p[50],r;
    
    r=1;
    
    rabs(100, 300, &r, p, 50);
    
    printf("\n");
    
    for (i=0; i<=4; i++)
    {
        for (j=0; j<=9; j++)
        printf("%d   ",p[10*i+j]);
        printf("\n");
    }
    printf("\n");
    
    return 0;
}