#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int Merge_bits(unsigned int non_masked_val, unsigned int masked_val, unsigned int mask)
{
    return non_masked_val ^ ((non_masked_val ^ masked_val) & mask);
}

unsigned int Merge_bits_2(unsigned int non_masked_val, unsigned int masked_val, unsigned int mask)
{
    return (non_masked_val & ~mask) | (masked_val & mask);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int a = 0x7AC34B64;
    unsigned int b = 0x98BF537A;
    unsigned int mask = 0x0000FFFF;
    
    printf("a 0x%x b 0x%x mask 0x%x\n", a, b, mask);
    printf("val 0x%x\n", Merge_bits(a, b, mask));
    printf("val 0x%x\n", Merge_bits_2(a, b, mask));
    
    return 0;
}