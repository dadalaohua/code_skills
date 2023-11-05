#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/syscall.h>

/*
Linux：获取线程的PID（TID、LWP）的几种方式
https://blog.csdn.net/test1280/article/details/87974748

可以通过
top -Hp %pid
来查看线程信息
例如:
top -Hp 30380
*/

pid_t gettid(void) {
    return syscall(SYS_gettid);
}

void *func1()/*1秒钟之后退出*/
{
    printf("%s: %lu %ld\n", __func__, pthread_self(), syscall(SYS_gettid));
    
    while(1)
        sleep(1);
    
    printf("线程1（ID：0x%x）退出\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

void *func2()/*5秒钟之后退出*/
{
    printf("%s: %lu %ld\n", __func__, pthread_self(), syscall(SYS_gettid));
    
    while(1)
        sleep(5);
    
    printf("线程2（ID：0x%x）退出\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

int main(int argc, char* argv[])
{
    printf("%s: %lu %ld\n", __func__, pthread_self(), syscall(SYS_gettid));

    int ret;
    pthread_t tid1,tid2;

    pthread_create(&tid1,NULL,func1,NULL);
    pthread_create(&tid2,NULL,func2,NULL);
    
    while(1)
        sleep(3);
    
    exit(0);
    
    return 0;
}