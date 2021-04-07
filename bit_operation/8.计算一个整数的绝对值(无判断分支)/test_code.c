#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CHAR_BIT 8

unsigned int bitabs(int val)
{
    unsigned int result;
    int const mask = val >> (sizeof(int) * CHAR_BIT - 1);

    result = (val + mask) ^ mask;

    return result;
}

//Negative absolute value
unsigned int bitnabs(int val)
{
    unsigned int result;
    int const mask = val >> (sizeof(int) * CHAR_BIT - 1);

    result = (mask - val) ^ mask;

    return result;
}

unsigned int bitabs2(int val)
{
    unsigned int result;
    int const mask = val >> (sizeof(int) * CHAR_BIT - 1);

    result = (val ^ mask) - mask;

    return result;
}

unsigned int bitnabs2(int val)
{
    unsigned int result;
    int const mask = val >> (sizeof(int) * CHAR_BIT - 1);

    result = mask - (val ^ mask);

    return result;
}

unsigned int bitabs3(int val)
{
    unsigned int result;
    int const mask = val >> (sizeof(int) * CHAR_BIT - 1);

    result = val - ((val + val) & mask);

    return result;
}

unsigned int bitnabs3(int val)
{
    unsigned int result;
    int const mask = val >> (sizeof(int) * CHAR_BIT - 1);

    result = ((val + val) & mask) - val;

    return result;
}

unsigned int bitabs4(int val)
{
    unsigned int result;
    int const mask = val >> (sizeof(int) * CHAR_BIT - 1);

    result = val - ((val << 1) & mask);

    return result;
}

unsigned int bitnabs4(int val)
{
    unsigned int result;
    int const mask = val >> (sizeof(int) * CHAR_BIT - 1);

    result = ((val << 1) & mask) - val;

    return result;
}

unsigned int bitabs5(int val)
{
    unsigned int result;

    result = ((val >> 30) | 1) * val;

    return result;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("bitabs %d \n", bitabs(85));
    printf("bitabs %d \n", bitabs(-85));
    
    printf("bitabs %d %d \n", 0x80000000, bitabs(0x80000000));
    printf("bitabs %d %d \n", 0x80000001, bitabs(0x80000001));
    
    printf("bitnabs %d \n", bitnabs(85));
    printf("bitnabs %d \n", bitnabs(-85));
    
    printf("bitnabs %d \n", bitnabs(0));
    printf("bitnabs %d \n", bitnabs(1));
    printf("bitnabs %d \n", bitnabs(-1));
    
    printf("bitnabs %d %d \n", 0x80000000, bitnabs(0x80000000));
    printf("bitnabs %d %d \n", 0x80000001, bitnabs(0x80000001));
    
    printf("bitnabs %d %d \n", 0x7fffffff, bitnabs(0x7fffffff));
    printf("bitnabs %d %d \n", 0x7ffffffe, bitnabs(0x7ffffffe));
    
    printf("bitabs2 %d \n", bitabs2(1));
    printf("bitabs2 %d \n", bitabs2(-1));
    
    printf("bitabs2 %d %d \n", 0x80000000, bitabs2(0x80000000));
    printf("bitabs2 %d %d \n", 0x80000001, bitabs2(0x80000001));
    
    printf("bitnabs2 %d %d \n", 0x80000000, bitnabs2(0x80000000));
    printf("bitnabs2 %d %d \n", 0x80000001, bitnabs2(0x80000001));
    
    printf("bitnabs2 %d %d \n", 0x7fffffff, bitnabs2(0x7fffffff));
    printf("bitnabs2 %d %d \n", 0x7ffffffe, bitnabs2(0x7ffffffe));
    
    printf("bitabs3 %d \n", bitabs3(1));
    printf("bitabs3 %d \n", bitabs3(-1));
    
    printf("bitabs3 %d %d \n", 0x80000000, bitabs3(0x80000000));
    printf("bitabs3 %d %d \n", 0x80000001, bitabs3(0x80000001));
    
    printf("bitnabs3 %d %d \n", 0x80000000, bitnabs3(0x80000000));
    printf("bitnabs3 %d %d \n", 0x80000001, bitnabs3(0x80000001));
    
    printf("bitnabs3 %d %d \n", 0x7fffffff, bitnabs3(0x7fffffff));
    printf("bitnabs3 %d %d \n", 0x7ffffffe, bitnabs3(0x7ffffffe));
    
    printf("bitabs4 %d \n", bitabs4(1));
    printf("bitabs4 %d \n", bitabs4(-1));
    
    printf("bitabs4 %d %d \n", 0x80000000, bitabs4(0x80000000));
    printf("bitabs4 %d %d \n", 0x80000001, bitabs4(0x80000001));
    
    printf("bitnabs4 %d %d \n", 0x80000000, bitnabs4(0x80000000));
    printf("bitnabs4 %d %d \n", 0x80000001, bitnabs4(0x80000001));
    
    printf("bitnabs4 %d %d \n", 0x7fffffff, bitnabs4(0x7fffffff));
    printf("bitnabs4 %d %d \n", 0x7ffffffe, bitnabs4(0x7ffffffe));
    
    printf("bitabs5 %d \n", bitabs5(1));
    printf("bitabs5 %d \n", bitabs5(-1));
    
    printf("bitabs5 %d %d \n", 0x80000000, bitabs5(0x80000000));
    printf("bitabs5 %d %d \n", 0x80000001, bitabs5(0x80000001));
    
    return 0;
}