#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned char       __u8;
typedef unsigned short      __u16;
typedef unsigned int        __u32;
typedef unsigned long long  __u64;

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
 * casts are necessary for constants, because we never know how for sure
 * how U/UL/ULL map to __u16, __u32, __u64. At least not in a portable way.
 */
#define ___constant_swab16(x) ((__u16)(				\
	(((__u16)(x) & (__u16)0x00ffU) << 8) |			\
	(((__u16)(x) & (__u16)0xff00U) >> 8)))

#define ___constant_swab32(x) ((__u32)(				\
	(((__u32)(x) & (__u32)0x000000ffUL) << 24) |		\
	(((__u32)(x) & (__u32)0x0000ff00UL) <<  8) |		\
	(((__u32)(x) & (__u32)0x00ff0000UL) >>  8) |		\
	(((__u32)(x) & (__u32)0xff000000UL) >> 24)))

#define ___constant_swab64(x) ((__u64)(				\
	(((__u64)(x) & (__u64)0x00000000000000ffULL) << 56) |	\
	(((__u64)(x) & (__u64)0x000000000000ff00ULL) << 40) |	\
	(((__u64)(x) & (__u64)0x0000000000ff0000ULL) << 24) |	\
	(((__u64)(x) & (__u64)0x00000000ff000000ULL) <<  8) |	\
	(((__u64)(x) & (__u64)0x000000ff00000000ULL) >>  8) |	\
	(((__u64)(x) & (__u64)0x0000ff0000000000ULL) >> 24) |	\
	(((__u64)(x) & (__u64)0x00ff000000000000ULL) >> 40) |	\
	(((__u64)(x) & (__u64)0xff00000000000000ULL) >> 56)))

#define ___constant_swahw32(x) ((__u32)(			\
	(((__u32)(x) & (__u32)0x0000ffffUL) << 16) |		\
	(((__u32)(x) & (__u32)0xffff0000UL) >> 16)))

#define ___constant_swahb32(x) ((__u32)(			\
	(((__u32)(x) & (__u32)0x00ff00ffUL) << 8) |		\
	(((__u32)(x) & (__u32)0xff00ff00UL) >> 8)))
    
/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/

int main(int argc, char* argv[])
{
    __u16 u16val = 0x5f3b;
    __u32 u32val = 0x5f3b3a61;
    __u64 u64val = 0x5f3b3a61a5bc8d92;

    printf("u16val 0x%x\n", u16val);
    printf("swab16 0x%x\n", ___constant_swab16(u16val)); 

    printf("u32val 0x%x\n", u32val);
    printf("swab32 0x%x\n", ___constant_swab32(u32val)); 

    printf("u64val 0x%llx\n", u64val);
    printf("swab64 0x%llx\n", ___constant_swab64(u64val)); 

    printf("u32val 0x%x\n", u32val);
    printf("swahw32 0x%x\n", ___constant_swahw32(u32val));
    
    printf("u32val 0x%x\n", u32val);
    printf("swahb32 0x%x\n", ___constant_swahb32(u32val));
    
    return 0;
}