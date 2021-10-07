#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 100
// 全局变量
int number = 0;

// 创建一把自旋锁
// 全局变量, 多个线程共享
pthread_spinlock_t spin;

// 线程处理函数
void* test_A_thread(void* arg)
{
    int i, cur;
    
    for(i = 0; i < MAX; i++)
    {
        // 如果线程A加锁成功, 不阻塞
        // 如果B加锁成功, 线程A进行睡眠
        if(pthread_spin_trylock(&spin)) {
            usleep(3);
            continue;
        }
        number++;
        cur = number;
        pthread_spin_unlock(&spin);
        printf("Thread A, id = %lu, number = %d\n", pthread_self(), cur);
        usleep(5);
    }

    return NULL;
}

void* test_B_thread(void* arg)
{
    int i, cur;
    
    for(i = 0; i < MAX; i++)
    {
        // A加锁成功, B线程访问这把锁的时候是锁定的
        // 线程B先阻塞, B线程解锁之后阻塞解除
        // 线程B加锁成功了
        pthread_spin_lock(&spin);
        number++;
        cur = number;
        pthread_spin_unlock(&spin);
        printf("Thread B, id = %lu, number = %d\n", pthread_self(), cur);
        usleep(5);
    }

    return NULL;
}
  
int main(int argc, char* argv[])
{  
    pthread_t p1, p2;

    // 初始化自旋锁
    pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);

    // 创建两个子线程
    pthread_create(&p1, NULL, test_A_thread, NULL);
    pthread_create(&p2, NULL, test_B_thread, NULL);

    // 阻塞，资源回收
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    // 销毁自旋锁
    // 线程销毁之后, 再去释放自旋锁
    pthread_spin_destroy(&spin);

    return 0;  
}
