#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//诊断-忽略:(关闭警告)
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wreturn-type"

static int test1(void)
{
    return;
}

//诊断-警告:(开启警告)
#pragma GCC diagnostic warning "-Wreturn-type"

static int test2(void)
{
    return;
}
//诊断-错误:(开启警告-升级为错误)
#pragma GCC diagnostic error "-Wreturn-type"

static int test3(void)
{
    return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    printf("hello world\n");
    
    return 0;
}