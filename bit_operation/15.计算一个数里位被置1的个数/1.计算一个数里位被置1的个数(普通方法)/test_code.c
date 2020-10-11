#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int count_bit1(unsigned int v)
{
    //unsigned int v; // count the number of bits set in v
    //                // 计算变量v的二进制中1的个数
    unsigned int c; // c accumulates the total bits set in v
                    // 保存计算的结果

    for (c = 0; v; v >>= 1)
    {
        c += v & 1;
    }
    
    return c;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int test = 0x5134684B;
    
    printf("count_bit1: %d\n", count_bit1(test));
    
    return 0;
}