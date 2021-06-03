#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
// Fewer operations:
bool determine_if_a_word_has_a_zero_byte(unsigned int v)
{
    // unsigned int v; // 32-bit word to check if any 8-bit byte in it is 0
    bool hasZeroByte = ~((((v & 0x7F7F7F7F) + 0x7F7F7F7F) | v) | 0x7F7F7F7F);
    
    return hasZeroByte;
}

// More operations:
bool determine_if_a_word_has_a_zero_byte_2(unsigned int v)
{
    bool hasNoZeroByte = ((v & 0xff) && (v & 0xff00) && (v & 0xff0000) && (v & 0xff000000));
    
    return hasNoZeroByte;
}

// More operations:
bool determine_if_a_word_has_a_zero_byte_3(unsigned int v)
{
    // OR:
    unsigned char * p = (unsigned char *) &v;
    bool hasNoZeroByte = *p && *(p + 1) && *(p + 2) && *(p + 3);
    
    return hasNoZeroByte;
}

//如果高字节是0x80，测试也返回true，因此偶尔会出现误报
bool determine_if_a_word_has_a_zero_byte_4(unsigned int v)
{
    bool hasZeroByte = ((v + 0x7efefeff) ^ ~v) & 0x81010100;
    if (hasZeroByte) // or may just have 0x80 in the high byte
    {
        hasZeroByte = ~((((v & 0x7F7F7F7F) + 0x7F7F7F7F) | v) | 0x7F7F7F7F);
    }
    
    return hasZeroByte;
}

//faster method
bool determine_if_a_word_has_a_zero_byte_5(unsigned int v)
{
#define haszero(v) (((v) - 0x01010101UL) & ~(v) & 0x80808080UL)
    
    return haszero(v);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int x1 = 0x55555555;   //没有
    unsigned int x2 = 0x88888888;   //没有
    unsigned int x3 = 0x00ffffff;   //有
    
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte(x1));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte(x2));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte(x3));
    printf("\n");
    
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_2(x1));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_2(x2));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_2(x3));
    printf("\n");
    
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_3(x1));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_3(x2));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_3(x3));
    printf("\n");
    
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_4(x1));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_4(x2));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_4(x3));
    printf("\n");
    
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_5(x1));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_5(x2));
    printf("Determine if a word has a zero byte %d\n", determine_if_a_word_has_a_zero_byte_5(x3));

    return 0;
}