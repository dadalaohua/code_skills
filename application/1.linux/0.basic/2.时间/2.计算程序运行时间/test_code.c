#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void hello_world(void)
{
    printf("Hello world!!!!\r\n");
}

int main(int argc, char* argv[])
{
    struct  timeval tv_begin,tv_end;
    
    gettimeofday(&tv_begin,NULL);
    
    hello_world();

    gettimeofday(&tv_end,NULL);

    printf("tv_begin_sec:%ld\n", tv_begin.tv_sec);
    printf("tv_begin_usec:%ld\n", tv_begin.tv_usec);

    printf("tv_end_sec:%ld\n", tv_end.tv_sec);
    printf("tv_end_usec:%ld\n", tv_end.tv_usec);
    
    printf("run_time:%lds %ldus\n", (tv_end.tv_sec - tv_begin.tv_sec - (tv_end.tv_usec < tv_begin.tv_usec ? 1 : 0)), (tv_end.tv_usec - tv_begin.tv_usec + (tv_end.tv_usec < tv_begin.tv_usec ? 1000000 : 0)));

    return 0;
}