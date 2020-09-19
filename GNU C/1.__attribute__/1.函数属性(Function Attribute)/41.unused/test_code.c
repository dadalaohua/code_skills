#include <stdio.h>

/*
unused：This attribute, attached to a function, means that the function is meant to be possibly unused. GCC will not produce a warning for this function.

表示该函数或变量可能不使用，这个属性可以避免编译器产生警告信息。
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
static int Function_Attributes_unused_0(int b) __attribute__((unused));

static int Function_Attributes_unused_0(int b)
{
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("hello world!!!\n");
    
    return 0;
}