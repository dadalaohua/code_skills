#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    https://elixir.bootlin.com/linux/v3.10.108/source/include/linux/bug.h
*/

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

/* Force a compilation error if a constant expression is not a power of 2 */
#define BUILD_BUG_ON_NOT_POWER_OF_2(n)			\
	BUILD_BUG_ON((n) == 0 || (((n) & ((n) - 1)) != 0))

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    BUILD_BUG_ON_NOT_POWER_OF_2(1024);
    BUILD_BUG_ON_NOT_POWER_OF_2(512);
    BUILD_BUG_ON_NOT_POWER_OF_2(256);
    BUILD_BUG_ON_NOT_POWER_OF_2(128);
    BUILD_BUG_ON_NOT_POWER_OF_2(64);
    
    // BUILD_BUG_ON_NOT_POWER_OF_2(0);
    // BUILD_BUG_ON_NOT_POWER_OF_2(100);
    // BUILD_BUG_ON_NOT_POWER_OF_2(164);
    
    return 0;
}