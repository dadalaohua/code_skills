#include <stdio.h>
#include <string.h>

#include "CBUF.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned char   uint8_t;
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define myQ_SIZE    64

volatile struct
{
    uint8_t     m_getIdx;
    uint8_t     m_putIdx;
    uint8_t     m_entry[ myQ_SIZE ];

} myQ;

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;
    unsigned char buffer[64];
    unsigned char buffer_out[64];
    
    CBUF_Init(myQ);
    
    printf("fifo cnt = %d\n", CBUF_Len(myQ));
    printf("fifo IsEmpty = %d\n", CBUF_IsEmpty(myQ));
    printf("fifo IsFull = %d\n", CBUF_IsFull(myQ));
    
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
        CBUF_Push(myQ, buffer[i]);
    }
    
    printf("fifo cnt = %d\n", CBUF_Len(myQ));
    printf("fifo IsEmpty = %d\n", CBUF_IsEmpty(myQ));
    printf("fifo IsFull = %d\n", CBUF_IsFull(myQ));
    
    printf("fifo get beginning of 0 data %d \n", CBUF_Get(myQ, 0));
    printf("fifo get beginning of 32 data %d \n", CBUF_Get(myQ, 32));
    
    printf("fifo get end of 2 data %d \n", CBUF_GetEnd(myQ, 2));
    printf("fifo get end of 0 data %d \n", CBUF_GetEnd(myQ, 0));
    
    memset(buffer_out, 0, sizeof(buffer_out));
    
    for(i = 0; i < sizeof(buffer); i++)
    {
        buffer_out[i] = CBUF_Pop(myQ);
    }
    
    printf("fifo cnt = %d\n", CBUF_Len(myQ));
    printf("fifo IsEmpty = %d\n", CBUF_IsEmpty(myQ));
    printf("fifo IsFull = %d\n", CBUF_IsFull(myQ));
    
    for(i = 0; i < sizeof(buffer_out); i++)
    {
        printf("buffer_out[%d] = %d ", i, buffer_out[i]);
        if(i % 5 == 0)
            printf("\n");
    }
    printf("\n");
    
    return 0;
}