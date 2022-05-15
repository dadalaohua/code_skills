#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
static void *
utf8_encode(void *buf, long c)
{
    unsigned char *s = buf;
    if (c >= (1L << 16)) {
        s[0] = 0xf0 |  (c >> 18);
        s[1] = 0x80 | ((c >> 12) & 0x3f);
        s[2] = 0x80 | ((c >>  6) & 0x3f);
        s[3] = 0x80 | ((c >>  0) & 0x3f);
        return s + 4;
    } else if (c >= (1L << 11)) {
        s[0] = 0xe0 |  (c >> 12);
        s[1] = 0x80 | ((c >>  6) & 0x3f);
        s[2] = 0x80 | ((c >>  0) & 0x3f);
        return s + 3;
    } else if (c >= (1L << 7)) {
        s[0] = 0xc0 |  (c >>  6);
        s[1] = 0x80 | ((c >>  0) & 0x3f);
        return s + 2;
    } else {
        s[0] = c;
        return s + 1;
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char buf[4] = {0};
    long c = 0xf00c; //unicode值，对应utf8值ef808c
    
    //方式一
    unsigned char* retbuf = utf8_encode(buf, c);
    for(int i = 0; i < (retbuf - buf); i++)
        printf("%x ", buf[i]);
    printf("\n");//打印结果ef 80 8c
    
    //方式二
    unsigned int val = 0;
    utf8_encode(&val, c);
    printf("%x\n", val);
    printf("\n");//打印结果8c80ef， 小端
    
    return 0;
}