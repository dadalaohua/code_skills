#include <stdio.h>
#include <string.h>

#include "ringbuffer.h"

unsigned char test_buffer[256];
ring_buf_t test_fifo;
ring_buf_t *this_test_fifo;

unsigned int test_fifo_pop(unsigned char *buffer, unsigned int len)
{
    return ring_buf_get(this_test_fifo, buffer, len);
}

unsigned int test_fifo_push(unsigned char *buffer, unsigned int len)
{
    return ring_buf_put(this_test_fifo, buffer, len);
}

unsigned int test_fifo_cnt(void)
{
    return ring_buf_len(this_test_fifo);
}

int test_fifo_init(void)
{
    int result;
    
    this_test_fifo = &test_fifo;
    result = ring_buf_init(this_test_fifo, test_buffer, sizeof(test_buffer));
    
    return result;
}

int main(int argc, char* argv[])
{ 
    int i;
    unsigned char buffer[64];
    unsigned char buffer_out[64];
    
    test_fifo_init();
    
    printf("fifo cnt = %d\n", test_fifo_cnt());
    
    for(i = 0; i < sizeof(buffer); i++)
    {
        buffer[i] = i;
        printf("buffer[%d] = %d ", i, buffer[i]);
        if(i % 5 == 0)
            printf("\n");
    }
    printf("\n");
    
    test_fifo_push(buffer, sizeof(buffer));
    
    printf("fifo cnt = %d\n", test_fifo_cnt());
    
    memset(buffer_out, 0, sizeof(buffer_out));
    
    test_fifo_pop(buffer_out, sizeof(buffer_out));
    
    printf("fifo cnt = %d\n", test_fifo_cnt());
    
    for(i = 0; i < sizeof(buffer_out); i++)
    {
        printf("buffer_out[%d] = %d ", i, buffer_out[i]);
        if(i % 5 == 0)
            printf("\n");
    }
    printf("\n");
    
    return 0;
}