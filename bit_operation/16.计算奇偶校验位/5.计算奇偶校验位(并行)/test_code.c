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
bool computing_parity_8(unsigned int val)
{
    val ^= val >> 4;
    val &= 0xf;
    return (0x6996 >> val) & 1;
}

bool computing_parity_32(unsigned int val)
{
    val ^= val >> 16;
    val ^= val >> 8;
    val ^= val >> 4;
    val &= 0xf;
    return (0x6996 >> val) & 1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char val1_8 = 0x25; //‭3bit 00100101‬
    unsigned char val2_8 = 0x27; //‭4bit ‭00100111‬
    
    unsigned int val1_32 = 0x315C4E25; //14bit ‭0b00110001010111000100111000100101‬
    unsigned int val2_32 = 0x355C4E25; //15bit 0b‭00110101010111000100111000100101‬
    
    printf("0x%x is an %s number of bits set\n", val1_8, computing_parity_8(val1_8) ? "odd" : "even");
    printf("0x%x is an %s number of bits set\n", val2_8, computing_parity_8(val2_8) ? "odd" : "even");
    
    printf("0x%x is an %s number of bits set\n", val1_32, computing_parity_32(val1_32) ? "odd" : "even");
    printf("0x%x is an %s number of bits set\n", val2_32, computing_parity_32(val2_32) ? "odd" : "even");
    
    return 0;
}