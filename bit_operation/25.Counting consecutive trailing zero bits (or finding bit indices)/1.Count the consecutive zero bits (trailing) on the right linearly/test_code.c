#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHAR_BIT 8
/************************************************************************/
/*                                                                      */
/************************************************************************/
int count_the_consecutive_zero_bits_trailing(unsigned int v)
{
    // unsigned int v;  // input to count trailing zero bits
    int c;  // output: c will count v's trailing zero bits,
            // so if v is 1101000 (base 2), then c will be 3
    if (v)
    {
        v = (v ^ (v - 1)) >> 1;  // Set v's trailing 0s to 1s and zero rest
        for (c = 0; v; c++)
        {
            v >>= 1;
        }
    }
    else
    {
        c = CHAR_BIT * sizeof(v);
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