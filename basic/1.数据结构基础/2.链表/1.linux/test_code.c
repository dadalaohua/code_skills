#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

LIST_HEAD(fox_list);    //链表头

struct fox {
        unsigned int tail_length;
        unsigned int weight;
        struct list_head list;
};

int main(int argc, char* argv[])
{  
    //初始化头结点
    struct fox *bigfox; //每次申请链表结点时所用的指针
    struct list_head * pos; 
    struct fox *p;
    struct list_head *n;
    struct fox *q;
    int i;
    
    for (i=0; i < 10; i++) {
        bigfox = (struct fox *)malloc(sizeof(struct fox));
        bigfox->tail_length = i+1+20;
        bigfox->weight      = i+1;
        list_add_tail(&bigfox->list, &fox_list);
        //list_add(&bigfox->list, &fox_list);
        printf("Node %d has added to the list...\n", i+1);
    }
    
    //遍历链表 法一
    // i = 0;
    // list_for_each(pos, &fox_list) {
        // p = list_entry(pos, struct fox, list);
        // printf("Node %d's data: %d,%d\n", i, p->tail_length, p->weight);
        // i++;
    // }
    
    //遍历链表 法二
    i = 0;
    list_for_each_entry(p, &fox_list, list) {
        printf("Node %d's data: %d,%d\n", i, p->tail_length, p->weight);
        i++;
    }
    
    //遍历链表 法三
    // i = 0;
    // list_for_each_entry_safe(p, q, &fox_list,list) {
        // printf("Node %d's data: %d,%d\n", i, p->tail_length, p->weight);
        // list_del(&p->list); //从链表中删除当前结点       
        // free(p); //释放该数据结点所占空间
        // printf("Node %d has removed from the doublelist...\n", i++);
    // }
    
    //为了安全删除结点而进行的遍历 法一 
    i = 0;
    list_for_each_safe(pos, n, &fox_list) {
        list_del(pos); //从链表中删除当前结点
        p = list_entry(pos, struct fox, list); //得到当前数据结点的首地址，即指针        
        free(p); //释放该数据结点所占空间
        printf("Node %d has removed from the doublelist...\n", i++);
    }
    
    //为了安全删除结点而进行的遍历 法二
    // i = 0;
    // list_for_each_entry_safe(p, q, &fox_list,list) {
        // list_del(&p->list); //从链表中删除当前结点       
        // free(p); //释放该数据结点所占空间
        // printf("Node %d has removed from the doublelist...\n", i++);
    // }

    i = 0;
    list_for_each_entry(p, &fox_list, list) {
        printf("Node %d's data: %d,%d\n", i, p->tail_length, p->weight);
        i++;
    }
    
    i = list_empty(&fox_list);
    printf("Node is %d\n", i);//1为空链表

    return 0;
}