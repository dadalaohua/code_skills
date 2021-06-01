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
int bit_log2(int v)
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

int bit_log2_2(int v)
{
    //unsigned int v; // 32-bit word to find the log of
    unsigned r;     // r will be lg(v)
    register unsigned int tt; // temporaries

    if ((tt = v >> 24))
    {
        r = 24 + LogTable256[tt];
    }
    else if ((tt = v >> 16))
    {
        r = 16 + LogTable256[tt];
    }
    else if ((tt = v >> 8))
    {
        r = 8 + LogTable256[tt];
    }
    else 
    {
        r = LogTable256[v];
    }
    
    return r;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;

    for(i = 0; i < 65; i++)
    {
        printf("%d %d\n", i, bit_log2(i));
    }
    
    for(i = 0; i < 65; i++)
    {
        printf("%d %d\n", i, bit_log2_2(i));
    }
    
    return 0;
}