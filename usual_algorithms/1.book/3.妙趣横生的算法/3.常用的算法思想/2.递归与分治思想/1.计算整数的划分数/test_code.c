#include <stdio.h>
#include <stdlib.h>

/****************************/
int P(int n,int m)
{
    if(m==1 || n == 1) return 1;
    if(m>n) return P(n,n);
    if(m==n) return 1+P(n,m-1);
    return P(n,m-1)+P(n-m,m);
}

/****************************/

int main(int argc, char* argv[])
{
    int n,s;
    printf("Please input a integer for getting the number of division\n");
    scanf("%d",&n);                 /*输入正整数n*/
    s = P(n,n);                     /*求出正整数n的划分数*/
    printf("The number of division of %d is %d\n",n,s);
    
    printf("\n");
    
    return 0;
}
