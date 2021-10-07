#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define MAX 100
#define PNUM 5
#define CNUM 5

// 链表的节点
struct Node
{
    int number;
    struct Node* next;
};

// 定义条件变量, 控制消费者线程
pthread_cond_t cond;
// 互斥锁变量
pthread_mutex_t mutex;
// 指向头结点的指针
struct Node * head = NULL;

int number = 0;
int end_flag = 0;

// 生产者的回调函数
void* producer(void* arg)
{
    int cur_number;
    
    // 一直生产
    while(1)
    {
        pthread_mutex_lock(&mutex);
        // 创建一个链表的新节点
        struct Node* pnew = (struct Node*)malloc(sizeof(struct Node));
        // 节点初始化
        pnew->number = number++;
        // 节点的连接, 添加到链表的头部, 新节点就新的头结点
        pnew->next = head;
        // head指针前移
        head = pnew;
        printf("+++producer, number = %d, tid = %lu\n", pnew->number, pthread_self());
        cur_number = pnew->number;
        pthread_mutex_unlock(&mutex);

        // 生产了任务, 通知消费者消费
        pthread_cond_broadcast(&cond);

        // 生产慢一点
        sleep(rand() % 3);
        
        //生产到指定数量，退出
        if(cur_number > MAX)
        {
            end_flag = 1;
            pthread_cond_signal(&cond);
            break;
        }
    }
    printf("producer end\n");
    
    return NULL;
}

// 消费者的回调函数
void* consumer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        // 一直消费, 删除链表中的一个节点
//        if(head == NULL)   // 这样写有bug
        while(head == NULL)
        {
            // 任务队列, 也就是链表中已经没有节点可以消费了
            // 消费者线程需要阻塞
            // 线程加互斥锁成功, 但是线程阻塞在这行代码上, 锁还没解开
            // 其他线程在访问这把锁的时候也会阻塞, 生产者也会阻塞 ==> 死锁
            // 这函数会自动将线程拥有的锁解开
            pthread_cond_wait(&cond, &mutex);
            // 当消费者线程解除阻塞之后, 会自动将这把锁锁上
            // 这时候当前这个线程又重新拥有了这把互斥锁
            
            //结束
            if(end_flag)
            {
                while(head != NULL)
                {
                    struct Node* pnode = head;
                    head  = pnode->next;
                    free(pnode);
                }
                pthread_mutex_unlock(&mutex); 
                goto end; 
            }
        }

        // 取出链表的头结点, 将其删除
        struct Node* pnode = head;
        printf("--consumer: number: %d, tid = %lu\n", pnode->number, pthread_self());
        head  = pnode->next;
        free(pnode);
        
        pthread_mutex_unlock(&mutex);        

        sleep(rand() % 3);
        
        //结束
        if(end_flag)
        {
            pthread_mutex_lock(&mutex);
            while(head != NULL)
            {
                struct Node* pnode = head;
                head  = pnode->next;
                free(pnode);
            }
            pthread_mutex_unlock(&mutex); 
            goto end; 
        }
    }
    
end:
    printf("consumer end\n");
    
    return NULL;
}

int main(int argc, char* argv[])
{
    // 初始化条件变量
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

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
        // 阻塞等待子线程退出
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

    // 销毁条件变量
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);   

    return 0;
}
