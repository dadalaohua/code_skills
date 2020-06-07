#include <stdio.h>

/*******************************************************************************
* Function Name  : rnds
* Description    : 产生0-1之间均匀分布的随机数序列
* Input          : double *r: 指向随机数种子
                   double p[]: 返回随机数序列
                   int n: 随机数序列长度
* Output         : None.
* Return         : None.
*******************************************************************************/
void rnds(double *r, double p[], int n)
{
    int i,m;
    double s,u,v;
    
    s=65536.0;
    u=2053.0;
    v=13849.0;
    
    for (i=0; i<=n-1; i++)
    {
        *r=u*(*r)+v;
        m=(int)(*r/s);
        *r=*r-m*s; p[i]=*r/s;
    }
    
    return;
}

int main(int argc, char* argv[])
{ 
    int i,j;
    double p[50],r;
    
    r=1.0; 
    rnds(&r, p, 50);
    
    printf("\n");
    
    for (i=0; i<=9; i++)
    {
        for (j=0; j<=4; j++)
            printf("%10.7lf  ",p[5*i+j]);
        printf("\n");
    }
    printf("\n");
    
    return 0;
}