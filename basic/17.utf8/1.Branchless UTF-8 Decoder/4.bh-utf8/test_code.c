#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "bh-utf8.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char buf[100] = {0};
    sprintf((char *)buf, "%s", "你好");
    printf("%s\n", buf);
    for(int i = 0; i < strlen((char *)buf); i++) {
        printf("0x%x ", buf[i]);
    }
    printf("\n");
    
    unsigned int c, state;
    unsigned char *next = buf;
    while(*next != 0) {
        if (!bh_utf8_decode(&state, &c, *next))
            printf("0x%x\n", c);
        else if (state == UTF8_REJECT)
            printf("%d\n", state);  // force errors to be checked
        
        next++;
    }
    
    return 0;
}