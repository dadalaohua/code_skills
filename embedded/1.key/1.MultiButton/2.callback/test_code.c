#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

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
    
}

void BTN1_PRESS_DOWN_Handler(void* btn)
{
    //do something...
    printf("PRESS_DOWN\n");
}

void BTN1_PRESS_UP_Handler(void* btn)
{
    //do something...
    printf("PRESS_UP\n");
}

void BTN1_PRESS_REPEAT_Handler(void* btn)
{
    //do something...
    printf("PRESS_REPEAT %d\n", ((struct Button *)btn)->repeat);
}

void BTN1_SINGLE_Click_Handler(void* btn)
{
    //do something...
    printf("SINGLE_CLICK\n");
}

void BTN1_DOUBLE_Click_Handler(void* btn)
{
    //do something...
    printf("DOUBLE_CLICK\n");
}

void BTN1_LONG_PRESS_START_Handler(void* btn)
{
    //do something...
    printf("LONG_PRESS_START\n");
}

void BTN1_LONG_PRESS_HOLD_Handler(void* btn)
{
    //do something...
    printf("LONG_PRESS_HOLD\n");
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
    
    ////////////////////////////
    int level = button_level;
    //先申请一个按键结构
    struct Button btn1;
    //初始化按键对象，绑定按键的GPIO电平读取接口**read_button_pin()** ，后一个参数设置有效触发电平
    button_init(&btn1, read_button1_GPIO, 0);
    //注册按键事件
    button_attach(&btn1, PRESS_DOWN,       BTN1_PRESS_DOWN_Handler);
    button_attach(&btn1, PRESS_UP,         BTN1_PRESS_UP_Handler);
    button_attach(&btn1, PRESS_REPEAT,     BTN1_PRESS_REPEAT_Handler);
    button_attach(&btn1, SINGLE_CLICK,     BTN1_SINGLE_Click_Handler);
    button_attach(&btn1, DOUBLE_CLICK,     BTN1_DOUBLE_Click_Handler);
    button_attach(&btn1, LONG_PRESS_START, BTN1_LONG_PRESS_START_Handler);
    button_attach(&btn1, LONG_PRESS_HOLD,  BTN1_LONG_PRESS_HOLD_Handler);
    //启动按键
    button_start(&btn1);
    
    for(;;)
    {
        getchar();
        level = !level;
        set_button_level(level);
    }

    return 0;
}