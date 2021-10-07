#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
char * toHex(int num, char *buf){
    char groupbuf[8];
    int i, flag = 0;
    char *p = buf;
    
    if(num == 0) {
        *p++ = '0';
        *p   = '\0';
        return buf;
    }
    
    for(i = 0; i < 8; i++) {
        groupbuf[i] = (num >> (i << 2)) & 0xf;
    }
    
    for(i = 7; i >= 0; i--) {
        if(groupbuf[i] != 0)
            flag = 1;
        
        if(flag) {
            if  (groupbuf[i] > 9)
                *p++ = (char)(groupbuf[i] - 10 + 'a');
            else
                *p++ = (char)(groupbuf[i] + '0');
        }
    }
    
    *p = '\0';
    
    return buf;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int num = 0;
    char buf[9];

    printf("num %d %x %s\n", num, num, toHex(num, buf));
    
    num = -2147483648;
    printf("num %d %x %s\n", num, num, toHex(num, buf));
    
    num = 2147483647;
    printf("num %d %x %s\n", num, num, toHex(num, buf));
    
    num = 26;
    printf("num %d %x %s\n", num, num, toHex(num, buf));
    
    num = -1;
    printf("num %d %x %s\n", num, num, toHex(num, buf));
    
    return 0;
}