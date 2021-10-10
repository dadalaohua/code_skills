#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "tos_k.h"

typedef struct item_st {
    int a;
    int b;
    int c;
} item_t;

//定义元素数量
#define PRIO_QUEUE_ITEM_MAX 5

//提供一块缓冲区用于内部管理
uint8_t prio_q_buffer[PRIO_QUEUE_ITEM_MAX * sizeof(item_t)];
//队列的缓冲区
uint8_t mgr_pool[TOS_PRIO_Q_MGR_ARRAY_SIZE(PRIO_QUEUE_ITEM_MAX)];

k_prio_q_t prio_q;

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    k_err_t err;
    int i;
    item_t item;
    size_t item_size;
    k_prio_t item_prio;
    
    //创建优先级队列
    tos_prio_q_create(&prio_q, mgr_pool, prio_q_buffer, PRIO_QUEUE_ITEM_MAX, sizeof(item_t));
    
    //数据入队
    for(i = PRIO_QUEUE_ITEM_MAX;i > 0; i--)
    {
        item.a = i;
        item.b = i;
        item.c = i;
        
        err = tos_prio_q_enqueue(&prio_q, &item, sizeof(item), i);
        if(err == K_ERR_NONE)
        {
            printf("enqueue a item: %d %d %d\n", item.a, item.b, item.c);
        }
        else
        {
            printf("prio queue enqueue fail,err = %d\r\n", err);
        }
    }
    
    //队列满之后，继续入队
    err = tos_prio_q_enqueue(&prio_q, &item, sizeof(item_t), i);
    if(err == K_ERR_PRIO_Q_FULL)
    {
        printf("prio queue is full: %s\n", tos_prio_q_is_full(&prio_q) ? "TRUE" : "FALSE");
    }
    else
    {
        printf("prio queue enqueue fail,err = %d\r\n", err);
    }
    
    //数据出队
    for(i = 0; i < PRIO_QUEUE_ITEM_MAX; ++i)
    {
        err = tos_prio_q_dequeue(&prio_q, &item, &item_size, &item_prio);
        if(err == K_ERR_NONE)
        {
            printf("dequeue a item[piro %d]: %d %d %d\n", item_prio, item.a, item.b, item.c);
        }
        else
        {
            printf("prio queue dequeue fail,err = %d\r\n", err);
        }
    }
    
    //没有数据后继续出队
    err = tos_prio_q_dequeue(&prio_q, &item, &item_size, &item_prio);
    if(err == K_ERR_PRIO_Q_EMPTY)
    {
        printf("prio queue is empty: %s\n", tos_prio_q_is_empty(&prio_q) ? "TRUE" : "FALSE");
    }
    else
    {
        printf("prio queue dequeue fail,err = %d\r\n", err);
    }
    
    return 0;
}