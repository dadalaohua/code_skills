#include <stdio.h>

/*******************************************************************************
* Function Name  : plyv
* Description    : 一维多项式求职
* Input          : double a[]: 存放n-1次多项式的n个系数
                   int n:      多项式的项数
                   double x:   指定的自变量值
* Output         : None.
* Return         : double plyv()：返回多项式值
*******************************************************************************/
double plyv(double a[], int n, double x)
{
    int i;
    double u;
    
    u = a[n-1];

    for (i = n-2; i >= 0; i--)
        u = u * x + a[i];

    return(u);
}

int main(int argc, char* argv[])
{ 
    int i;
    double a[7] = {-20.0, 7.0, -7.0, 1.0, 3.0, -5.0, 2.0};
    double x[6] = {0.9, -0.9, 1.1, -1.1, 1.3, -1.3};
    
    printf("\n");
    for (i = 0; i <= 5; i++)
      printf("x(%d)=%5.2lf   p(%d)=%13.7e\n",
             i, x[i], i, plyv(a, 7, x[i]));
             
    printf("\n");
    
    return 0;
}