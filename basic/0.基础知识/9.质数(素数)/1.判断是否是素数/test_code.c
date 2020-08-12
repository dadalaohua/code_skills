#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum bool{false, true} bool;

//基本实现
bool isPrime(unsigned int num)
{
    unsigned int i;
    
    if(num <= 1)
        return false;

    for(i = 2; i < num; i++)
    {
        if(num % i == 0)
            return false;
    }

    return true;
}

//初步优化
//1.当n是偶数的时候，我们根本不需要循环，除了2以外的偶数一定是合数
//2.环的上界其实也没有必要到n-1，到根号n就可以了。
//  因为因数如果存在一定是成对出现的，如果存在小于根号n的因数，那么n除以它一定大于根号n
//  假如n是合数，必然存在非1的两个约数p1和p2，其中p1<=sqrt(n)，p2>=sqrt(n)
bool isPrime_2(unsigned int num)
{
    unsigned int i;
    unsigned int sqr;
    
    if(num <= 1)
        return false;
    
    if((num % 2 == 0) && (num != 2))
        return false;

    sqr = (unsigned int)sqrt((double)num);
    for(i = 3; i <= sqr; i++)
    {
        if( num % i == 0 )
            return false;
    }

    return true;
}

//数学上有一个定理，只有形如6n-1和6n+1的自然数可能是素数，这里的n是大于等于1的整数。
//这个定理乍一看好像很高级，但其实很简单，
//因为所有自然数都可以写成6n,6n+1,6n+2,6n+3,6n+4,6n+5这6种，
//其中6n,6n+2,6n+4是偶数，一定不是素数。
//6n+3可以写成3(2n+1)，显然也不是素数，所以只有可能6n+1和6n+5可能是素数。
//6n+5等价于6n-1，所以我们一般写成6n-1和6n+1。
bool isPrime_3(unsigned int num)
{
    unsigned int i;
    unsigned int sqr;
    
    if (num <= 3)
        return num > 1;
    
    if ((num % 6 != 1) && (num % 6 != 5))
        return false;

    sqr = (unsigned int)sqrt((double)num);
    for(i = 5; i <= sqr; i += 6)
    {
        if ((num % i == 0) || (num % (i + 2) == 0))
            return false;
    }

    return true;
}

/****************************/

int main(int argc, char* argv[])
{
    unsigned int array[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
                        59, 61, 67, 71, 73, 79, 83, 89, 97};

    unsigned int i;
    
    printf("一百以内的所有质数：\n");
    for(i = 0; i < sizeof(array)/sizeof(array[0]); i++ )
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    printf("方法一：\n");
    for(i = 0; i < 100; i++)
    {
        if(isPrime(i))
            printf("%d ", i);
    }
    printf("\n");
    
    printf("方法二：\n");
    for(i = 0; i < 100; i++)
    {
        if(isPrime_2(i))
            printf("%d ", i);
    }
    printf("\n");
    
    printf("方法三：\n");
    for(i = 0; i < 100; i++)
    {
        if(isPrime_3(i))
            printf("%d ", i);
    }
    printf("\n");
    
    return 0;
}