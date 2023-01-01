#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
// greatest common divisor 最大公约数
// 辗转相除法
unsigned int gcd(unsigned int a, unsigned int b) {
    return b == 0 ? a : gcd(b, a % b);
}

unsigned int gcd_2(unsigned int a, unsigned int b) {
    return b ? gcd_2(b, a % b) : a;
}

int gcd_3(int num1, int num2) {
    while (num2 != 0) {
        int temp = num1;
        num1 = num2;
        num2 = temp % num2;
    }
    return num1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a, b;
    
    a = 9, b = 6;
    printf("a %d b %d gcd %d\n", a, b, gcd(a, b));
    printf("a %d b %d gcd %d\n", a, b, gcd_2(a, b));
    printf("a %d b %d gcd %d\n", a, b, gcd_3(a, b));
    
    a = 19, b = 17;
    printf("a %d b %d gcd %d\n", a, b, gcd(a, b));
    printf("a %d b %d gcd %d\n", a, b, gcd_2(a, b));
    printf("a %d b %d gcd %d\n", a, b, gcd_3(a, b));
    
    a = 123, b = 666;
    printf("a %d b %d gcd %d\n", a, b, gcd(a, b));
    printf("a %d b %d gcd %d\n", a, b, gcd_2(a, b));
    printf("a %d b %d gcd %d\n", a, b, gcd_3(a, b));
    
    return 0;
}
