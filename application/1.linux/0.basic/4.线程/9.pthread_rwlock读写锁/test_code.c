#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define MAX 100
#define WT_NUM 3
#define RT_NUM 5

// 全局变量
int number = 0;

// 定义读写锁
pthread_rwlock_t rwlock;

// 写的线程的处理函数
void* writeNum(void* arg)
{
    int cur;
    
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);
        number ++;
        cur = number;
        pthread_rwlock_unlock(&rwlock);
        printf("++写操作完毕, number : %d, tid = %lu\n", cur, pthread_self());
        
        // 添加sleep目的是要看到多个线程交替工作
        usleep(rand() % 100);
        
        if(cur > MAX)
            break;
    }
    
    return NULL;
}

// 读线程的处理函数
// 多个线程可以如果处理动作相同, 可以使用相同的处理函数
// 每个线程中的栈资源是独享
void* readNum(void* arg)
{
    int cur;
    
    while(1)
    {
        pthread_rwlock_rdlock(&rwlock);
        cur = number;
        printf("--全局变量number = %d, tid = %lu\n", cur, pthread_self());
        pthread_rwlock_unlock(&rwlock);
        
        usleep(rand() % 100);
        
        if(cur > MAX)
            break;
    }
    
    return NULL;
}

int main()
{
    // 3个写线程, 5个读的线程
    pthread_t wtid[WT_NUM];
    pthread_t rtid[RT_NUM];
    
    // 初始化读写锁
    pthread_rwlock_init(&rwlock, NULL);
    
    for(int i = 0; i < WT_NUM; ++i)
    {
        pthread_create(&wtid[i], NULL, writeNum, NULL);
    }

    for(int i = 0; i < RT_NUM; ++i)
    {
        pthread_create(&rtid[i], NULL, readNum, NULL);
    }

    // 释放资源
    for(int i = 0; i < WT_NUM; ++i)
    {
        pthread_join(wtid[i], NULL);
    }

    for(int i = 0; i < RT_NUM; ++i)
    {
        pthread_join(rtid[i], NULL);
    }

    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    

    return 0;
}
