#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void handle(union sigval v)
{
    time_t t;
    char p[32];
    
    time(&t);
    strftime(p, sizeof(p), "%T", localtime(&t));
    printf("%s thread %lu, val = %d, signal captured.\n", p, pthread_self(), v.sival_int);
    return;
}

int main(int argc, char* argv[])
{
    struct sigevent evp;
    struct itimerspec ts;
    timer_t timer;
    int ret;
    
    memset(&evp, 0, sizeof(evp));
    
    evp.sigev_value.sival_ptr = &timer;
    evp.sigev_notify          = SIGEV_THREAD;   //线程通知的方式，派驻新线程  
    evp.sigev_notify_function = handle;         //线程函数地址 
    evp.sigev_value.sival_int = 3;              //作为handle()的参数
    
    ret = timer_create(CLOCK_REALTIME, &evp, &timer);
    if(ret)
        perror("timer_create");
    
    ts.it_interval.tv_sec   = 1;    // 后续按照该时间间隔 
    ts.it_interval.tv_nsec  = 0;
    ts.it_value.tv_sec      = 3;    // 最初开始时间间隔 
    ts.it_value.tv_nsec     = 0;
    ret = timer_settime(timer, TIMER_ABSTIME, &ts, NULL);
    if(ret)
        perror("timer_settime");
    
    for(;;);
    
    return 0;
}