#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int count_bit1(unsigned int v)
{
    //unsigned int v; // count bits set in this (32-bit value)
    unsigned int c; // store the total here
    static const int S[] = {1, 2, 4, 8, 16}; // Magic Binary Numbers
    static const int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

    c = v - ((v >> 1) & B[0]);
    c = ((c >> S[1]) & B[1]) + (c & B[1]);
    c = ((c >> S[2]) + c) & B[2];
    c = ((c >> S[3]) + c) & B[3];
    c = ((c >> S[4]) + c) & B[4];
    
    return c;
}

unsigned int count_bit2(unsigned int v)
{
    unsigned int c; // store the total here
    
    v = v - ((v >> 1) & 0x55555555);                    // reuse input as temporary
                                                        // 将输入变量作为临时变量重复使用
    v = (v & 0x33333333) + ((v >> 2) & 0x33333333);     // temp
                                                        // 临时变量
    c = (((v + (v >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24; // count
                                                        // 计算结果
    return c;
}

unsigned int count_bit3(unsigned int v)
{
    return c;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int test = 0x5134684B;
    
    printf("count_bit1: %d\n", count_bit1(test));
    printf("count_bit2: %d\n", count_bit2(test));
    //printf("count_bit3: %d\n", count_bit3(test));

    return 0;
}