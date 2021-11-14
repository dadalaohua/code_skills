#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//ns延时
void sleep_nsec(int nsec)
{
    struct timespec req;
    
    req.tv_sec  = nsec / 1000000000;
    req.tv_nsec = nsec % 1000000000;

    pselect(0, NULL, NULL, NULL, &req, NULL);
}

//us延时
void sleep_usec(int usec)
{
    struct timespec req;
    
    req.tv_sec  = usec / 1000000;
    req.tv_nsec = (usec % 1000000) * 1000;

    pselect(0, NULL, NULL, NULL, &req, NULL);
}

//ms延时
void sleep_msec(int msec)
{
    struct timespec req;
    
    req.tv_sec  = msec / 1000;
    req.tv_nsec = (msec % 1000) * 1000000;

    pselect(0, NULL, NULL, NULL, &req, NULL);
}

//s延时
void sleep_sec(int sec)
{
    struct timespec req;
    
    req.tv_sec  = sec;
    req.tv_nsec = 0;

    pselect(0, NULL, NULL, NULL, &req, NULL);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    struct timeval tv_begin,tv_end;
    
    gettimeofday(&tv_begin,NULL);
    
    sleep_nsec(5000);    //延时5000ns

    gettimeofday(&tv_end,NULL);

    printf("run_time:%lds %ldus\n", (tv_end.tv_sec - tv_begin.tv_sec), (tv_end.tv_usec - tv_begin.tv_usec));
    
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