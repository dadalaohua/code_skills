#include <stdio.h>

//可选方案 按位与 和 查找表

//按位与方案 内存占用少(32位int，32位机器)
unsigned int reverse_1(unsigned int x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    
    return((x >> 16) | (x << 16));
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

// Option 1:
unsigned int reverse_table_1(unsigned int v)
{
    unsigned int c; // c will get v reversed

    c = (BitReverseTable256[v & 0xff] << 24) | 
        (BitReverseTable256[(v >> 8) & 0xff] << 16) | 
        (BitReverseTable256[(v >> 16) & 0xff] << 8) |
        (BitReverseTable256[(v >> 24) & 0xff]);
    
    return c;
}

unsigned int reverse_table_1_1(unsigned int x)
{
    x = (BitReverseTable256[x       & 0xff] << 24)|
        (BitReverseTable256[x >>  8 & 0xff] << 16)|
        (BitReverseTable256[x >> 16 & 0xff] <<  8)|
        (BitReverseTable256[x >> 24 & 0xff]      );

    return x;
}

// Option 2:
unsigned int reverse_table_2(unsigned int v)
{
    unsigned int c; // c will get v reversed

    unsigned char *p = (unsigned char *) &v;
    unsigned char *q = (unsigned char *) &c;
    
    q[3] = BitReverseTable256[p[0]]; 
    q[2] = BitReverseTable256[p[1]]; 
    q[1] = BitReverseTable256[p[2]]; 
    q[0] = BitReverseTable256[p[3]];
    
    return c;
}

//其它方案
//简单
unsigned int reverse_3(unsigned int v)
{
    unsigned int r = v; // r will be reversed bits of v; first get LSB of v
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

//更快 32位处理器
unsigned char reverseBits(unsigned char b)
{
    b = ((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;

    return b;
}

unsigned int reverse_4(unsigned int toReverse)
{
    unsigned int reversed;
    unsigned char inByte0 = (toReverse & 0xFF);
    unsigned char inByte1 = (toReverse & 0xFF00) >> 8;
    unsigned char inByte2 = (toReverse & 0xFF0000) >> 16;
    unsigned char inByte3 = (toReverse & 0xFF000000) >> 24;
    
    reversed = (reverseBits(inByte0) << 24) | (reverseBits(inByte1) << 16) | (reverseBits(inByte2) << 8) | (reverseBits(inByte3));
    
    return reversed;
}

unsigned int reverse_4_1(unsigned int x)
{
    x = (reverseBits(x       & 0xff) << 24)|
        (reverseBits(x >>  8 & 0xff) << 16)|
        (reverseBits(x >> 16 & 0xff) <<  8)|
        (reverseBits(x >> 24 & 0xff)      );
    
    return x;
}

//64位处理器
unsigned char reverseBits_64(unsigned char b)
{
    b = (b * 0x0202020202ULL & 0x010884422010ULL) % 1023;

    return b;
}

unsigned int reverse_4_32(unsigned int x)
{
    x = (reverseBits_64(x       & 0xff) << 24)|
        (reverseBits_64(x >>  8 & 0xff) << 16)|
        (reverseBits_64(x >> 16 & 0xff) <<  8)|
        (reverseBits_64(x >> 24 & 0xff)      );
    
    return x;
}

unsigned long long reverse_4_64(unsigned long long toReverse)
{
    unsigned long long reversed;
    unsigned char inByte0 = (toReverse & 0xFF);
    unsigned char inByte1 = (toReverse & 0xFF00) >> 8;
    unsigned char inByte2 = (toReverse & 0xFF0000) >> 16;
    unsigned char inByte3 = (toReverse & 0xFF000000) >> 24;
    unsigned char inByte4 = (toReverse & 0xFF00000000) >> 32;
    unsigned char inByte5 = (toReverse & 0xFF0000000000) >> 40;
    unsigned char inByte6 = (toReverse & 0xFF000000000000) >> 48;
    unsigned char inByte7 = (toReverse & 0xFF00000000000000) >> 56;
    
    reversed = ((unsigned long long)reverseBits_64(inByte0) << 56) | ((unsigned long long)reverseBits_64(inByte1) << 48)\
                | ((unsigned long long)reverseBits_64(inByte2) << 40) | ((unsigned long long)reverseBits_64(inByte3) << 32)\
                | (reverseBits_64(inByte4) << 24) | (reverseBits_64(inByte5) << 16)\
                | (reverseBits_64(inByte6) << 8) | (reverseBits_64(inByte7));
    
    return reversed;
}

//半字节查表
const static unsigned char BitReverseTable16[] = 
{
    0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE,
    0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF
};

// Option 1:
unsigned int reverse_5_table_1(unsigned int v)
{
    unsigned int reversed; // reversed will get v reversed

    reversed = ((BitReverseTable16[((v & 0xff) >> 4) & 0x0F] | BitReverseTable16[(v & 0xff) & 0x0F] << 4) << 24)\
    | ((BitReverseTable16[((v >> 8) >> 4) & 0x0F] | BitReverseTable16[(v >> 8) & 0x0F] << 4) << 16)\
    | ((BitReverseTable16[((v >> 16) >> 4) & 0x0F] | BitReverseTable16[(v >> 16) & 0x0F] << 4) << 8)\
    | (BitReverseTable16[((v >> 24) >> 4) & 0x0F] | BitReverseTable16[(v >> 24) & 0x0F] << 4);
    
    return reversed;
}

unsigned int reverse_5_table_1_1(unsigned int x)
{
    x = ((BitReverseTable16[((x      ) >> 4) & 0x0F] | BitReverseTable16[(x      ) & 0x0F] << 4) << 24) |
        ((BitReverseTable16[((x >>  8) >> 4) & 0x0F] | BitReverseTable16[(x >>  8) & 0x0F] << 4) << 16) |
        ((BitReverseTable16[((x >> 16) >> 4) & 0x0F] | BitReverseTable16[(x >> 16) & 0x0F] << 4) <<  8) |
         (BitReverseTable16[((x >> 24) >> 4) & 0x0F] | BitReverseTable16[(x >> 24) & 0x0F] << 4);

    return x;
}

unsigned int reverse_5_table_1_2(unsigned int x)
{ 
    x = ((BitReverseTable16[(x >>  4) & 0x0F] | BitReverseTable16[(x      ) & 0x0F] << 4) << 24) |
        ((BitReverseTable16[(x >> 12) & 0x0F] | BitReverseTable16[(x >>  8) & 0x0F] << 4) << 16) |
        ((BitReverseTable16[(x >> 20) & 0x0F] | BitReverseTable16[(x >> 16) & 0x0F] << 4) <<  8) |
         (BitReverseTable16[(x >> 28) & 0x0F] | BitReverseTable16[(x >> 24) & 0x0F] << 4);
    
    return x;
}

// Option 2:
unsigned int reverse_5_table_2(unsigned int v)
{
    unsigned int reversed; // reversed will get v reversed

    unsigned char *p = (unsigned char *) &v;
    unsigned char *q = (unsigned char *) &reversed;
    
    q[3] = BitReverseTable16[(p[0] >> 4) & 0x0F] | BitReverseTable16[p[0] & 0x0F] << 4; 
    q[2] = BitReverseTable16[(p[1] >> 4) & 0x0F] | BitReverseTable16[p[1] & 0x0F] << 4; 
    q[1] = BitReverseTable16[(p[2] >> 4) & 0x0F] | BitReverseTable16[p[2] & 0x0F] << 4;
    q[0] = BitReverseTable16[(p[3] >> 4) & 0x0F] | BitReverseTable16[p[3] & 0x0F] << 4;
    
    return reversed;
}

/****************************/
//64位处理器
unsigned char reverse_6_64(unsigned char x)
{
    x = ((x * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
    
    return x;
}

unsigned int reverse_6(unsigned int x)
{
    x = (reverse_6_64(x       & 0xff) << 24)|
        (reverse_6_64(x >>  8 & 0xff) << 16)|
        (reverse_6_64(x >> 16 & 0xff) <<  8)|
        (reverse_6_64(x >> 24 & 0xff)      );
    
    return x;
}

/****************************/

unsigned int reverse_7(unsigned int x)
{
    // swap odd and even bits
    x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
    // swap consecutive pairs
    x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
    // swap nibbles ... 
    x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);
    // swap bytes
    x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
    // swap 2-byte long pairs
    x = ( x >> 16             ) | ( x               << 16);
    
    return x;
}

unsigned int reverse_8(unsigned int v)
{
    unsigned int s = sizeof(v) * 8; // bit size; must be power of 2 
    unsigned int mask = ~0;         
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

// Option 1:
unsigned int reverse_table_10_1(unsigned int x)
{
    x = (BitReverseTable256_2[x       & 0xff] << 24)|
        (BitReverseTable256_2[x >>  8 & 0xff] << 16)|
        (BitReverseTable256_2[x >> 16 & 0xff] <<  8)|
        (BitReverseTable256_2[x >> 24 & 0xff]      );

    return x;
}

// Option 2:
unsigned int reverse_table_10_2(unsigned int v)
{
    unsigned int c; // c will get v reversed

    unsigned char *p = (unsigned char *) &v;
    unsigned char *q = (unsigned char *) &c;
    
    q[3] = BitReverseTable256_2[p[0]]; 
    q[2] = BitReverseTable256_2[p[1]]; 
    q[1] = BitReverseTable256_2[p[2]]; 
    q[0] = BitReverseTable256_2[p[3]];
    
    return c;
}

/****************************/

int main(int argc, char* argv[])
{
    int num = 0x6a53b3d2;
    long long num_64 = 0x6a53b3d212345678;
    
    printf("reverse num 0x%x\n", num);
    
    printf("reverse 1 0x%x\n", reverse_1(num));
    printf("reverse table 1 0x%x\n", reverse_table_1(num));
    printf("reverse table 1 0x%x\n", reverse_table_1_1(num));
    printf("reverse table 2 0x%x\n", reverse_table_2(num));
    printf("reverse 3 0x%x\n", reverse_3(num));
    printf("reverse 4 0x%x\n", reverse_4(num));
    printf("reverse 4 0x%x\n", reverse_4_1(num));
    printf("reverse 5 table 1 0x%x\n", reverse_5_table_1(num));
    printf("reverse 5 table 1 0x%x\n", reverse_5_table_1_1(num));
    printf("reverse 5 table 1 0x%x\n", reverse_5_table_1_2(num));
    printf("reverse 5 table 2 0x%x\n", reverse_5_table_2(num));
    
    printf("reverse 4 32 0x%x\n", reverse_4_32(num));
    printf("reverse 6 32 0x%x\n", reverse_6(num));
    printf("reverse 7 32 0x%x\n", reverse_7(num));
    printf("reverse 8 32 0x%x\n", reverse_8(num));
    
    printf("reverse 10 table 1 0x%x\n", reverse_table_10_1(num));
    printf("reverse 10 table 2 0x%x\n", reverse_table_10_2(num));
    
    printf("reverse num 0x%llx\n", num_64);
    printf("reverse 4 64 0x%llx\n", reverse_4_64(num_64));
    
    return 0;
}