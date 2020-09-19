#include <stdio.h>
/*
__attribute__((noinline)) function attribute

This function attribute suppresses the inlining of a function at the call points of the function.
声明为非内联函数

*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
int fn(void) __attribute__((noinline));

int fn(void)
{
    return 66;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    printf("val:%d\n", fn());

    return 0;
}