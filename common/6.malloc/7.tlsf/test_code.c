#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tlsf.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char buf[10000];    //分配给内存池的空间
    printf("buf: %p\n", buf);
    printf("size:           %zu\n", tlsf_size());           //内存管理占用的空间
    printf("align_size:     %zu\n", tlsf_align_size());     //对齐大小
    printf("block_size_min: %zu\n", tlsf_block_size_min()); //最小值
    printf("block_size_max: %zu\n", tlsf_block_size_max()); //最大值
    printf("pool_overhead:  %zu\n", tlsf_pool_overhead());  //开销
    printf("alloc_overhead: %zu\n", tlsf_alloc_overhead()); //开销
    
    tlsf_t tlsf = tlsf_create_with_pool(buf, sizeof(buf));  //创建， 这里有效的空间大小为 sizeof(buf) - tlsf_size()
    char *tmp = tlsf_malloc(tlsf, 1024);    //malloc
    printf("%zu\n", tlsf_block_size(tmp));  //查看实际分配的内存大小
    tmp = tlsf_realloc(tlsf, tmp, 2048);    //realloc
    printf("%zu\n", tlsf_block_size(tmp));
    tlsf_free(tlsf, tmp);       //free
    
    printf("pool: %p\n", tlsf_get_pool(tlsf));
    tlsf_destroy(tlsf);
    return 0;
}