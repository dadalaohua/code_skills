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

void test3(double a)
{
    printf("test3 %f\n", a);
}

void other(void)
{
    printf("other\n");
}

#define test(x) _Generic((x), \
                    int: test1(x), \
                    float: test2(x), \
                    double: test3(x), \
                    default: other())
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a;
    float x;
    double y;
    
    a = 10;
    test(a);
    
    x = 112.34;
    test(x);
    
    y = 66.88;
    test(y);
    
    //不存在的类型
    char c;
    test(c);
    
    return 0;
}