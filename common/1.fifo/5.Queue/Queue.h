#include <stdio.h>

#ifndef __QUEUE_H__
#define __QUEUE_H__

/***************************************
 *fuction :数据类型定义
 *author  :(公众号:最后一个bug)
 **************************************/
//节点数据类型定义
typedef struct _tag_stNode
{ 
   void *data;              //数据指针
   struct _tag_stNode *next;//指向下一个节点
}STNode; 

//队列结构体定义
typedef struct _tag_stQueue 
{ 
   int    QueueSize; //队列大小
   size_t memSize;  //数据大小
   STNode *head;    //头指针
   STNode *tail;    //尾指针
}STQueue; 

/***************************************
 *fuction  :函数接口声明
 *author   :(公众号:最后一个bug)
 **************************************/
//队列接口函数定义
void QueueInit(STQueue *q, size_t memSize); 
int  QueueIn(STQueue *, const void *); 
void QueueOut(STQueue *, void *); 
void GetQueueUnit(STQueue *, void *); 
void ClearQueue(STQueue *); 
int  GetQueueSize(STQueue *); 

#endif 