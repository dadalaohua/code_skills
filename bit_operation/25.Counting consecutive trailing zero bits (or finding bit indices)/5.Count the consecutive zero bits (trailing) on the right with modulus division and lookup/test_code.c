#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int count_the_consecutive_zero_bits_trailing(unsigned int v)
{
    // unsigned int v;  // find the number of trailing zeros in v
    int r;           // put the result in r
    static const int Mod37BitPosition[] = // map a bit value mod 37 to its position
    {
        32, 0, 1, 26, 2, 23, 27, 0, 3, 16, 24, 30, 28, 11, 0, 13, 4,
        7, 17, 0, 25, 22, 31, 15, 29, 10, 12, 6, 0, 21, 14, 9, 5,
        20, 8, 19, 18
    };
    r = Mod37BitPosition[(-v & v) % 37];

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