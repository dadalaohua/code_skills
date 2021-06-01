#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int count_the_consecutive_zero_bits_trailing(unsigned int v)
{
    // unsigned int v;  // find the number of trailing zeros in 32-bit v 
    int r;           // result goes here
    static const int MultiplyDeBruijnBitPosition[32] = 
    {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    r = MultiplyDeBruijnBitPosition[((unsigned int)((v & -v) * 0x077CB531U)) >> 27];

    return r;
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