#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//us延时
void sleep_usec(int usec)
{
    struct timeval tv;
    
    tv.tv_sec = usec / 1000000;
    tv.tv_usec = usec % 1000000;

    select(0, NULL, NULL, NULL, &tv);
}

//ms延时
void sleep_msec(int msec)
{
    struct timeval tv;
    
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;

    select(0, NULL, NULL, NULL, &tv);
}

//s延时
void sleep_sec(int sec)
{
    struct timeval tv;
    
    tv.tv_sec = sec;
    tv.tv_usec = 0;

    select(0, NULL, NULL, NULL, &tv);
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