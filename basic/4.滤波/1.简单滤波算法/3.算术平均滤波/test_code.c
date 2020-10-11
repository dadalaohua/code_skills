#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/****************************/
/*     rand_50_60()函数     */
/*    返回50～60的随机函数  */
/****************************/
int rand_50_60(void)
{
    return rand()%11 + 50;
}

/****************************/
/*     rand_0_100()函数         */
/*返回0～100的随机函数      */
/****************************/
int rand_0_100(void)
{
    return rand()%101;
}

/****************************/
/*     rand_1_10()函数     */
/*    返回1～10的随机函数  */
/****************************/
int rand_1_10(void)
{
    return rand()%10 + 1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int get_ad(void)
{
    int rnd;
    
    rnd = rand_1_10();
    
    if(rnd == 10)
    {
        rnd = rand_0_100();
    }
    else
    {
        rnd = rand_50_60();
    }
    
    return rnd;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define N 12

int filter(void)
{  
    int sum = 0;
    int count = 0;
    
    for(count = 0; count < N; count++ )
    {
        sum += get_ad();
        //delay();
    }
    
    return (sum/N);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));     // 设置随机数种子
    
    while(1)
    {
        printf("val %d \r\n", filter());
        sleep(1);
    }
    return 0;
}