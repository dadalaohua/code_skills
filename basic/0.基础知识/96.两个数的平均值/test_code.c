#include <stdio.h>
#include <limits.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//基础方式，会有溢出的问题
unsigned int average0(unsigned int a, unsigned int b) {
    return (a + b) / 2;
}

unsigned int average1(unsigned int a, unsigned int b) {
    return a > b ? (b + (a - b) / 2) : (a + (b - a) / 2);
}

unsigned int average2(unsigned int a, unsigned int b) {
    return (a / 2) + (b / 2) + (a & b & 1);
}

unsigned int average3(unsigned int a, unsigned int b) {
    return (a & b) + (a ^ b) / 2;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int a = 100, b = 50;
    printf("( %u + %u ) / 2 = %u \n", a, b, average0(a, b));
    printf("( %u + %u ) / 2 = %u \n", a, b, average1(a, b));
    printf("( %u + %u ) / 2 = %u \n", a, b, average2(a, b));
    printf("( %u + %u ) / 2 = %u \n", a, b, average3(a, b));
    
    a = UINT_MAX, b = 1;
    printf("( %u + %u ) / 2 = %u \n", a, b, average0(a, b));//计算错误，会溢出
    printf("( %u + %u ) / 2 = %u \n", a, b, average1(a, b));
    printf("( %u + %u ) / 2 = %u \n", a, b, average2(a, b));
    printf("( %u + %u ) / 2 = %u \n", a, b, average3(a, b));
    
    a = 2, b = UINT_MAX;
    printf("( %u + %u ) / 2 = %u \n", a, b, average0(a, b));//计算错误，会溢出
    printf("( %u + %u ) / 2 = %u \n", a, b, average1(a, b));
    printf("( %u + %u ) / 2 = %u \n", a, b, average2(a, b));
    printf("( %u + %u ) / 2 = %u \n", a, b, average3(a, b));
    
    return 0;
}