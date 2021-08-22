#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include "test_task.h"

#include "timeslice.h"
unsigned int temp_cnt = 0;
//1ms中断
void sigroutine(int signo)
{
   switch (signo){
       case SIGALRM:
           
           timeslice_tick();   //invoke this function per 1ms
           
           temp_cnt++;
           if(temp_cnt >= 1000)
           {
               printf("temp_cnt %d\n", temp_cnt);
               temp_cnt = 0;
           }
           
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
   
    // InitialTaskManager();
    test_task_1_init();
    test_task_2_init();

    for(;;){
        timeslice_exec();
    }

    return 0;
}