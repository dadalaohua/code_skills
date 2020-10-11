#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

//可选方案 按位与 和 查找表

//按位与方案
unsigned char reverse_1(unsigned char x)
{
    x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));
    x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
    
    return ((x >> 4) | (x << 4));
}

//查找表 最快
static const unsigned char BitReverseTable256[] = 
{
    0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
    0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
    0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
    0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
    0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
    0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
    0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
    0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
    0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
    0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
    0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
    0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
    0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
    0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
    0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
    0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};

unsigned char reverse_table(unsigned char v)
{
    return BitReverseTable256[v];
}

/****************************/

//其它方案

/****************************/

unsigned char reverse_3(unsigned char v)
{
    unsigned char r = v; // r will be reversed bits of v; first get LSB of v
    int s = sizeof(v) * 8 - 1; // extra shift needed at end

    while(v >>= 1)//for (v >>= 1; v; v >>= 1)
    {   
        r <<= 1;
        r |= v & 1;
        s--;
    }
    r <<= s; // shift when v's highest bits are zero
    
    return r;
}

/****************************/

unsigned char reverse_4(unsigned char b)
{
    b = ((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;

    return b;
}

/****************************/

//半字节查表
const static unsigned char BitReverseTable16[] = 
{
    0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE,
    0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF
};

unsigned char reverse_5(unsigned char v)
{
    unsigned char reversed; // reversed will get v reversed

    reversed = BitReverseTable16[((v & 0xff) >> 4) & 0x0F]\
            | BitReverseTable16[(v & 0xff) & 0x0F] << 4;
    
    return reversed;
}

unsigned char reverse_5_1(unsigned char x)
{
    x = BitReverseTable16[ x      & 0x0F] << 4 |
        BitReverseTable16[ x >> 4 & 0x0F];
    
    return x;
}


/****************************/

unsigned char reverse_6(unsigned char c)
{
    int i;
    unsigned char newc = 0x00;

    for (i = 0; i < 7; i++)
    {
        newc |= (c & 1);
        newc <<= 1;
        c >>= 1;
    }

    return newc;
}

/****************************/

unsigned char reverse_7(unsigned char c)
{
#define exchange(x,y) { (x) ^= (y);  \
                        (y) ^= (x);  \
                        (x) ^= (y);  \
                      }

    union {
            unsigned char c;
            struct {
                    unsigned char bit0:1;
                    unsigned char bit1:1;
                    unsigned char bit2:1;
                    unsigned char bit3:1;
                    unsigned char bit4:1;
                    unsigned char bit5:1;
                    unsigned char bit6:1;
                    unsigned char bit7:1;
            } bchar;
    } ubc;
    ubc.c = c;
    exchange(ubc.bchar.bit0, ubc.bchar.bit7);
    exchange(ubc.bchar.bit1, ubc.bchar.bit6);
    exchange(ubc.bchar.bit2, ubc.bchar.bit5);
    exchange(ubc.bchar.bit3, ubc.bchar.bit4);

    return ubc.c;
}

/****************************/

unsigned char reverse_8(unsigned char x)
{
    x = (x * 0x0202020202ULL & 0x010884422010ULL) % 1023;
    
    return x;
}

/****************************/

unsigned char reverse_9(unsigned char x)
{
    x = ((x * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
    
    return x;
}
/****************************/

unsigned char reverse_10(unsigned char v)
{
    unsigned char s = sizeof(v) * 8; // bit size; must be power of 2 
    unsigned char mask = ~0;         
    while ((s >>= 1) > 0) 
    {
      mask ^= (mask << s);
      v = ((v >> s) & mask) | ((v << s) & ~mask);
    }
    
    return v;
}

/****************************/
static const unsigned char BitReverseTable256_2[] = 
{
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};

unsigned char reverse_11(unsigned char v)
{
    return BitReverseTable256_2[v];
}

/****************************/

/****************************/

int main(int argc, char* argv[])
{
    unsigned char num = 0x53;
    
    printf("reverse num 0x%x\n", num);
    
    printf("reverse 1 0x%x\n", reverse_1(num));
    printf("reverse table 0x%x\n", reverse_table(num));
    printf("reverse 3 0x%x\n", reverse_3(num));
    printf("reverse 4 0x%x\n", reverse_4(num));
    printf("reverse 5 table 0x%x\n", reverse_5(num));
    printf("reverse 5 table 0x%x\n", reverse_5_1(num));
    printf("reverse 6 0x%x\n", reverse_6(num));
    printf("reverse 7 0x%x\n", reverse_7(num));
    printf("reverse 8 0x%x\n", reverse_8(num));
    printf("reverse 9 0x%x\n", reverse_9(num));
    printf("reverse 10 0x%x\n", reverse_10(num));
    printf("reverse 11 0x%x\n", reverse_11(num));
    
    return 0;
}