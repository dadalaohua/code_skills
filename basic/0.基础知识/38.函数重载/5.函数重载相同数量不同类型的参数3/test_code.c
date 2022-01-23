#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

void test1(int a)
{
    printf("test1 %d\n", a);
}

void test2(float a)
{
    printf("test2 %f\n", a);
}

#define test(a) __builtin_choose_expr(__builtin_types_compatible_p(typeof(a), int), test1(a), \
                    __builtin_choose_expr(__builtin_types_compatible_p(typeof(a), float), test2(a), (void *)0))
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a;
    float x;
    
    a = 10;
    test(a);
    
    x = 112.34;
    test(x);
    
    return 0;
}