#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int round_up_to_the_next_highest_power_of_2_by_float_casting(unsigned int v)
{
    // unsigned int const v; // Round this 32-bit value to the next highest power of 2
    unsigned int r;       // Put the result here. (So v=3 -> r=4; v=8 -> r=8)

    if (v > 1) 
    {
        float f = (float)v;
        unsigned int const t = 1U << ((*(unsigned int *)&f >> 23) - 0x7f);
        r = t << (t < v);
    }
    else 
    {
        r = 1;
    }
    
    return r;
}

unsigned int round_up_to_the_next_highest_power_of_2_by_float_casting_2(unsigned int v)
{
    // unsigned int const v; // Round this 32-bit value to the next highest power of 2
    unsigned int r;       // Put the result here. (So v=3 -> r=4; v=8 -> r=8)

    if (v > 1) 
    {
        float f = (float)(v - 1);  
        r = 1U << ((*(unsigned int*)(&f) >> 23) - 126);
    }
    else 
    {
        r = 1;
    }
    
    return r;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;
    
    for(i = 0; i < 65; i++)
        printf("%d %d\n", i, round_up_to_the_next_highest_power_of_2_by_float_casting(i));
    
    for(i = 0; i < 65; i++)
        printf("%d %d\n", i, round_up_to_the_next_highest_power_of_2_by_float_casting_2(i));

    return 0;
}