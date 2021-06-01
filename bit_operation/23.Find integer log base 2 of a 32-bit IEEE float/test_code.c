#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//以2为底取对数函数log2(v)
int bit_log2(float v)
{
    //const float v; // find int(log2(v)), where v > 0.0 && finite(v) && isnormal(v)
    int c;         // 32-bit int c gets the result;

    c = *(const int *) &v;  // OR, for portability:  memcpy(&c, &v, sizeof c);
    c = (c >> 23) - 127;
    
    return c;
}

static const char LogTable256[256] = 
{
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
    LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};

int bit_log2_2(float v)
{
    //const float v;              // find int(log2(v)), where v > 0.0 && finite(v)
    int c;                      // 32-bit int c gets the result;
    int x = *(const int *) &v;  // OR, for portability:  memcpy(&x, &v, sizeof x);

    c = x >> 23;

    if (c)
    {
        c -= 127;
    }
    else
    {   // subnormal, so recompute using mantissa: c = intlog2(x) - 149;
        register unsigned int t; // temporary
        // Note that LogTable256 was defined earlier
        if ((t = x >> 16))
        {
            c = LogTable256[t] - 133;
        }
        else
        {
            c = (t = x >> 8) ? LogTable256[t] - 141 : LogTable256[x] - 149;
        }
    }
    
    return c;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    float i;

    for(i = 0; i < 65; i+= 0.8)
    {
        printf("%f %d\n", i, bit_log2(i));
    }
    
    for(i = 0; i < 65; i+= 0.8)
    {
        printf("%f %d\n", i, bit_log2_2(i));
    }
    
    return 0;
}