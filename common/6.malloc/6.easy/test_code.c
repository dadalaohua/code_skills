#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i = 0;
    char *buf;
    DMEM *node = DynMemGet(512);
    
    buf = node->addr;
    memset(buf, 0x5A, node->size);
    printf("addr %d size %d tb %d\n", (int)node->addr, node->size, node->tb);
    
    for(i = 0; i < 32; i++){
        printf("0x%x ", buf[i]);
    }
    printf("\n");

    DynMemPut(node);
    
    return 0;
}