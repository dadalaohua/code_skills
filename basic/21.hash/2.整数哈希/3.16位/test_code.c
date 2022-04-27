#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//https://github.com/skeeto/hash-prospector
// 2-round xorshift-multiply (-Xn2)
// bias = 0.0085905051336723701
uint16_t hash16_xm2(uint16_t x)
{
    x ^= x >> 8; x *= 0x88b5U;
    x ^= x >> 7; x *= 0xdb2dU;
    x ^= x >> 9;
    return x;
}

// 3-round xorshift-multiply (-Xn3)
// bias = 0.0045976709018820602
uint16_t hash16_xm3(uint16_t x)
{
    x ^= x >>  7; x *= 0x2993U;
    x ^= x >>  5; x *= 0xe877U;
    x ^= x >>  9; x *= 0x0235U;
    x ^= x >> 10;
    return x;
}

// No multiplication (-Imn6)
// bias = 0.023840118344741465
uint16_t hash16_s6(uint16_t x)
{
    x += x << 7; x ^= x >> 8;
    x += x << 3; x ^= x >> 2;
    x += x << 4; x ^= x >> 8;
    return x;
}

// Which is identical to this xorshift-multiply
// uint16_t hash16_s6(uint16_t x)
// {
    // x *= 0x0081U; x ^= x >> 8;
    // x *= 0x0009U; x ^= x >> 2;
    // x *= 0x0011U; x ^= x >> 8;
    // return x;
// }
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    //hash16_xm2
    printf("hash16_xm2:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %5u %04x %3d\n", i, hash16_xm2(i), hash16_xm2(i), hash16_xm2(i)%100);
    }
    printf("\n");
    
    //hash16_xm3
    printf("lhash16_xm3:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %5u %04x %3d\n", i, hash16_xm3(i), hash16_xm3(i), hash16_xm3(i)%100);
    }
    printf("\n");
    
    //hash16_s6
    printf("hash16_s6:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %5u %04x %3d\n", i, hash16_s6(i), hash16_s6(i), hash16_s6(i)%100);
    }
    printf("\n");
    
    return 0;
}