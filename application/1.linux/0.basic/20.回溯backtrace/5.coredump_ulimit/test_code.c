#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <execinfo.h>
#include <sys/resource.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CORE_SIZE   (1024 * 1024)//bytes
int coredump_ulimit(void)
{
    struct rlimit rlmt;
    if (getrlimit(RLIMIT_CORE, &rlmt) == -1) {
        return -1; 
    }   
    printf("Before set rlimit CORE dump current is:%d, max is:%d\n", (int)rlmt.rlim_cur, (int)rlmt.rlim_max);

    rlmt.rlim_cur = (rlim_t)CORE_SIZE;
    rlmt.rlim_max = (rlim_t)CORE_SIZE;

    // rlmt.rlim_cur = RLIM_INFINITY; //软限制，表示对资源没有限制
    // rlmt.rlim_max = RLIM_INFINITY; //硬限制，这个参数表示对资源没有限制，一定要大于等于rlim_cur值

    if (setrlimit(RLIMIT_CORE, &rlmt) == -1) {
        return -1; 
    }   

    if (getrlimit(RLIMIT_CORE, &rlmt) == -1) {
        return -1; 
    }   
    printf("After set rlimit CORE dump current is:%d, max is:%d\n", (int)rlmt.rlim_cur, (int)rlmt.rlim_max);

    // /*测试非法内存，产生core文件*/
    // int *ptr = NULL;
    // *ptr = 10; 

    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void test3(int n)
{
    char *str;
    printf("in test3 [%d]\n", n);
    strcpy(str, "123");
}

void test2(int n)
{
    printf("in test2 [%d]\n", n);
    test3(3);
}

void test1(int n)
{
    printf("in test1 [%d]\n", n);
    test2(2);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    coredump_ulimit();
    
    test1(1);
    
    // int val = 666;
    // char buf[100];
    // while(1) {
        // for(int i = 1; i < 10000; i++) {
            // buf[i] = buf[i - 1] + val;
        // }
        // break;
    // }
    // printf("buf %d\n", buf[0]);

    while(1) {
        sleep(1);
    }
    
    return 0;
}