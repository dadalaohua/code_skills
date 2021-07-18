#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include "tinyOS.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*      信号量传递       */
SEM test_sem;

volatile unsigned char timers[MAXTASKS];

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*task1任务，1000ms一次*/

unsigned char task1()
{
_SS
    while(1)
    {
        printf("test_task_1_poll\n");
        SendSem(test_sem);
        WaitX(250);
        WaitX(250);
        WaitX(250);
        WaitX(250);
    }
_EE
}


unsigned char task2()
{
_SS
    while(1)
    {
        WaitSem(test_sem);        
        printf("WaitSem test_task_2\n");       
    }
_EE
}

unsigned char task3()
{
_SS
    while(1)
    {
        printf("test_task_3_poll\n");
        WaitX(250);      
        WaitX(250);
    }
_EE
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//1ms中断
void sigroutine(int signo)
{
   switch (signo){
       case SIGALRM:
           
           UpdateTimers();   //invoke this function per 1ms
           
           signal(SIGALRM, sigroutine);
           break;
   }
   return;
}

int main(int argc, char* argv[])
{
    struct itimerval value, ovalue;

    printf("process id is %d\n", getpid());

    signal(SIGALRM, sigroutine);

    //每隔1ms发出一个SIGALRM
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 1000;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 1000;
    setitimer(ITIMER_REAL, &value, &ovalue);
   
    /*tinyOS start here */
    InitTasks();        //初始化任务，实际上是给timers清零
    InitSem(test_sem);//初始化信号量

    for(;;)
    {
        RunTaskA(task1, 1);
        RunTaskA(task2, 2);
        RunTaskA(task3, 3);
    }

    return 0;
}