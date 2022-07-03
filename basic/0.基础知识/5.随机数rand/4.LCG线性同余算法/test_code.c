#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//LCG（linear congruential generator）线性同余算法

/************************************************************************/
/*                                                                      */
/************************************************************************/
//https://elixir.bootlin.com/linux/latest/source/drivers/net/hamradio/dmascc.c#L260
static unsigned long linuxrand;

unsigned char linux_random(void)
{
    /* See "Numerical Recipes in C", second edition, p. 284 */
    linuxrand = linuxrand * 1664525L + 1013904223L;
    return (unsigned char) (linuxrand >> 24);
}

//Numerical Recipes in C
//C数值算法
unsigned long idum;

uint32_t idum_random(void)
{
    idum = 1664525L * idum + 1013904223L;
    return idum;
}

//glibc
//glibc-2.33/stdlib/random_r.c
//int __random_r (struct random_data *buf, int32_t *result)
//
//output bits of seed in rand()
//bit 30..0
unsigned long glibc_val;

uint32_t glibc_random(void)
{
    glibc_val = ((glibc_val * 1103515245U) + 12345U) & 0x7fffffff;
    return glibc_val;
}

//glibc
//glibc-2.33/stdlib/rand_r.c:
//int rand_r (unsigned int *seed)
//
/* This algorithm is mentioned in the ISO C standard, here extended
   for 32 bits.  */
int
rand_r (unsigned int *seed)
{
  unsigned int next = *seed;
  int result;

  next *= 1103515245;
  next += 12345;
  result = (unsigned int) (next / 65536) % 2048;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  *seed = next;

  return result;
}

unsigned int glibc_seed;

int glibc_rand(void)
{
    return rand_r(&glibc_seed);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("%d\n", RAND_MAX);
    // linuxrand = 123456;
    // for(int i = 0; i < 100; i++)
        // printf("%3d %d\n", i, linux_random());
    printf("\n");
    
    idum = 123456;
    for(int i = 0; i < 100; i++)
        printf("%3d %10u\n", i, idum_random());
    printf("\n");
    
    glibc_val = 123456;
    for(int i = 0; i < 100; i++)
        printf("%3d %10u\n", i, glibc_random());
    printf("\n");
    
    glibc_seed = 123456;
    for(int i = 0; i < 100; i++)
        printf("%3d %10u\n", i, glibc_rand());
    printf("\n");
    
    return 0;
}