#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MP_OK               0
#define MP_MALLOC_FIAL      -1
#define MP_NOT_INIT         -2

typedef struct bpn memory_pool_node;

struct bpn{
    unsigned int column;
    unsigned char * data;
    memory_pool_node * next;
};

typedef struct{
    unsigned int total_count;
    unsigned int used_count;
    unsigned int block_len;
    memory_pool_node  * free_header;
    memory_pool_node  * used_header;
}memory_pool_colume;

int buffer_pool_init(unsigned int colume_no, unsigned int block_len[], unsigned int block_count[]);
memory_pool_node * buffer_malloc(unsigned int size);
int buffer_free(memory_pool_node * buffer);
int buffer_pool_destory(void);
int buffer_runtime_print(void);

#endif