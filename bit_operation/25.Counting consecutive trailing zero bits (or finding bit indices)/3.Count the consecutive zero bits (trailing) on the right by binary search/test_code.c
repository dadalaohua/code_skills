#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int count_the_consecutive_zero_bits_trailing(unsigned int v)
{
    // unsigned int v;     // 32-bit word input to count zero bits on right
    unsigned int c;     // c will be the number of zero bits on the right,
                        // so if v is 1101000 (base 2), then c will be 3
    // NOTE: if 0 == v, then c = 31.
    if (v & 0x1) 
    {
        // special case for odd v (assumed to happen half of the time)
        c = 0;
    }
    else
    {
        c = 1;
        if ((v & 0xffff) == 0) 
        {
            v >>= 16;  
            c += 16;
        }
        if ((v & 0xff) == 0) 
        {
            v >>= 8;  
            c += 8;
        }
        if ((v & 0xf) == 0) 
        {
            v >>= 4;
            c += 4;
        }
        if ((v & 0x3) == 0) 
        {
            v >>= 2;
            c += 2;
        }
        c -= v & 0x1;
    }

    return c;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;
    
    for(i = 0; i < 0xff; i++)
        printf("0x%x %d\n", i, count_the_consecutive_zero_bits_trailing(i));
    
    return 0;
}