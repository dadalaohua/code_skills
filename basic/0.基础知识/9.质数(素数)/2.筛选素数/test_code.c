#include <stdio.h>
#include <string.h>
#include <math.h>

#define PRIMES_RANGE_MAX 1000

typedef enum bool{false, true} bool;

//筛除标记
bool sieve_number[PRIMES_RANGE_MAX];
//存放素数
bool primes[PRIMES_RANGE_MAX];

//埃拉托斯特尼筛法
bool eratosthenes(unsigned int num)
{
    unsigned int i;
    unsigned int sqr;
    unsigned long long j;

    memset(sieve_number, true, sizeof(sieve_number));
    
    sieve_number[0] = false;
    sieve_number[1] = false;     //0和1都不是素数
    
    sqr = (unsigned int)sqrt((double)num);

    for(i = 2; i < sqr; i++)
    {
        if(sieve_number[i])
        {
            for(j = i * i; j < num; j += i) //j从i²开始判断更高效，因为之前2*i，3*i等等已经被筛除了，j要用long long型来防止溢出
            {
                sieve_number[j] = false;
            }
        }
    }
    
    printf("埃拉托斯特尼筛法 一百以内的所有质数：\n");
    for(i = 0;i < num; i++)
    {
        if(sieve_number[i])
        {
            printf("%d ", i);
        }
    }
    printf("\n");

    return true;
}

//欧拉筛法
bool euler(unsigned int num)
{
    unsigned int i;
    unsigned int sqr;
    unsigned long long j;
    unsigned int cnt = 0; //记录已知素数数量

    memset(primes, true, sizeof(primes));
    
    sieve_number[0] = false;
    sieve_number[1] = false;     //0和1都不是素数
    
    for(i = 2; i < num; i++)
    {
        if(sieve_number[i])
        {
            primes[cnt] = i;
            cnt++;
        }

        for(j = 0; (j < cnt) && (i * primes[j] <= num); j++)
        {
            sieve_number[i * primes[j]] = false; //筛除
            
            if(i % primes[j] == 0) //关键代码
                break;
        }
    }
    
    printf("欧拉筛法一百以内的所有质数：\n");
    for(i = 0;i < cnt; i++)
    {
        printf("%d ", primes[i]);
    }
    printf("\n");

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
    eratosthenes(100);
    
    printf("方法二：\n");
    euler(100);
    
    return 0;
}