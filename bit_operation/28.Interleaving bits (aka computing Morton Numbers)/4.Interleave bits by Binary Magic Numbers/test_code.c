#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int interleave_bits(unsigned short x, unsigned short y)
{
    static const unsigned int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF};
    static const unsigned int S[] = {1, 2, 4, 8};

    // unsigned int x; // Interleave lower 16 bits of x and y, so the bits of x
    // unsigned int y; // are in the even positions and bits from y in the odd;
    unsigned int z; // z gets the resulting 32-bit Morton Number.  
                    // x and y must initially be less than 65536.

    x = (x | (x << S[3])) & B[3];
    x = (x | (x << S[2])) & B[2];
    x = (x | (x << S[1])) & B[1];
    x = (x | (x << S[0])) & B[0];

    y = (y | (y << S[3])) & B[3];
    y = (y | (y << S[2])) & B[2];
    y = (y | (y << S[1])) & B[1];
    y = (y | (y << S[0])) & B[0];

    z = x | (y << 1);
    
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