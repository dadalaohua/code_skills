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
bool computing_parity(unsigned char val)
{
    return (((val * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char val1 = 0x25; //‭3bit 00100101‬
    unsigned char val2 = 0x27; //‭4bit ‭00100111‬
    
    printf("0x%x is an %s number of bits set\n", val1, computing_parity(val1) ? "odd" : "even");
    printf("0x%x is an %s number of bits set\n", val2, computing_parity(val2) ? "odd" : "even");
    
    return 0;
}