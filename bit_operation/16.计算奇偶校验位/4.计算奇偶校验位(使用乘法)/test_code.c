#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef enum bool{false, true} bool;

/************************************************************************/
/*                                                                      */
/************************************************************************/
//计算奇偶校验
//如果设置了奇数位数，则为1，否则为0
bool computing_parity(unsigned int val)
{
    val ^= val >> 1;
    val ^= val >> 2;
    val = (val & 0x11111111U) * 0x11111111U;
    return (val >> 28) & 1;
}

bool computing_parity_64(unsigned long long val)
{
    val ^= val >> 1;
    val ^= val >> 2;
    val = (val & 0x1111111111111111UL) * 0x1111111111111111UL;
    return (val >> 60) & 1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int val1 = 0x315C4E25; //14bit ‭0b00110001010111000100111000100101‬
    unsigned int val2 = 0x355C4E25; //15bit 0b‭00110101010111000100111000100101‬
    unsigned long long val3 = 0x315C4E25315C4E25;
    unsigned long long val4 = 0x355C4E25355C4E21;
    
    printf("0x%x is an %s number of bits set\n", val1, computing_parity(val1) ? "odd" : "even");
    printf("0x%x is an %s number of bits set\n", val2, computing_parity(val2) ? "odd" : "even");
    
    printf("0x%llx is an %s number of bits set\n", val3, computing_parity_64(val3) ? "odd" : "even");
    printf("0x%llx is an %s number of bits set\n", val4, computing_parity_64(val4) ? "odd" : "even");
    
    return 0;
}