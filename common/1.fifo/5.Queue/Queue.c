#include <stdlib.h>
#include <string.h>
#include "Queue.h"

/***************************************
 *fuction  :队列初始化
 *author   :(公众号:最后一个bug)
 **************************************/
void QueueInit(STQueue *q, size_t memSize)
{
   q->QueueSize = 0;
   q->memSize = memSize;
   q->head = q->tail = NULL;
}

/***************************************
 *fuction  :入队列
 *author   :(公众号:最后一个bug)
 **************************************/
int QueueIn(STQueue *q, const void *data)
{
    STNode *newNode = (STNode *)malloc(sizeof(STNode));

    if(newNode == NULL)
    {
        return -1;
    }

    newNode->data = malloc(q->memSize);

    if(newNode->data == NULL)
    {
        free(newNode);
        return -1;
    }

    newNode->next = NULL;

    memcpy(newNode->data, data, q->memSize);

    if(q->QueueSize == 0)
    {
        q->head = q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }

    q->QueueSize++;
    return 0;
}

/***************************************
 *fuction  :出队列
 *author   :(公众号:最后一个bug)
 **************************************/
void QueueOut(STQueue *q, void *data)
{
    if(q->QueueSize > 0)
    {
        STNode *temp = q->head;
        memcpy(data, temp->data, q->memSize);

        if(q->QueueSize > 1)
        {
            q->head = q->head->next;
        }
        else
        {
            q->head = NULL;
            q->tail = NULL;
        }

        q->QueueSize--;
        free(temp->data);
        free(temp);
    }
}

/***************************************
 *fuction  :获得队列头部数据
 *author   :(公众号:最后一个bug)
 **************************************/
void GetQueueUnit(STQueue *q, void *data)
{
    if(q->QueueSize > 0)
    {
       STNode *temp = q->head;
       memcpy(data, temp->data, q->memSize);
    }
}

/***************************************
 *fuction  :清除队列
 *author   :(公众号:最后一个bug)
 **************************************/
void ClearQueue(STQueue *q)
{
  STNode *temp;

  while(q->QueueSize > 0)
  {
      temp = q->head;
      q->head = temp->next;
      q->QueueSize--;
      free(temp->data);
      free(temp);
  }

  q->head = NULL;
  q->tail = NULL;
}

/***************************************
 *fuction  :获得队列数据个数
 *author   :(公众号:最后一个bug)
 **************************************/
int GetQueueSize(STQueue *q)
{
    return q->QueueSize;
}