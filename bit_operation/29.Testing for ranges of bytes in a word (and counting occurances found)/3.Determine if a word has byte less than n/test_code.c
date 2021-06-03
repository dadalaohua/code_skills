#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//Requirements: x>=0; 0<=n<=128
#define hasless(x,n) (((x)-~0UL/255*(n))&~(x)&~0UL/255*128)

//To count the number of bytes in x that are less than n
#define countless(x,n) \
(((~0UL/255*(127+(n))-((x)&~0UL/255*127))&~(x)&~0UL/255*128)/128%255)

bool determine_if_a_word_has_a_byte_less_than_n(unsigned int x, unsigned char n)
{
    return hasless(x,n);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int x1 = 0x12345678;
    unsigned int x2 = 0x88888888;
    unsigned int x3 = 0x00ffffff;
    
    printf("Determine if a word has a byte less than n %d\n", determine_if_a_word_has_a_byte_less_than_n(x1, 0x56));
    printf("Determine if a word has a byte less than n %d\n", determine_if_a_word_has_a_byte_less_than_n(x2, 0x78));
    printf("Determine if a word has a byte less than n %d\n", determine_if_a_word_has_a_byte_less_than_n(x3, 0x20));
    printf("\n");
    
    printf("Determine if a word has a byte less than n %ld\n", countless(x1, 0x56));
    printf("Determine if a word has a byte less than n %ld\n", countless(x2, 0x78));
    printf("Determine if a word has a byte less than n %ld\n", countless(x3, 0x20));
    printf("\n");
    
    return 0;
}