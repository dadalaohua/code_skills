#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
static void *
utf8_decode(void *buf, unsigned int *c, int *e)
{
    static const char lengths[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 4, 0
    };
    static const int masks[]  = {0x00, 0x7f, 0x1f, 0x0f, 0x07};
    static const unsigned int mins[] = {4194304, 0, 128, 2048, 65536};
    static const int shiftc[] = {0, 18, 12, 6, 0};
    static const int shifte[] = {0, 6, 4, 2, 0};

    unsigned char *s = buf;
    int len = lengths[s[0] >> 3];

    /* Compute the pointer to the next character early so that the next
     * iteration can start working on the next character. Neither Clang
     * nor GCC figure out this reordering on their own.
     */
    unsigned char *next = s + len + !len;

    /* Assume a four-byte character and load four bytes. Unused bits are
     * shifted out.
     */
    *c  = (unsigned int)(s[0] & masks[len]) << 18;
    *c |= (unsigned int)(s[1] & 0x3f) << 12;
    *c |= (unsigned int)(s[2] & 0x3f) <<  6;
    *c |= (unsigned int)(s[3] & 0x3f) <<  0;
    *c >>= shiftc[len];

    /* Accumulate the various error conditions. */
    *e  = (*c < mins[len]) << 6; // non-canonical encoding
    *e |= ((*c >> 11) == 0x1b) << 7;  // surrogate half?
    *e |= (*c > 0x10FFFF) << 8;  // out of range?
    *e |= (s[1] & 0xc0) >> 2;
    *e |= (s[2] & 0xc0) >> 4;
    *e |= (s[3]       ) >> 6;
    *e ^= 0x2a; // top two bits of each tail byte correct?
    *e >>= shifte[len];

    return next;
}

void print_valid_char(unsigned char *buf) {
    unsigned char *next = buf;
    unsigned char *last = buf;
    unsigned int c;
    int e;
    
    while(*next != 0) {
        last = next;
        next = utf8_decode(next, &c, &e);
        
        //将UTF8解码失败的字符设置为空格
        if(e != 0) {
            int len = next - last;
            for(int i = 0; i < len; i++) {
                *(last + i) = ' ';
            }
            e = 0;
        } else if(c < 0x20) { //将小于0x20的不可见字符设置为空格
            *last = ' ';
        }
    }
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char buf[100] = {0};
    sprintf((char *)buf, "%s", "你好");
    printf("%s\n", buf);
    buf[6]  = 0x61;
    buf[7]  = 0x01;
    buf[8] = 0x77;
    sprintf((char *)&buf[9], "%s", "世界");
    buf[15] = 0x6D;
    buf[16] = 0x03;
    buf[17] = 0x04;
    buf[18] = 0x62;
    buf[19] = 0x0A;
    buf[20] = 0x71;
    printf("%s\n", buf);
    for(int i = 0; i < strlen((char *)buf); i++) {
        printf("0x%x ", buf[i]);
    }
    printf("\n");
    
    //转换为有效字符或者可见字符
    print_valid_char(buf);
    for(int i = 0; i < strlen((char *)buf); i++) {
        printf("0x%x ", buf[i]);
    }
    printf("\n");
    printf("test:\n");
    printf("%s\n", buf);
    printf("\n");
    printf("\n");
    
    unsigned char testbuf[] = {0x34,0x32,0x2c,0x22, 
        0x66,0x6c,0x61,0x67, 
        0x73,0x22,0x3a,0x31, 
        0x7d,0x2c,0x7b,0x22, 
        0x73,0x73,0x69,0x64, 
        0x22,0x3a,0x22,0xe8, 
        0xc9,0xb7,0xe3,0xd6, 
        0xb1,0xb2,0xa5,0xd7, 
        0xa8,0xd3,0xc3,0x22, 
        0x2c,0x22,0x72,0x73, 
        0x73,0x69,0x22,0x3a, 
        0x2d,0x34,0x36,0x2c, 
        0x22,0x66,0x6c,0x61, 
        0x67,0x73,0x22,0x3a, 
        0x31,0x7d,0x2c,0x7b, 
        0x22,0x73,0x73,0x69, 
        0x64,0x22,0x3a,0x22, 
        0x54,0x65,0x6e,0x64, 
        0x61,0x5f,0x42,0x41, 
        0x43,0x37,0x43,0x30, 
        0x22,0x2c,0x22,0x72, 
        0x73,0x73,0x69,0x22, 
        0x3a,0x2d,0x34,0x37, 
        0x2c,0x22,0x66,0x6c, 
        0x61,0x67,0x73,0x22};
    printf("%s\n", testbuf);
    for(int i = 0; i < strlen((char *)testbuf); i++) {
        printf("0x%x ", testbuf[i]);
    }
    printf("\n");
    
    print_valid_char(testbuf);
    for(int i = 0; i < strlen((char *)testbuf); i++) {
        printf("0x%x ", testbuf[i]);
    }
    printf("\n");
    printf("test:\n");
    printf("%s\n", testbuf);
    
    return 0;
}