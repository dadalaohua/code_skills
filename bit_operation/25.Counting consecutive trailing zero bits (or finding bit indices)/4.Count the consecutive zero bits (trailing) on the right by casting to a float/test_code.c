#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int count_the_consecutive_zero_bits_trailing(unsigned int v)
{
    // unsigned int v;            // find the number of trailing zeros in v
    int r;                     // the result goes here
    float f = (float)(v & -v); // cast the least significant bit in v to a float
    r = (*(unsigned int *)&f >> 23) - 0x7f;

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