#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "memory_pool.h"

int main(int argc, char* argv[])
{
    printf("press any key to start init and malloc memory pool\n");
    getchar();
    unsigned int a[10] = { 8 ,16 ,32 ,64 ,128 , 256 , 512 , 1024 ,2028 , 4096};
    unsigned int b[10] = { 100 ,500 ,1000 ,1500 ,2000 , 3000 , 4000 , 5000 ,4000 , 2000};
    buffer_pool_init(10, a , b);
    int i = 455;
    memory_pool_node * node = NULL;
#if 0
    while (i > 0)
    {
        node = buffer_malloc(6);
        if (node != NULL)
        {
            printf("pool no[%d] get memory success!!!\n" , node->column);
            node->data[0] = i;
        }
        else
        {
            printf("malloc fail !!!\n");
            getchar();
        }
        i--;
        Sleep(10);
    }
    getchar();
#endif
    memory_pool_node * node1 = buffer_malloc(6);
    memory_pool_node * node2 = buffer_malloc(172);
    memory_pool_node * node3 = buffer_malloc(186);
    memory_pool_node * node4 = buffer_malloc(1300);
    memory_pool_node * node5 = buffer_malloc(2100);
    buffer_malloc(40);
    buffer_malloc(60);
    buffer_malloc(80);
    buffer_malloc(100);
    buffer_malloc(120);
    buffer_malloc(130);
    buffer_malloc(150);
    buffer_malloc(180);
    buffer_malloc(700);
    buffer_malloc(900);
    buffer_runtime_print();
    printf("press any key to free memory pool\n");
    getchar();
    buffer_free(node5);
    buffer_free(node4);
    buffer_free(node3);
    buffer_runtime_print();
    buffer_free(node2);
    buffer_free(node1);
    buffer_runtime_print();
    printf("press any key to destory memory pool\n");
    getchar();
    buffer_pool_destory();
    printf("press any key to quit\n");
    getchar();
     
    return 0;
}