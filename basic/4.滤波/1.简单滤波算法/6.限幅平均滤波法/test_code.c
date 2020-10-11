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
#define THRESHOLD  10

int value_buf[N];
int value_sn = 0;
int value_average = 0;

int filter(void) 
{  
    int count;
    int sum = 0;
    int value;
    
    value = get_ad();
    
    if ((value - value_buf[value_sn] > THRESHOLD) || (value_buf[value_sn] - value > THRESHOLD))
        return value_average;
    
    value_buf[value_sn++] = value;

    if (value_sn == N)
        value_sn = 0;
    
    for(count = 0; count < N; count++)
        sum += value_buf[count];
    
    value_average = sum/N;
    
    return value_average;
}

void value_buf_init(void)
{
    int count;
    int sum = 0;
    
    for(count = 0; count < N; count++)
        value_buf[count] = get_ad();
    
    for(count = 0; count < N; count++)
        sum += value_buf[count];
    
    value_average = sum/N;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));     // 设置随机数种子
    
    value_buf_init();
    
    while(1)
    {
        printf("val %d \r\n", filter());
        sleep(1);
    }
    return 0;
}