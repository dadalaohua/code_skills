#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CHAR_BIT 8

unsigned int interleave_bits(unsigned short x, unsigned short y)
{
    // unsigned short x;   // Interleave bits of x and y, so that all of the
    // unsigned short y;   // bits of x are in the even positions and y in the odd;
    unsigned int z = 0; // z gets the resulting Morton Number.

    for (int i = 0; i < sizeof(x) * CHAR_BIT; i++) // unroll for more speed...
    {
        z |= (x & 1U << i) << i | (y & 1U << i) << (i + 1);
    }
    
    return z;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned short x1 = 0xff, y1 = 0x00;
    unsigned short x2 = 0x00, y2 = 0xff;
    unsigned short x3 = 0x5a, y3 = 0x88;
    
    printf("x1 0x%x y1 0x%x interleave 0x%x\n", x1, y1, interleave_bits(x1, y1));
    printf("x2 0x%x y2 0x%x interleave 0x%x\n", x2, y2, interleave_bits(x2, y2));
    printf("x3 0x%x y3 0x%x interleave 0x%x\n", x3, y3, interleave_bits(x3, y3));
    
    return 0;
}