#include <stdio.h>
#include <stdlib.h>

/*判断n是否是素数，是则返回1，不是则返回0*/
int isPrime(int n)
{
    int i;
    
    if(n < 2)
        return 0;
    
    for(i = 2; i < n; i++)
    {
        if(n % i == 0)
            return 0;   /*n可以被i整除，因此n不是素数，返回0*/
    }
    
    return 1;           /*n是素数，返回1*/
}

/*寻找[low,high]之间的素数*/
void getPrime(int low,int high)
{
    int i;
    for(i = low; i <= high; i++)
    {
        if(isPrime(i))
        {
            printf("%d ",i);        /*如果i是素数，则打印出来*/
        }
    }
}

/****************************/

int main(int argc, char* argv[])
{
    int low, high;
    
    printf("Please input the domain for searching prime\n");
    printf("low limitation:");
    scanf("%d",&low);
    printf("high limitation:");
    scanf("%d",&high);
    printf("The whole primes in this domain are\n");
    getPrime(low,high);
    
    printf("\n");
    
    return 0;
}
