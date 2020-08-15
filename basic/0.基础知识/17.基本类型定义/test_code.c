#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
typedef signed char         s8;
typedef short               s16;
typedef int                 s32;
typedef long long           s64;

typedef u8  uint8_t;
typedef u16 uint16_t;
typedef u32 uint32_t;
typedef u64 uint64_t;
typedef s8  int8_t;
typedef s16 int16_t;
typedef s32 int32_t;
typedef s64 int64_t;

/************************************************************************/
/*                                                                      */
/************************************************************************/


/****************************/

int main(int argc, char* argv[])
{
    printf("unsigned char      sizeof %d\n", sizeof(unsigned char     ));
    printf("unsigned short     sizeof %d\n", sizeof(unsigned short    ));
    printf("unsigned int       sizeof %d\n", sizeof(unsigned int      ));
    printf("unsigned long long sizeof %d\n", sizeof(unsigned long long));
    
    printf("signed char sizeof %d\n", sizeof(signed char));
    printf("short       sizeof %d\n", sizeof(short      ));
    printf("int         sizeof %d\n", sizeof(int        ));
    printf("long long   sizeof %d\n", sizeof(long long  ));
    
    printf("u8  sizeof %d\n", sizeof(u8));
    printf("u16 sizeof %d\n", sizeof(u16));
    printf("u32 sizeof %d\n", sizeof(u32));
    printf("u64 sizeof %d\n", sizeof(u64));
    
    printf("s8  sizeof %d\n", sizeof(s8));
    printf("s16 sizeof %d\n", sizeof(s16));
    printf("s32 sizeof %d\n", sizeof(s32));
    printf("s64 sizeof %d\n", sizeof(s64));
    
    printf("uint8_t  sizeof %d\n", sizeof(uint8_t));
    printf("uint16_t sizeof %d\n", sizeof(uint16_t));
    printf("uint32_t sizeof %d\n", sizeof(uint32_t));
    printf("uint64_t sizeof %d\n", sizeof(uint64_t));
    
    printf("int8_t  sizeof %d\n", sizeof(int8_t));
    printf("int16_t sizeof %d\n", sizeof(int16_t));
    printf("int32_t sizeof %d\n", sizeof(int32_t));
    printf("int64_t sizeof %d\n", sizeof(int64_t));
    
    return 0;
}