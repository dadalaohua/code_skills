#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned int        u32;
typedef unsigned long long  u64;

/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
 * upper_32_bits - return bits 32-63 of a number
 * @n: the number we're accessing
 *
 * A basic shift-right of a 64- or 32-bit quantity.  Use this to suppress
 * the "right shift count >= width of type" warning when that quantity is
 * 32-bits.
 */
#define upper_32_bits(n) ((u32)(((n) >> 16) >> 16))

/**
 * lower_32_bits - return bits 0-31 of a number
 * @n: the number we're accessing
 */
#define lower_32_bits(n) ((u32)(n))

/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/

int main(int argc, char* argv[])
{
    u64 val64 = 0x5f2b385adcaa1109;
    u32 val32 = 0x5f2b385a;
    
    printf("val64 0x%llx\n", val64);
    printf("val64 upper 32 0x%x\n", upper_32_bits(val64));
    printf("val64 lower 32 0x%x\n", lower_32_bits(val64)); 
    
    printf("val32 0x%x\n", val32);
    printf("val32 upper 32 0x%x\n", upper_32_bits(val32));
    printf("val32 lower 32 0x%x\n", lower_32_bits(val32)); 
    
    return 0;
}