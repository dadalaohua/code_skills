#include <stdio.h>
/*
__attribute__((noinline)) function attribute

This function attribute indicates that a function must be inlined.
The compiler attempts to inline the function, regardless of the characteristics of the function.
In some circumstances the compiler may choose to ignore the __attribute__((always_inline)) attribute and not inline a function. For example:
A recursive function is never inlined into itself.
Functions making use of alloca() are never inlined.

总是内联
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
static int max(int x, int y) __attribute__((always_inline));

static int max(int x, int y)
{
    return x > y ? x : y; // always inline if possible
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    printf("val:%d\n", max(10, 16));

    return 0;
}