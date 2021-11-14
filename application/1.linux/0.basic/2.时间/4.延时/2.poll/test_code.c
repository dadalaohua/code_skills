#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <poll.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//ms延时
void sleep_msec(int msec)
{
    poll(NULL, 0, msec);
}
//s延时
void sleep_sec(int sec)
{
    poll(NULL, 0, sec*1000);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    struct timeval tv_begin,tv_end;
    
    gettimeofday(&tv_begin,NULL);
    
    sleep_msec(100);    //延时100ms

    gettimeofday(&tv_end,NULL);

    printf("run_time:%lds %ldus\n", (tv_end.tv_sec - tv_begin.tv_sec), (tv_end.tv_usec - tv_begin.tv_usec));

    gettimeofday(&tv_begin,NULL);

    sleep_sec(2);    //延时2s

    gettimeofday(&tv_end,NULL);

    printf("run_time:%lds %ldus\n", (tv_end.tv_sec - tv_begin.tv_sec), (tv_end.tv_usec - tv_begin.tv_usec));
    
    return 0;
}