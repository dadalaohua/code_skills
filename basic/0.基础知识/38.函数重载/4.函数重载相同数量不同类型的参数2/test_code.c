#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

void test1(void * a, void * b)
{
    printf("test1 %d %d\n", *(int *)a, *(int *)b);
}

void test2(void * a, void * b)
{
    printf("test2 %f %f\n", *(float *)a, *(float *)b);
}

typedef void (* testfunc)(void *, void *);

void test(testfunc p, void * a, void * b) {
    p(a, b);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a,b;
    float x,y;
    
    a = 10;
    b = 20;
    test(test1, &a, &b);
    
    x = 112.34;
    y = 66.88;
    test(test2, &x, &y);
    
    return 0;
}