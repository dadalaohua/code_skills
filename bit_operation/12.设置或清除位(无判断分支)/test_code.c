#include <stdio.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int Conditionally_set_or_clear_bits(unsigned int val, unsigned int mask, bool flag)
{
    val ^= (-flag ^ val) & mask;    //if (flag) val |= mask; else val &= ~mask;
    
    return val;
}

unsigned int Conditionally_set_or_clear_bits_2(unsigned int val, unsigned int mask, bool flag)
{
    val = (val & ~mask) | (-flag & mask);    //if (flag) val |= mask; else val &= ~mask;
    
    return val;
}

unsigned int Conditionally_set_or_clear_bits_3(unsigned int val, unsigned int mask, bool flag)
{
    if (flag)
        val |= mask; 
    else
        val &= ~mask;
    
    return val;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int val1 = 0x35;  //0b0011 0101
    unsigned int mask1 = 0xCC; //0b1100 1100
    
    unsigned int val2 = 0x35;  //0b0011 0101
    unsigned int mask2 = 0x24; //0b0010 0100
    
    printf("val: 0x%x mask 0x%x result 0x%x\n", val1, mask1, Conditionally_set_or_clear_bits  (val1, mask1, true));
    printf("val: 0x%x mask 0x%x result 0x%x\n", val1, mask1, Conditionally_set_or_clear_bits_2(val1, mask1, true));
    printf("val: 0x%x mask 0x%x result 0x%x\n", val1, mask1, Conditionally_set_or_clear_bits_3(val1, mask1, true));
    
    printf("val: 0x%x mask 0x%x result 0x%x\n", val2, mask2, Conditionally_set_or_clear_bits  (val2, mask2, false));
    printf("val: 0x%x mask 0x%x result 0x%x\n", val2, mask2, Conditionally_set_or_clear_bits_2(val2, mask2, false));
    printf("val: 0x%x mask 0x%x result 0x%x\n", val2, mask2, Conditionally_set_or_clear_bits_3(val2, mask2, false));
    
    return 0;
}