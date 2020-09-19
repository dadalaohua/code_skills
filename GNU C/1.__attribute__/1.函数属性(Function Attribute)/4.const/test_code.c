#include <stdio.h>
/*
__attribute__((const)) function attribute

The const function attribute specifies that a function examines only its arguments, and has no effect except for the return value. That is, the function does not read or modify any global memory.
If a function is known to operate only on its arguments then it can be subject to common sub-expression elimination and loop optimizations.
This attribute is stricter than __attribute__((pure)) because functions are not permitted to read global memory.
*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
// __attribute__((const)) functions do not read or modify any global memory
int my_double(int b) __attribute__((const));

int my_double(int b)
{
    return b*2;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    int i;
    int result;
    
    for (i = 0; i < 10; i++)
    {
       result = my_double(i);
       printf (" i = %d , result = %d \n", i, result);
    }

    return 0;
}