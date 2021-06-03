#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//Requirements: x>=0; 0<=m<=127; 0<=n<=128
#define likelyhasbetween(x,m,n) \
((((x)-~0UL/255*(n))&~(x)&((x)&~0UL/255*127)+~0UL/255*(127-(m)))&~0UL/255*128)

#define hasbetween(x,m,n) \
((~0UL/255*(127+(n))-((x)&~0UL/255*127)&~(x)&((x)&~0UL/255*127)+~0UL/255*(127-(m)))&~0UL/255*128)

#define countbetween(x,m,n) (hasbetween(x,m,n)/128%255)

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int x1 = 0x12345678;
    unsigned int x2 = 0x88888888;
    unsigned int x3 = 0x00ffffff;
    
    printf("Determine if a word has a byte between m and n %d\n", (bool)likelyhasbetween(x1, 0x30, 0x58));
    printf("Determine if a word has a byte between m and n %d\n", (bool)likelyhasbetween(x2, 0x12, 0x78));
    printf("Determine if a word has a byte between m and n %d\n", (bool)likelyhasbetween(x3, 0x00, 0x20));
    printf("\n");
    
    printf("Determine if a word has a byte between m and n %d\n", (bool)hasbetween(x1, 0x30, 0x58));
    printf("Determine if a word has a byte between m and n %d\n", (bool)hasbetween(x2, 0x12, 0x78));
    printf("Determine if a word has a byte between m and n %d\n", (bool)hasbetween(x3, 0x00, 0x20));
    printf("\n");
    
    printf("Determine if a word has a byte between m and n %ld\n", countbetween(x1, 0x30, 0x58));
    printf("Determine if a word has a byte between m and n %ld\n", countbetween(x2, 0x12, 0x78));
    printf("Determine if a word has a byte between m and n %ld\n", countbetween(x3, 0x00, 0x20));
    printf("\n");
    
    return 0;
}