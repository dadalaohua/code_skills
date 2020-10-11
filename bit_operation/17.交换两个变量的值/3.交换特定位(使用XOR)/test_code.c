#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int swap_32(unsigned int b, unsigned int i, unsigned int j, unsigned int n)
{
    unsigned int r;    // bit-swapped result goes here
                       // 变量r存放位交换后的结果

    unsigned int x = ((b >> i) ^ (b >> j)) & ((1U << n) - 1); // XOR temporary
                                                              // 异或操作的临时变量
    r = b ^ ((x << i) | (x << j));
    
    return r;
}

unsigned char swap_8(unsigned char b, unsigned char i, unsigned char j, unsigned char n)
{
    unsigned char r;    // bit-swapped result goes here
                       // 变量r存放位交换后的结果

    unsigned char x = ((b >> i) ^ (b >> j)) & ((1U << n) - 1); // XOR temporary
                                                              // 异或操作的临时变量
    r = b ^ ((x << i) | (x << j));
    
    return r;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
举一个 指定二进制位范围来交换数值 的例子
我们有b = 00101111（二进制形式），
希望交换的位长度为n = 3，
起始点是i = 1（从右往左数第2个位）的连续3个位，
以及起点为j = 5的连续3个位；
那么结果就会是r = 11100011(二进制)。
*/
int main(int argc, char* argv[])
{
    unsigned int num_32;
    unsigned char num_8;
    
    num_32 = 0x2000000F; //0010 0000 0000 0000 0000 0000 0000 1111
    
    //0010 0000 0000 0000 0000 0000 0000 1111 => 
    //1110 0000 0000 0000 0000 0000 0000 0011 0xE0000003
    printf("num_32 0x%x swap 0x%x\n", num_32, swap_32(num_32, 1, 29, 3));
    
    num_8 = 0x2f; //00101111
    
    //00101111 => 11100011 0xE3
    printf("num_8 0x%x swap 0x%x\n", num_8, swap_8(num_8, 1, 5, 3));

    return 0;
}