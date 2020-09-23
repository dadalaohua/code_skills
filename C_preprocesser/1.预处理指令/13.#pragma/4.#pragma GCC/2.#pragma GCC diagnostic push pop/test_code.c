#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//诊断-忽略:(关闭警告)
#pragma GCC diagnostic ignored "-Wunused-function"

//记录当前的诊断状态
#pragma GCC diagnostic push
//诊断-忽略:(关闭警告)
#pragma GCC diagnostic ignored "-Wreturn-type"

static int test1(void)
{
    return 0;
}

static int test2(void)
{
    return;
}
//恢复到之前的诊断状态
#pragma GCC diagnostic pop

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