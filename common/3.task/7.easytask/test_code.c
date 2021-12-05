#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

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
           break;
   }
   return;
}

int get_time(void)
{
    return systime;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//下面的数值放大了100倍，避免测试程序打印太多log，实际使用应按正常的值
#define INTERVAL_10_MSEC        1000    //这里应该是10
#define INTERVAL_50_MSEC        5000    //这里应该是50
#define INTERVAL_500_MSEC       50000   //这里应该是500

void function_A(void)
{
    printf("function_A\n");
}

void function_B(void)
{
    printf("function_B\n");
}

void function_C(void)
{
    printf("function_C\n");
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

typedef struct
{
   int interval;      
   void (*proc)(void); 
} timer_task;

static const timer_task timer_handler_task[] = 
{
    { INTERVAL_10_MSEC,  function_A }, 
    { INTERVAL_50_MSEC,  function_B }, 
    { INTERVAL_500_MSEC, function_C },
    { 0, NULL }
};

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
   
    ////////////////////////////
    const timer_task *ptr;
    int time;

    for(;;)
    {
        if (tick) 
        {
            tick--;
            time = get_time();
            for (ptr = timer_handler_task; ptr->interval != 0; ptr++)
            {
                if (!(time % ptr->interval))
                    (ptr->proc)(); 
            }
        }
    }

    return 0;
}