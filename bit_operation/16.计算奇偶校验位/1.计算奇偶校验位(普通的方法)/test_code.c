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
    bool parity = false;

    while (val)
    {
        parity = !parity;
        val = val & (val - 1);
    }
    
    return parity;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int val1 = 0x315C4E25; //14bit ‭0b00110001010111000100111000100101‬
    int val2 = 0x355C4E25; //15bit 0b‭00110101010111000100111000100101‬
    
    printf("0x%x is an %s number of bits set\n", val1, computing_parity(val1) ? "odd" : "even");
    printf("0x%x is an %s number of bits set\n", val2, computing_parity(val2) ? "odd" : "even");
    
    return 0;
}