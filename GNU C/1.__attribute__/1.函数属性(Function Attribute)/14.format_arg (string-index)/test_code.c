#include <stdio.h>
#include <stdarg.h>
/*
__attribute__((format_arg(string-index))) function attribute

This attribute specifies that a function takes a format string as an argument. Format strings can contain typed placeholders that are intended to be passed to printf-style functions such as printf(), scanf(), strftime(), or strfmon().
This attribute causes the compiler to perform placeholder type checking on the specified argument when the output of the function is used in calls to a printf-style function.
Note
This function attribute is a GNU compiler extension that the ARM compiler supports. 
Syntax
__attribute__((format_arg(string-index))) 
Where string-index specifies the argument that is the format string argument (starting from one).


*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
// Function used by printf. No format type checking.
char *myFormatText1 (const char *fmt);

// Function used by printf. Format type checking on argument 1.
char *myFormatText2 (const char *fmt) __attribute__((format_arg(1)));

char *myFormatText1 (const char *fmt)
{
    return fmt;
}
char *myFormatText2 (const char *fmt)
{
    return fmt;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a;
    float b;

    a = 5;
    b = 9.099999;

    printf(myFormatText1("Here is an integer: %d\n"), a); // No type checking. Types match anyway.
    printf(myFormatText1("Here is an integer: %d\n"), b); // No type checking. Type mismatch, but no warning                            

    printf(myFormatText2("Here is an integer: %d\n"), a); // Type checking. Types match.
    printf(myFormatText2("Here is an integer: %d\n"), b); // Type checking. Type mismatch results in Warning:  #181-D

    return 0;
}