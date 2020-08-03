#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

/****************************/
/*     rand01()函数         */
/*返回0、1的随机函数        */
/****************************/
int rand_0_1(void)
{
    return rand()%2;
}

int rand_01(void)
{
    int rnd ;

    /*去除随机数的最大值*/
    while((rnd = rand()) == RAND_MAX) ;
    /*随机数的计算*/ 
    return (int)((double)rnd/RAND_MAX*2) ;
}

/****************************/
/*     rand01()函数         */
/*返回0～100的随机函数      */
/****************************/
int rand_0_100(void)
{
    return rand()%101;
}

int rand100(void)
{
    int rnd ;

    /*去除随机数的最大值*/
    while((rnd=rand())==RAND_MAX) ;
    /*随机数的计算*/ 
    return (int)((double)rnd/RAND_MAX*101) ;
}

/****************************/
/*     rand01()函数         */
/*返回1～10的随机函数       */
/****************************/
int rand_1_10(void)
{
    return rand()%10 + 1;
}

/****************************/
/*     rand1()函数          */
/*返回0～1的实数的随机函数  */
/****************************/
double rand1(void)
{
    return (double)rand()/RAND_MAX;
}

/****************************/

int main(int argc, char* argv[])
{
    int i = 0;
    
    srand((unsigned)time(NULL));     // 设置随机数种子
    //srand(32767);
    
    printf("RAND_MAX %d 0x%x\n", RAND_MAX, RAND_MAX);
    
    for (i = 0; i < 10; i++)
    {
        printf("%u ", rand());
    }
    printf("\n");
    
    for (i = 0; i < 10; i++)
    {
        printf("%u ", rand_0_1());
    }
    printf("\n");
    
    for (i = 0; i < 10; i++)
    {
        printf("%u ", rand_01());
    }
    printf("\n");
    
    for (i = 0; i < 10; i++)
    {
        printf("%u ", rand_0_100());
    }
    printf("\n");
    
    for (i = 0; i < 10; i++)
    {
        printf("%u ", rand100());
    }
    printf("\n");
    
    for (i = 0; i < 10; i++)
    {
        printf("%u ", rand_1_10());
    }
    printf("\n");
    
    for (i = 0; i < 10; i++)
    {
        printf("%f ", rand1());
    }
    printf("\n");
    
    return 0;
}