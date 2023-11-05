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

ps查看线程所在的cpu + pstack 线程+ strace 线程
https://www.cnblogs.com/dream397/p/13572589.html
*/

pid_t gettid(void) {
    return syscall(SYS_gettid);
}

int check_ps(pid_t pid)
{
    FILE* fp;
    int count = 0;
    char buf[512];
    char command[150];

    int rpid, lwp, psr;
    float cpu, mem;
    char stat[16];
    char time[16];
    char abandon[16];
    sprintf(command, "ps -mo pid,lwp,%%cpu,%%mem,psr,stat,time -p %d", pid);
    if((fp = popen(command,"r")) == NULL) {
        return 0;
    }
    
    fgets(buf, sizeof(buf), fp);
    printf("%s", buf);
    printf("\n");
    
    fgets(buf, sizeof(buf), fp);
    printf("%s", buf);
    sscanf(buf, "%d %s %f %f %s %s %s", &rpid, abandon, &cpu, &mem, abandon, abandon, time);
    printf("%d %s %f %f %s %s %s\n", rpid, abandon, cpu, mem, abandon, abandon, time);
    printf("\n");
    
    while( (fgets(buf, sizeof(buf), fp))!= NULL ) {
        printf("%s", buf);
        sscanf(buf, "%s %d %f %s %d %s %s", abandon, &lwp, &cpu, abandon, &psr, stat, time);
        printf("%s %d %f %s %d %s %s\n", abandon, lwp, cpu, abandon, psr, stat, time);
        printf("\n");
    }
    
    pclose(fp);
    
    return count;
}

void *func1(void)
{
    printf("%s: %lu %ld\n", __func__, pthread_self(), syscall(SYS_gettid));
    
    while(1)
        sleep(1);
    
    printf("线程1（ID：0x%x）退出\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

void *func2(void)/*5秒钟之后退出*/
{
    printf("%s: %lu %ld\n", __func__, pthread_self(), syscall(SYS_gettid));
    
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
    
    check_ps(syscall(SYS_gettid));
    
    while(1) {
        sleep(3);
        check_ps(syscall(SYS_gettid));
    }
    printf("end!!!!!!!!!\n");
    exit(0);
    
    return 0;
}