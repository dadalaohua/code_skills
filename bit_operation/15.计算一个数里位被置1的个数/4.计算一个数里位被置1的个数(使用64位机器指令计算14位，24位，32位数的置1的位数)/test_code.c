#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int count_bit1_14(unsigned int v)
{
    //unsigned int v; // count the number of bits set in v
    //                // 待检测的数，计算变量v的二进制中1的个数
    unsigned int c; // c accumulates the total bits set in v
                    // 位被置1的总数，保存计算的结果

    // option 1, for at most 14-bit values in v:
    //公式1 计算最大为14位的数:
    c = (v * 0x200040008001ULL & 0x111111111111111ULL) % 0xf;

    return c;
}

unsigned int count_bit1_24(unsigned int v)
{
    //unsigned int v; // count the number of bits set in v
    //                // 待检测的数，计算变量v的二进制中1的个数
    unsigned int c; // c accumulates the total bits set in v
                    // 位被置1的总数，保存计算的结果

    // option 2, for at most 24-bit values in v:
    //公式2 计算最大为24位的数:
    c =  ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    c += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) 
         % 0x1f;

    return c;
}

unsigned int count_bit1_32(unsigned int v)
{
    //unsigned int v; // count the number of bits set in v
    //                // 待检测的数，计算变量v的二进制中1的个数
    unsigned int c; // c accumulates the total bits set in v
                    // 位被置1的总数，保存计算的结果

    // option 3, for at most 32-bit values in v:
    //公式3 计算最大为32位的数:
    c =  ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    c += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) % 
         0x1f;
    c += ((v >> 24) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    
    return c;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int test1 = 0x0000194B;//‭0000 0000 0000 0000 0001 1001 0100 1011‬ < 0x00003fff
    unsigned int test2 = 0x00B90FA9;//‭0000 0000 1011 1001 0000 1111 1010 1001‬ < 0x00ffffff 
    unsigned int test3 = 0x5134684B;//‭0101 0001 0011 0100 0110 1000 0100 1011‬ < 0xffffffff 
    
    printf("count_bit1 14: %d\n", count_bit1_14(test1));
    printf("count_bit1 24: %d\n", count_bit1_24(test2));
    printf("count_bit1 32: %d\n", count_bit1_32(test3));
    
    return 0;
}