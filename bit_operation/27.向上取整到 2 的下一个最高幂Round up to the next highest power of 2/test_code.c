#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int Round_up_to_the_next_highest_power_of_2(unsigned int v)
{
    //unsigned int v; // compute the next highest power of 2 of 32-bit v

    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    
    return v;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int buf[] = {0, 1, 2, 3, 5, 10, 17, 63, 111, 215, 387, 512, 513, 798};
    int i = 0;
    
    for(i = 0; i < sizeof(buf)/sizeof(int); i++)
    {
        printf("val:%d, next highest power of 2:%d\n", buf[i], Round_up_to_the_next_highest_power_of_2(buf[i]));
    }
    
    return 0;
}