#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Queue.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int val;
    STQueue q;

    QueueInit(&q, sizeof(int));

    for(val = 0; val < 10; val++)
    {
        QueueIn(&q, &val);
        printf("Data: %d enter Quene.\n", val + 1);
    }

    printf("\n");

    GetQueueUnit(&q, &val);

    printf("The value that is at the front of the queue is %d\n\n", val + 1);

    while(GetQueueSize(&q) > 0)
    {
        QueueOut(&q, &val);
        printf("Data: %d exit Quene.\n", val + 1);
    }
    
    return 0;
}