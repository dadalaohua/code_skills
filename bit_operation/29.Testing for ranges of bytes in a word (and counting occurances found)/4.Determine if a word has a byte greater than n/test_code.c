#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//Requirements: x>=0; 0<=n<=127
#define hasmore(x,n) (((x)+~0UL/255*(127-(n))|(x))&~0UL/255*128)

//To count the number of bytes in x that are more than n
#define countmore(x,n) \
(((((x)&~0UL/255*127)+~0UL/255*(127-(n))|(x))&~0UL/255*128)/128%255)

bool determine_if_a_word_has_a_byte_greater_than_n(unsigned int x, unsigned char n)
{
    return hasmore(x,n);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int x1 = 0x12345678;
    unsigned int x2 = 0x88888888;
    unsigned int x3 = 0x00ffffff;
    
    printf("Determine if a word has a byte greater than n %d\n", determine_if_a_word_has_a_byte_greater_than_n(x1, 0x56));
    printf("Determine if a word has a byte greater than n %d\n", determine_if_a_word_has_a_byte_greater_than_n(x2, 0x78));
    printf("Determine if a word has a byte greater than n %d\n", determine_if_a_word_has_a_byte_greater_than_n(x3, 0x20));
    printf("\n");
    
    printf("Determine if a word has a byte greater than n %ld\n", countmore(x1, 0x56));
    printf("Determine if a word has a byte greater than n %ld\n", countmore(x2, 0x78));
    printf("Determine if a word has a byte greater than n %ld\n", countmore(x3, 0x20));
    printf("\n");
    
    return 0;
}