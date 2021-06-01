#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//以2为底取对数函数log2(v)
int bit_log2(int v)
{
    // int v; // 32-bit integer to find the log base 2 of
    int r; // result of log_2(v) goes here
    union { unsigned int u[2]; double d; } t; // temp

    t.u[__FLOAT_WORD_ORDER==LITTLE_ENDIAN] = 0x43300000;
    t.u[__FLOAT_WORD_ORDER!=LITTLE_ENDIAN] = v;
    t.d -= 4503599627370496.0;
    r = (t.u[__FLOAT_WORD_ORDER==LITTLE_ENDIAN] >> 20) - 0x3FF;
    
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