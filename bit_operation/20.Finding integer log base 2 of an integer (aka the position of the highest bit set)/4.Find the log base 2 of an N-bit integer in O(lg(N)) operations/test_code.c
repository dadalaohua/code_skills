#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//以2为底取对数函数log2(v)
unsigned int bit_log2(unsigned int v)
{
    //unsigned int v;  // 32-bit value to find the log2 of 
    const unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
    const unsigned int S[] = {1, 2, 4, 8, 16};
    int i;

    register unsigned int r = 0; // result of log2(v) will go here
    for (i = 4; i >= 0; i--) // unroll for speed...
    {
        if (v & b[i])
        {
            v >>= S[i];
            r |= S[i];
        }
    }

    return r;
}

unsigned int bit_log2_2(unsigned int v)
{
    // OR (IF YOUR CPU BRANCHES SLOWLY):

    //unsigned int v;            // 32-bit value to find the log2 of 
    register unsigned int r; // result of log2(v) will go here
    register unsigned int shift;

    r =     (v > 0xFFFF) << 4; v >>= r;
    shift = (v > 0xFF  ) << 3; v >>= shift; r |= shift;
    shift = (v > 0xF   ) << 2; v >>= shift; r |= shift;
    shift = (v > 0x3   ) << 1; v >>= shift; r |= shift;
                                            r |= (v >> 1);

    return r;
}

//如果你知道 v 是 2 的幂，可以使用该方式
//如果不是的话，会出错
unsigned int bit_log2_3(unsigned int v)
{
    // OR (IF YOU KNOW v IS A POWER OF 2):

    // unsigned int v;  // 32-bit value to find the log2 of 
    static const unsigned int b[] = {0xAAAAAAAA, 0xCCCCCCCC, 0xF0F0F0F0, 
                                     0xFF00FF00, 0xFFFF0000};
    register unsigned int r = (v & b[0]) != 0;
    int i;
    
    for (i = 4; i > 0; i--) // unroll for speed...
    {
        r |= ((v & b[i]) != 0) << i;
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
    
    for(i = 0; i < 65; i++)
    {
        printf("%d %d\n", i, bit_log2_2(i));
    }
    
    for(i = 0; i < 65; i++)
    {
        printf("%d %d\n", i, bit_log2_3(i));
    }
    
    return 0;
}