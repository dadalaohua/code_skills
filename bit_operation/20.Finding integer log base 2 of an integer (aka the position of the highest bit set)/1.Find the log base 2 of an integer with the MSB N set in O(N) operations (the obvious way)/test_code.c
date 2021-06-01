#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//以2为底取对数函数log2(v)
int bit_log2(int v)
{
    //unsigned int v; // 32-bit word to find the log base 2 of
    unsigned int r = 0; // r will be lg(v)

    while (v >>= 1) // unroll for more speed...
    {
        r++;
    }
    
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
    
    return 0;
}