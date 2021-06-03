#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define haszero(v) (((v) - 0x01010101UL) & ~(v) & 0x80808080UL)

#define hasvalue(x,n) \
(haszero((x) ^ (~0UL/255 * (n))))

bool determine_if_a_word_has_a_byte_equal_to_n(unsigned int x, unsigned char n)
{
    return hasvalue(x,n);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int x1 = 0x12345678;
    unsigned int x2 = 0x88888888;
    unsigned int x3 = 0x00ffffff;
    
    printf("Determine if a word has a byte equal to n %d\n", determine_if_a_word_has_a_byte_equal_to_n(x1, 0x56));
    printf("Determine if a word has a byte equal to n %d\n", determine_if_a_word_has_a_byte_equal_to_n(x2, 0x88));
    printf("Determine if a word has a byte equal to n %d\n", determine_if_a_word_has_a_byte_equal_to_n(x3, 0x88));
    printf("\n");
    
    return 0;
}