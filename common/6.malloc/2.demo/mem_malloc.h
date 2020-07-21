#ifndef __MALLOC_H
#define __MALLOC_H

/************************************************************************/
/*                                                                      */
/************************************************************************/
#ifndef NULL
#define NULL 0
#endif

#define MEM_SIZE 128

typedef struct
{
    unsigned char *mem_ptr;
    unsigned int mem_size;
    unsigned int mem_index;
} mem_block;

int mem_malloc(unsigned int msize);
void *mem_buffer(int id);
void mem_free(int id);
   
#endif
