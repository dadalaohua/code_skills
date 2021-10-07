#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 100
#define PNUM 5
#define CNUM 5

// 链表的节点
struct Node
{
    int number;
    struct Node* next;
};

// 生产者线程信号量
sem_t psem;
// 消费者线程信号量
sem_t csem;

// 互斥锁变量
pthread_mutex_t mutex;
// 指向头结点的指针
struct Node * head = NULL;

int number = 0;
int end_flag = 0;

// 生产者的回调函数
void* producer(void* arg)
{
    // 一直生产
    while(1)
    {
        // 生产者拿一个信号灯
        sem_wait(&psem);
        // 创建一个链表的新节点
        struct Node* pnew = (struct Node*)malloc(sizeof(struct Node));
        // 节点初始化
        number++;
        pnew->number = number;
        // 节点的连接, 添加到链表的头部, 新节点就新的头结点
        pnew->next = head;
        // head指针前移
        head = pnew;
        printf("+++producer, number = %d, tid = %lu\n", pnew->number, pthread_self());
        
        // 通知消费者消费, 给消费者加信号灯
        sem_post(&csem);
        

        // 生产慢一点
        sleep(rand() % 3);
        
        if(number > MAX) {
            end_flag = 1;
            sem_post(&csem);
            break;
        }
    }
    printf("producer\n");
    return NULL;
}

// 消费者的回调函数
void* consumer(void* arg)
{
    while(1)
    {
        sem_wait(&csem);
        
        if(end_flag) {
            break;
        }
        
        // 取出链表的头结点, 将其删除
        struct Node* pnode = head;
        printf("--consumer: number: %d, tid = %lu\n", pnode->number, pthread_self());
        head  = pnode->next;
        free(pnode);
        // 通知生产者生成, 给生产者加信号灯
        sem_post(&psem);

        sleep(rand() % 3);
        
        if(end_flag) {
            break;
        }
    }
    printf("consumer\n");
    return NULL;
}

int main(int argc, char* argv[])
{
    // 初始化信号量
    // 生产者和消费者拥有的信号灯的总和为1
    sem_init(&psem, 0, 1);  // 生成者线程一共有1个信号灯
    sem_init(&csem, 0, 0);  // 消费者线程一共有0个信号灯

    // 创建5个生产者, 5个消费者
    pthread_t ptid[PNUM];
    pthread_t ctid[CNUM];
    for(int i = 0; i < PNUM; ++i)
    {
        pthread_create(&ptid[i], NULL, producer, NULL);
    }

    for(int i = 0; i < CNUM; ++i)
    {
        pthread_create(&ctid[i], NULL, consumer, NULL);
    }

    // 释放资源
    for(int i = 0; i < PNUM; ++i)
    {
        pthread_join(ptid[i], NULL);
    }

    for(int i = 0; i < CNUM; ++i)
    {
        pthread_join(ctid[i], NULL);
    }
    
    //销毁所有申请的内存
    while(head != NULL)
    {
        struct Node* pnode = head;
        head  = pnode->next;
        free(pnode);
    }

    sem_destroy(&psem);
    sem_destroy(&csem);   

    return 0;
}
