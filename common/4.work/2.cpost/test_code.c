#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include "cpost.h"

unsigned int system_cnt = 0;

void test_task_handle(void);
void test_task_delay_handle(void);

//1ms中断
void sigroutine(int signo)
{
    switch (signo){
        case SIGALRM:
        
            signal(SIGALRM, sigroutine);
           
            system_cnt++;
           
            if(system_cnt%1000 == 0)
            {
                cpost(test_task_handle);
               
                cpostDelay(test_task_delay_handle, 500);
               
                if(system_cnt > 10000)
                    cpostRemove(test_task_handle);
            }
           
            
            break;
    }
    return;
}

unsigned int test_system_get_tick(void)
{
    return system_cnt;
}

void test_task_handle(void)
{
    static unsigned int temp_cnt = 0;
    
    printf("test_task_handle %d\n", temp_cnt++);
}

void test_task_delay_handle(void)
{
    static unsigned int temp_cnt = 0;
    
    printf("test_task_delay_handle %d\n", temp_cnt++);
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
   
    for(;;){
        cpostProcess();
    }

    return 0;
}