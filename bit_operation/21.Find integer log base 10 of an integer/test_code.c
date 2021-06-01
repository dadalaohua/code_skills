#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
static const char LogTable256[256] = 
{
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
    LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};

//以2为底取对数函数log2(v)
int IntegerLogBase2(int v)
{
    //unsigned int v; // 32-bit word to find the log of
    unsigned r;     // r will be lg(v)
    register unsigned int t, tt; // temporaries

    if ((tt = (v >> 16)))
    {
        r = (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
    }
    else 
    {
        r = (t = v >> 8) ? 8 + LogTable256[t] : LogTable256[v];
    }
    
    return r;
}

int bit_log10(unsigned int v)
{
    // unsigned int v; // non-zero 32-bit integer value to compute the log base 10 of 
    int r;          // result goes here
    int t;          // temporary

    static unsigned int const PowersOf10[] = 
        {1, 10, 100, 1000, 10000, 100000,
         1000000, 10000000, 100000000, 1000000000};

    t = (IntegerLogBase2(v) + 1) * 1233 >> 12; // (use a lg2 method from above)
    r = t - (v < PowersOf10[t]);

    return r;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;

    for(i = 0; i < 1200; i+=8)
    {
        printf("%d %d\n", i, bit_log10(i));
    }
    
    return 0;
}