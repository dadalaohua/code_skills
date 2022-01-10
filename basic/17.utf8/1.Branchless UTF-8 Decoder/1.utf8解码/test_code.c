#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utf8.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char buf[100] = {0};
    sprintf(buf, "%s", "你好");
    printf("%s\n", buf);
    for(int i = 0; i < strlen(buf); i++) {
        printf("0x%x ", buf[i]);
    }
    printf("\n");
    
    unsigned int c;
    int e;
    unsigned char *next = buf;
    while(*next != 0) {
        next = utf8_decode(next, &c, &e);
        printf("0x%x\n", c);
        printf("%d\n", e);
    }
    
    return 0;
}