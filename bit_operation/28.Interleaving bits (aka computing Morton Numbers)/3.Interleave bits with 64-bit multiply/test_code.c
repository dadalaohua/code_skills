#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int interleave_bits(unsigned short x, unsigned short y)
{
    // unsigned char x;  // Interleave bits of (8-bit) x and y, so that all of the
    // unsigned char y;  // bits of x are in the even positions and y in the odd;
    unsigned short z; // z gets the resulting 16-bit Morton Number.

    z = (((x * 0x0101010101010101ULL & 0x8040201008040201ULL) * 
         0x0102040810204081ULL >> 49) & 0x5555) |
        (((y * 0x0101010101010101ULL & 0x8040201008040201ULL) * 
         0x0102040810204081ULL >> 48) & 0xAAAA);
    
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