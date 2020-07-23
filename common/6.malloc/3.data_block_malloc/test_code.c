#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "data_block_man.h"

int main(int argc, char* argv[])
{
    unsigned int remain, i;
    unsigned char *ptr;
    
    data_block_mem_init();
    
    remain = data_block_mem_remain();
    printf("data block mem remain %d\n", remain);
    
    ptr = data_block_mem_malloc(3);
    
    memset(ptr, 3, 3*DATA_BLOCK_SIZE);
    
    for(i = 0; i < 3*DATA_BLOCK_SIZE; i++)
    {
        if(i%16 == 0)
            printf("\n");
        
        printf("0x%x ", *(ptr + i));
    }
    printf("\n");
    
    remain = data_block_mem_offset(ptr);
    printf("data block mem offset %d\n", remain);
    
    remain = data_block_mem_remain();
    printf("data block mem remain %d\n", remain);
    
    data_block_mem_free(ptr);
    
    remain = data_block_mem_remain();
    printf("data block mem remain %d\n", remain);
    
    ptr = data_block_mem_malloc(5);
    
    for(i = 0; i < 5*DATA_BLOCK_SIZE; i++)
    {
        if(i%16 == 0)
            printf("\n");
        
        printf("0x%x ", *(ptr + i));
    }
    printf("\n");
    
    remain = data_block_mem_remain();
    printf("data block mem remain %d\n", remain);
    
    data_block_mem_free(ptr);
    
    remain = data_block_mem_remain();
    printf("data block mem remain %d\n", remain);
     
    return 0;
}