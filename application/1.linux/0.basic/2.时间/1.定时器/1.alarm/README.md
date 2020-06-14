1、alarm 
　　如果不要求很精确的话，用 alarm() 和 signal() 就够了



unsigned int alarm(unsigned int seconds)
        专门为SIGALRM信号而设，在指定的时间seconds秒后，将向进程本身发送SIGALRM信号，又称为闹钟时间。进程调用alarm后，任何以前的alarm()调用都将无效。如果参数seconds为零，那么进程内将不再包含任何闹钟时间。如果调用alarm（）前，进程中已经设置了闹钟时间，则返回上一个闹钟时间的剩余时间，否则返回0。 

示例：
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
​
void sigalrm_fn(int sig)
{
    printf("alarm!\n");
    alarm(2);
    return;
}
​
int main(void)
{
    signal(SIGALRM, sigalrm_fn);
    alarm(2);
​
    while(1) pause();
}