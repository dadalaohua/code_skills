#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct
{
    int a;
    short b;
    long c;
    float d;
    char buf[10];
} test_struct;

test_struct foo(void)
{
    test_struct test;
    int i;
    
    test.a = 10;
    test.b = 20;
    test.c = 30;
    test.d = 66.666;
    
    for(i = 0; i < 10; i++)
        test.buf[i] = i + 10;
    
    return test;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    test_struct test_hello = foo();
    test_struct test_hello2;
    int i;
    
    printf("test.a %d\n",  test_hello.a);
    printf("test.b %d\n",  test_hello.b);
    printf("test.c %ld\n", test_hello.c);
    printf("test.d %f\n",  test_hello.d);
    
    for(i = 0; i < 10; i++)
        printf("test.buf[%d] %d\n", i, test_hello.buf[i]);
    
    test_hello2 = foo();
    
    printf("test.a %d\n",  test_hello2.a);
    printf("test.b %d\n",  test_hello2.b);
    printf("test.c %ld\n", test_hello2.c);
    printf("test.d %f\n",  test_hello2.d);
    
    for(i = 0; i < 10; i++)
        printf("test.buf[%d] %d\n", i, test_hello2.buf[i]);
    
    return 0;
}