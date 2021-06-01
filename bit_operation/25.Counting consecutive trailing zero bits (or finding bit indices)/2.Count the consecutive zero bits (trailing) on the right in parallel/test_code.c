#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int count_the_consecutive_zero_bits_trailing(unsigned int v)
{
    // unsigned int v;      // 32-bit word input to count zero bits on right
    unsigned int c = 32; // c will be the number of zero bits on the right
    v &= -(v);//v &= -signed(v);
    if (v) c--;
    if (v & 0x0000FFFF) c -= 16;
    if (v & 0x00FF00FF) c -= 8;
    if (v & 0x0F0F0F0F) c -= 4;
    if (v & 0x33333333) c -= 2;
    if (v & 0x55555555) c -= 1;

    return c;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;
    
    for(i = 0; i < 0xff; i++)
    {
        printf("0x%x %d\n", i, count_the_consecutive_zero_bits_trailing(i));
    }
    
    return 0;
}