#include <stdio.h>

/*******************************************************************************
* Function Name  : rnd1
* Description    : 产生0到1之间均匀分布的一个随机数
* Input          : double *r: 指向随机数种子
* Output         : None.
* Return         : double p：返回一个0~1之间均匀分布的随机数
*******************************************************************************/
double rnd1(double *r)
{
    int m;
    double s,u,v,p;
    
    s=65536.0;
    u=2053.0;
    v=13849.0;
    
    m=(int)(*r/s);
    *r=*r-m*s;
    *r=u*(*r)+v;
    m=(int)(*r/s);
    *r=*r-m*s;
    p=*r/s;
    
    return(p);
}

int main(int argc, char* argv[])
{ 
    int i;
    double r;
    
    r=5.0;
    
    printf("\n");
    
    for (i = 0; i <= 9; i++)
       printf("%10.7lf\n",rnd1(&r));
   
    printf("\n");
    
    return 0;
}