#include <stdio.h>
#include <stdarg.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define __COUNT_ARGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _n, X...) _n
#define COUNT_ARGS(X...) __COUNT_ARGS(, ##X, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define test(...) __test(COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)

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

void __test(int len, ...)
{
    int a, b, c;
    va_list ap;

    va_start(ap, len);
    a = va_arg(ap, int);
    
    if(len > 1)
        b = va_arg(ap, int);
    
    if(len > 2)
        c = va_arg(ap, int);
    
    va_end(ap);

    if(len == 2)
        test2(a, b);
    else if(len == 3)
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