#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int modulus_division(unsigned int denominator, unsigned int numerator, unsigned int s)
{
    //unsigned int n;                      // numerator
    //                                     // 变量n为分子（被模除的数）
    //const unsigned int s;                // s > 0
    //const unsigned int d = (1 << s) - 1; // so d is either 1, 3, 7, 15, 31, ...).
    //                                     // 那么变量d从小到大依次为:1, 3, 7, 15, 31, ...
    unsigned int m;                      // n % d goes here.
                                         // 保存n%d的结果

    for (m = denominator; denominator > numerator; denominator = m)
    {
        for (m = 0; denominator; denominator >>= s)
        {
            m += denominator & numerator;
        }
    }
    // Now m is a value from 0 to d, but since with modulus division
    // 此时m的值范围时0到d，但由于这里是模除（译者注：所以需要特殊处理m等于d的情况）
    // we want m to be 0 when it is d.
    // 当m的值为d时，我们希望m的值变成0
    m = m == numerator ? 0 : m;
    
    return m;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int n = 13;
    unsigned int s = 3;
    unsigned int d = (1U << s) - 1;
    
    printf("%d %% %d = %d\n", n, d, modulus_division(n, d, s));
    
    return 0;
}