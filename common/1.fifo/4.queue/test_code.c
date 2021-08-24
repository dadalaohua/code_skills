#include <stdio.h>
#include <string.h>

#include "queue.h"

unsigned char test_buffer[64];
queue_t test_queue;

int main(int argc, char* argv[])
{ 
    int i;
    unsigned char buffer[64];
    unsigned char buffer_out[64];
    
    //设置队列的大小为64，实际可用只有63，属于设计缺陷
    queue_create(&test_queue, test_buffer, sizeof(test_buffer), sizeof(unsigned char));
    
    printf("fifo cnt = %d\n", queue_size(&test_queue));
    printf("fifo IsEmpty = %d\n", queue_is_empty(&test_queue));
    printf("fifo IsFull = %d\n", queue_is_full(&test_queue));
    
    for(i = 0; i < sizeof(buffer); i++)
    {
        buffer[i] = i;
        printf("buffer[%d] = %d ", i, buffer[i]);
        if(i % 5 == 0)
            printf("\n");
    }
    printf("\n");
    
    for(i = 0; i < sizeof(buffer); i++)
    {
        queue_put(&test_queue, &buffer[i]);
    }
    
    printf("fifo cnt = %d\n", queue_size(&test_queue));
    printf("fifo IsEmpty = %d\n", queue_is_empty(&test_queue));
    printf("fifo IsFull = %d\n", queue_is_full(&test_queue));

    memset(buffer_out, 0, sizeof(buffer_out));
    
    for(i = 0; i < sizeof(buffer_out); i++)
    {
        queue_get(&test_queue, &buffer_out[i]);
    }
    
    printf("fifo cnt = %d\n", queue_size(&test_queue));
    printf("fifo IsEmpty = %d\n", queue_is_empty(&test_queue));
    printf("fifo IsFull = %d\n", queue_is_full(&test_queue));
    
    for(i = 0; i < sizeof(buffer_out); i++)
    {
        printf("buffer_out[%d] = %d ", i, buffer_out[i]);
        if(i % 5 == 0)
            printf("\n");
    }
    printf("\n");
    
    return 0;
}