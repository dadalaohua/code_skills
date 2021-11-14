#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//us延时
void sleep_usec(int usec)
{
    usleep(usec);
}
//ms延时
void sleep_msec(int msec)
{
    usleep(msec * 1000);
}
//s延时
void sleep_sec(int sec)
{
    usleep(sec * 1000000);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    struct timeval tv_begin,tv_end;
    
    gettimeofday(&tv_begin,NULL);
    
    sleep_usec(5000);    //延时5000us

    gettimeofday(&tv_end,NULL);

    printf("run_time:%lds %ldus\n", (tv_end.tv_sec - tv_begin.tv_sec), (tv_end.tv_usec - tv_begin.tv_usec));
    
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