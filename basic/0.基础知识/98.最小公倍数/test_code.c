#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
// greatest common divisor 最大公约数
// 辗转相除法
unsigned int gcd(unsigned int a, unsigned int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// least common multiple 最小公倍数
unsigned int lcm(unsigned int a, unsigned int b) {
    return a * b / gcd(a, b);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a, b;
    
    a = 9, b = 6;
    printf("a %d b %d gcd %d\n", a, b, lcm(a, b));
    
    a = 19, b = 17;
    printf("a %d b %d gcd %d\n", a, b, lcm(a, b));
    
    a = 123, b = 369;
    printf("a %d b %d gcd %d\n", a, b, lcm(a, b));
    
    return 0;
}
