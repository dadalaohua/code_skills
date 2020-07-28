#include <stdio.h>

/*******************************************************************************
* Function Name  : rab1
* Description    : 产生任意区间内均匀分布的一个随机整数
* Input          : int a: 随机整数所在的区间[a,b]
                   int b: 随机整数所在的区间[a,b]
                   int *r: 指向随机数种子,应为大于零的奇数
* Output         : None.
* Return         : int p：返回一个在区间[a,b]内的随机整数
*******************************************************************************/
int rab1(int a, int b, int *r)
{ 
    int k,l,m,i,p;
    
    k = b-a+1;
    l = 2;
    
    while(l<k)
        l=l+l;
    
    m=4*l;
    k=*r;
    i=1;
    
    while(i<=1)
    {
        k=k+k+k+k+k;
        k=k%m;
        l=k/4+a;
        
        if (l<=b)
        {
            p=l;
            i=i+1;
        }
    }
    *r=k;
    
    return(p);
}

int main(int argc, char* argv[])
{ 
    int i,j,r;
    
    r = 5;
    
    printf("\n");
    for (i=0; i<=4; i++)
    {
        for (j=0; j<=9; j++)
        printf("%d   ",rab1(101, 200, &r));
        printf("\n");
    }
    printf("\n");
    
    return 0;
}