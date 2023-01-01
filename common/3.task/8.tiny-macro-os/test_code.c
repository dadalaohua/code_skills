#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include "tiny-macro-os.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
volatile int tick;
volatile int systime = 0;
/************************************************************************/
/*                                                                      */
/************************************************************************/
//1ms中断
void sigroutine(int signo)
{
   switch (signo){
       case SIGALRM:
           
           tick = 1;   //invoke this function per 1ms
           systime++;
           
           signal(SIGALRM, sigroutine);
           
           OS_UPDATE_TIMERS();
           break;
   }
   return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*void参数表示函数无参数，可以不写该void，但是定义不标准，所以写上void最好 */
OS_TASK(os_test1, void)
{
    OS_TASK_START(os_test1);
    /* 禁止在OS_TASK_START和OS_TASK_END之间使用switch */
    while (1)
    {
        printf("os_test1\n");
        OS_TASK_WAITX(OS_SEC_TICKS * 6 / 10);
    }
    OS_TASK_END(os_test1);
}

/* 带参数任务编写格式函数参数直接作为宏定义中的成员写进去即可 */
OS_TASK(os_test2, unsigned char params, ...)
{
    OS_TASK_START(os_test2);
    /* 禁止在OS_TASK_START和OS_TASK_END之间使用switch */
    while (1)
    {
        printf("os_test2:%d\n", params);
        OS_TASK_WAITX(OS_SEC_TICKS * 6 / 10);
    }
    OS_TASK_END(os_test2);
}

void tmos_test_main(void)
{
    OS_INIT_TASKS();
    unsigned char i = 0;
    while (1)
    {
        /* 所有的主任务都需要手动在main函数的while(1)中调用 */
        OS_RUN_TASK(os_test1);
        OS_RUN_TASK(os_test2, i++);
    }
}

int main(int argc, char* argv[])
{
    struct itimerval value, ovalue;

    signal(SIGALRM, sigroutine);

    //每隔1ms发出一个SIGALRM
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 1000;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 1000;
    setitimer(ITIMER_REAL, &value, &ovalue);
    
    tmos_test_main();
    
    return 0;
}