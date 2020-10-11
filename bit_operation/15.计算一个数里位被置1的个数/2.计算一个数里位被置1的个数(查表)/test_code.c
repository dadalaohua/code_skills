#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
static const unsigned char BitsSetTable256[256] =
{
#   define B2(n) n,     n+1,     n+1,     n+2
#   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
    B6(0), B6(1), B6(1), B6(2)
};

unsigned int count_bit1_1(unsigned int v)
{
    //unsigned int v; // count the number of bits set in v
    //                // 计算变量v的二进制中1的个数
    unsigned int c; // c accumulates the total bits set in v
                    // 保存计算的结果
    // Option 1:
    // 第一种：
    c = BitsSetTable256[v & 0xff] +
        BitsSetTable256[(v >> 8) & 0xff] +
        BitsSetTable256[(v >> 16) & 0xff] +
        BitsSetTable256[v >> 24];

    return c;
}

unsigned int count_bit1_2(unsigned int v)
{
    //unsigned int v; // count the number of bits set in v
    //                // 计算变量v的二进制中1的个数
    unsigned int c; // c accumulates the total bits set in v
                    // 保存计算的结果
    // Option 2:
    // 第二种：
    unsigned char * p = (unsigned char *) &v;
    c = BitsSetTable256[p[0]] +
        BitsSetTable256[p[1]] +
        BitsSetTable256[p[2]] +
        BitsSetTable256[p[3]];

    return c;
}

unsigned int count_bit1_3(unsigned int v)
{
    unsigned char BitsSetTable256_1[256];
    int i;
    unsigned int c; // c accumulates the total bits set in v
                    // 保存计算的结果
    
    // To initially generate the table algorithmically:
    // 使用算法来预处理表的内容
    BitsSetTable256_1[0] = 0;
    for (i = 0; i < 256; i++)
    {
        BitsSetTable256_1[i] = (i & 1) + BitsSetTable256_1[i / 2];
    }
    
    c = BitsSetTable256_1[v & 0xff] +
        BitsSetTable256_1[(v >> 8) & 0xff] +
        BitsSetTable256_1[(v >> 16) & 0xff] +
        BitsSetTable256_1[v >> 24];
        
    return c;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int test = 0x5134684B;
    
    printf("count_bit1: %d\n", count_bit1_1(test));
    printf("count_bit1: %d\n", count_bit1_2(test));
    printf("count_bit1: %d\n", count_bit1_3(test));
    
    return 0;
}