#include <stdio.h>
/*
__attribute__((pure)) function attribute

Many functions have no effects except to return a value, and their return value depends only on the parameters and global variables. Functions of this kind can be subject to data flow analysis and might be eliminated.
Note
This function attribute is a GNU compiler extension that the ARM compiler supports.
Although related, this function attribute is not equivalent to the __pure keyword. The function attribute equivalent to __pure is __attribute__((const)).

*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
int Function_Attributes_pure_0(int b) __attribute__((pure));

//The call to Function_Attributes_pure_0 in this example might be eliminated because its result is not used.
int Function_Attributes_pure_0(int b)
{
    return b++;
}

int foo(int b)
{
    int aLocal=0;
    aLocal += Function_Attributes_pure_0(b);
    aLocal += Function_Attributes_pure_0(b);
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    printf("val:%d\n", foo(10));

    return 0;
}