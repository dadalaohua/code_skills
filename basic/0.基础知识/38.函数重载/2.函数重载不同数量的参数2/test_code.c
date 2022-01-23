#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include "test_code.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
void test1(int a)
{
    printf("test1 %d\n", a);
}

void test2(int a, int b)
{
    printf("test2 %d %d\n", a, b);
}

void test3(int a, int b, int c)
{
    printf("test3 %d %d %d\n", a, b, c);
}

void __test(int len, int a, ...)
{
    int b, c;
    va_list ap;

    va_start(ap, a);
    
    if(len >= 1)
        b = va_arg(ap, int);
    
    if(len >= 2)
        c = va_arg(ap, int);
    
    va_end(ap);

    if(len == 1)
        test2(a, b);
    else if(len == 2)
        test3(a, b, c);
    else
        test1(a);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    test(8);
    test(1, 2);
    test(66, 88, 99);
    return 0;
}