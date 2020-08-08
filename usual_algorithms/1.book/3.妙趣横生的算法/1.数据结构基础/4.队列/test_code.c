#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct QNode{
    ElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct{
    QueuePtr front;     //队头指针
    QueuePtr rear;      //队尾指针
}LinkQueue;

void initQueue(LinkQueue *q){
    /*初始化一个空队列*/
    q->front = q->rear = (QueuePtr)malloc(sizeof(QNode));
                                /*创建一个头结点，队头队尾指针指向该结点*/
    if( !q->front)
        exit(0);                /*创建头结点失败*/
    
    q->front->next = NULL;      /*头结点指针域置NULL*/
}

void EnQueue(LinkQueue *q, ElemType e){
    QueuePtr p;
    
    p = (QueuePtr)malloc(sizeof(QNode));    /*创建一个队列元素结点*/
    if(!q->front) 
        exit(0);                 /*创建头结点失败*/
    
    p->data = e;
    p->next = NULL;
    q->rear ->next = p;
    q->rear = p;
}

void DeQueue(LinkQueue *q, ElemType *e){
    /*如果队列q不为空，删除q的队头元素，用e返回其值*/
    QueuePtr p;
    
    if(q->front == q->rear)
        return;         /*队列为空，返回*/
    p = q->front->next;
    *e = p->data;
    q->front->next = p->next;
    if(q->rear == p)
        q->rear = q->front;    /*如果队头就是队尾，则修改队尾指针*/
    free(p);
}

DestroyQueue(LinkQueue *q){
    while(q->front){
        q->rear = q->front->next;       /*q->rear 指向q->front的后继结点*/
        free(q->front);                 /*释放掉q->front*/
        q->front = q->rear;             /*q->front后移*/
    }
}

/****************************/

int main(int argc, char* argv[])
{
    ElemType e;
    LinkQueue q;
    
    initQueue(&q);              /*初始化一个队列q*/
    printf("Please input a string into a queue\n");
    scanf("%c",&e);
    
    while(e!='@'){
        EnQueue(&q,e);          /*向队列中输入字符串，以@表示结束*/ 
        scanf("%c",&e);
    }
    
    printf("The string into the queue is\n");
    
    while(q.front != q.rear){   /*将队列中的元素出队列，并打印在屏幕上*/
        DeQueue(&q,&e);
        printf("%c",e);
    }
    
    printf("\n");
    
    DestroyQueue(&q);           /*销毁队列q*/
    
    return 0;
}