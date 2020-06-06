#include "fifo.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
int fifo_init(struct fifo *fifo, unsigned char *buffer, unsigned int size)
{
    /* size must be a power of 2 */
    if (size & (size - 1))
        return -1;
    
    if (!fifo || !buffer || size == 0)
        return -1;

    fifo->buffer = buffer;
    fifo->size = size;
    fifo->in = fifo->out = 0;

    return 0;
}

unsigned int fifo_put(struct fifo *fifo, unsigned char *buffer, unsigned int len)
{
    unsigned int l;

    len = min(len, fifo->size - fifo->in + fifo->out);

    /* first put the data starting from fifo->in to buffer end */
    l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
    memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);

    /* then put the rest (if any) at the beginning of the buffer */
    memcpy(fifo->buffer, buffer + l, len - l);

    fifo->in += len;

    return len;
}

unsigned int fifo_get(struct fifo *fifo, unsigned char *buffer, unsigned int len)
{
    unsigned int l;

    len = min(len, fifo->in - fifo->out);

    /* first get the data from fifo->out until the end of the buffer */
    l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
    memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);

    /* then get the rest (if any) from the beginning of the buffer */
    memcpy(buffer + l, fifo->buffer, len - l);

    fifo->out += len;

    return len;
}

unsigned int fifo_cnt(struct fifo *fifo)
{
    return (fifo->in - fifo->out);
}

void fifo_reset(struct fifo *fifo)
{
    fifo->in = fifo->out = 0;
}
