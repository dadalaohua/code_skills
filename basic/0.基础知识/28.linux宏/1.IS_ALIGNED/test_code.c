#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    https://elixir.bootlin.com/linux/v3.10.108/source/include/linux/kernel.h
*/

#define IS_ALIGNED(x, a)		(((x) & ((typeof(x))(a) - 1)) == 0)

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("%d\n", IS_ALIGNED(0x80000, 1 << 12));
    // printf("%d\n", IS_ALIGNED(0x1000, 1 << 12));
    // printf("%d\n", IS_ALIGNED(0x1002, 1 << 12));
    printf("%d\n", IS_ALIGNED(512, 256));
    //printf("%d\n", IS_ALIGNED(1024, 256));
    printf("%d\n", IS_ALIGNED(500, 256));
    return 0;
}