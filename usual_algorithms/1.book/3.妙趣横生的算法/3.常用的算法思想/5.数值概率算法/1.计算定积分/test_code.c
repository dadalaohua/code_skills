#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/****************************/
double Darts(int n)
{
    double x,y;
    time_t t;
    int i,count = 0;
    srand((unsigned)time(&t));
    for(i=0;i<n;i++)
    {
        x = rand()%100/100.0;
        y = rand()%100/100.0;
        if(y<=1 - pow(x,2))
            count++;
    }
    return (double)count/(double)n;     /*返回落入阴影区域的点数与总点数n的比值*/
}

/****************************/

int main(int argc, char* argv[])
{
    int n;
    printf("Please input the accuracy\n") ;     /*输入精度，即投点数*/
    scanf("%d",&n);
    printf("The result is about\n");            /*输出计算结果*/
    printf("%f\n",Darts(n));
    
    printf("\n");
    
    return 0;
}
