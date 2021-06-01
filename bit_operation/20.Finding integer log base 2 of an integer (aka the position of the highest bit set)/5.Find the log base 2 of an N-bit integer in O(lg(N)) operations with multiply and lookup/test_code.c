#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//以2为底取对数函数log2(v)
int bit_log2(unsigned int v)
{
    //uint32_t v; // find the log base 2 of 32-bit v
    int r;      // result goes here

    static const int MultiplyDeBruijnBitPosition[32] = 
    {
        0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
    };

    v |= v >> 1; // first round down to one less than a power of 2 
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;

    r = MultiplyDeBruijnBitPosition[(unsigned int)(v * 0x07C4ACDDU) >> 27];
    
    return r;
}

//如果您知道 v 是 2 的幂，那么你只需要以下内容：
//如果不是的话，会出错
int bit_log2_2(unsigned int v)
{
    //uint32_t v; // find the log base 2 of 32-bit v
    int r;      // result goes here

    static const int MultiplyDeBruijnBitPosition2[32] = 
    {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    r = MultiplyDeBruijnBitPosition2[(unsigned int)(v * 0x077CB531U) >> 27];
    
    return r;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;

    for(i = 0; i < 65; i++)
    {
        printf("%d %d\n", i, bit_log2(i));
    }
    
    for(i = 0; i < 65; i++)
    {
        printf("%d %d\n", i, bit_log2_2(i));
    }
    
    return 0;
}