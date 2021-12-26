#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>

#include "multi_button.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
volatile int button_level = 1;
/************************************************************************/
/*                                                                      */
/************************************************************************/
//5ms中断
void sigroutine(int signo)
{
   switch (signo){
       case SIGALRM:
           
           button_ticks();
           
           signal(SIGALRM, sigroutine);
           break;
   }
   return;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void set_button_level(unsigned char level)
{
    button_level = level;
}

unsigned char get_button_level(void)
{
    return button_level;
}

unsigned char read_button1_GPIO(void) 
{
    return get_button_level();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void thread(void* argc)  
{
    int level = button_level;
    while(1) {
        getchar();
        level = !level;
        set_button_level(level);
    }
} 

int main(int argc, char* argv[])
{
    struct itimerval value, ovalue;

    printf("process id is %d\n", getpid());

    signal(SIGALRM, sigroutine);

    //每隔5ms发出一个SIGALRM
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 5000;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 5000;
    setitimer(ITIMER_REAL, &value, &ovalue);
    
    pthread_t id; 

    pthread_create(&id, NULL, (void  *)thread, NULL);  
   
    ////////////////////////////

    struct Button btn1;
    static unsigned char btn1_event_val;
    
    button_init(&btn1, read_button1_GPIO, 0);
    button_start(&btn1);
    
    for(;;)
    {
        if(btn1_event_val != get_button_event(&btn1)) {
            btn1_event_val = get_button_event(&btn1);
            
            if(btn1_event_val == PRESS_DOWN) {
                //do something
                printf("PRESS_DOWN\n");
            } else if(btn1_event_val == PRESS_UP) {
                //do something
                printf("PRESS_UP\n");
            } else if(btn1_event_val == PRESS_REPEAT) {
                //do something
                printf("PRESS_REPEAT\n");
            } else if(btn1_event_val == SINGLE_CLICK) {
                //do something
                printf("SINGLE_CLICK\n");
            } else if(btn1_event_val == DOUBLE_CLICK) {
                //do something
                printf("DOUBLE_CLICK\n");
            } else if(btn1_event_val == LONG_PRESS_START) {
                //do something
                printf("LONG_PRESS_START\n");
            } else if(btn1_event_val == LONG_PRESS_HOLD) {
                //do something
                printf("LONG_PRESS_HOLD\n");
            }
        }
        usleep(10000);
    }

    return 0;
}