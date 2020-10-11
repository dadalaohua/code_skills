#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int modulus_division(unsigned int denominator, unsigned int numerator)
{
    unsigned int m;
    
    m = denominator & (numerator - 1);
    
    return m;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int n = 13;
    unsigned int d = 1U << 3;
    
    printf("%d %% %d = %d\n", n, d, modulus_division(n, d));
    
    return 0;
}