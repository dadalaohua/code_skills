#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

/*
Linux多线程编程时如何查看一个进程中的某个线程是否存活
https://blog.csdn.net/weiyuefei/article/details/54092268

这篇文章使用的方式不可靠，pthread_t值在内部使用时很可能转换为指针使用，
如果其值作为地址的内存区域被释放了很可能导致这个pthread_kill的crash
（即使外部对pthread_t这个值的保存的内存区域未被释放），
且代码流程上存在对一个pthread_t调用pthread_try_join后
又对其调用pthread_kill的情况，
同时内存被释放了如果没有被立即占用就可能还可以使用，
这也就导致不是每次必现的crash

详细见下文

pthread_kill引发的争论
https://www.jianshu.com/p/756240e837dd
*/
void *func1()/*1秒钟之后退出*/
{
    sleep(1);
    
    printf("线程1（ID：0x%x）退出。\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

void *func2()/*5秒钟之后退出*/
{
    sleep(5);
    printf("线程2（ID：0x%x）退出。\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

void test_pthread(pthread_t tid) /*pthread_kill的返回值：成功（0） 线程不存在（ESRCH） 信号不合法（EINVAL）*/
{
    int pthread_kill_err;
    pthread_kill_err = pthread_kill(tid, 0);

    if(pthread_kill_err == ESRCH)
        printf("ID为0x%x的线程不存在或者已经退出。\n",(unsigned int)tid);
    else if(pthread_kill_err == EINVAL)
        printf("发送信号非法。\n");
    else
        printf("ID为0x%x的线程目前仍然存活。\n",(unsigned int)tid);
}

int main(int argc, char* argv[])
{
    int ret;
    pthread_t tid1,tid2;

    pthread_create(&tid1,NULL,func1,NULL);
    pthread_create(&tid2,NULL,func2,NULL);

    test_pthread(tid1);/*测试ID为tid1的线程是否存在*/
    test_pthread(tid2);/*测试ID为tid2的线程是否存在*/
    // test_pthread(132);/*不存在的id会导致段错误，Segmentation fault (core dumped)*/
    
    sleep(3);/*创建两个进程3秒钟之后，分别测试一下它们是否还活着*/

    test_pthread(tid1);/*测试ID为tid1的线程是否存在*/
    test_pthread(tid2);/*测试ID为tid2的线程是否存在*/
    
    sleep(3);
    
    test_pthread(tid1);/*测试ID为tid1的线程是否存在*/
    test_pthread(tid2);/*测试ID为tid2的线程是否存在*/

    exit(0);
    
    return 0;
}