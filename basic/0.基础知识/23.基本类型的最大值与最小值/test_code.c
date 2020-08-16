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
#define USHRT_MAX	((u16)(~0U))
#define SHRT_MAX	((s16)(USHRT_MAX>>1))
#define SHRT_MIN	((s16)(-SHRT_MAX - 1))
#define INT_MAX		((int)(~0U>>1))
#define INT_MIN		(-INT_MAX - 1)
#define UINT_MAX	(~0U)
#define LONG_MAX	((long)(~0UL>>1))
#define LONG_MIN	(-LONG_MAX - 1)
#define ULONG_MAX	(~0UL)
#define LLONG_MAX	((long long)(~0ULL>>1))
#define LLONG_MIN	(-LLONG_MAX - 1)
#define ULLONG_MAX	(~0ULL)
#define SIZE_MAX	(~(size_t)0)

#define U8_MAX		((u8)~0U)
#define S8_MAX		((s8)(U8_MAX>>1))
#define S8_MIN		((s8)(-S8_MAX - 1))
#define U16_MAX		((u16)~0U)
#define S16_MAX		((s16)(U16_MAX>>1))
#define S16_MIN		((s16)(-S16_MAX - 1))
#define U32_MAX		((u32)~0U)
#define S32_MAX		((s32)(U32_MAX>>1))
#define S32_MIN		((s32)(-S32_MAX - 1))
#define U64_MAX		((u64)~0ULL)
#define S64_MAX		((s64)(U64_MAX>>1))
#define S64_MIN		((s64)(-S64_MAX - 1))

/****************************/

int main(int argc, char* argv[])
{
    printf("USHRT_MAX   %u\n", USHRT_MAX );
    printf("SHRT_MAX    %d\n", SHRT_MAX  );
    printf("SHRT_MIN    %d\n", SHRT_MIN  );
    printf("INT_MAX     %d\n", INT_MAX   );
    printf("INT_MIN     %d\n", INT_MIN   );
    printf("UINT_MAX    %u\n", UINT_MAX  );
    printf("LONG_MAX    %ld\n", LONG_MAX  );
    printf("LONG_MIN    %ld\n", LONG_MIN  );
    printf("ULONG_MAX   %lu\n", ULONG_MAX );
    printf("LLONG_MAX   %lld\n", LLONG_MAX );
    printf("LLONG_MIN   %lld\n", LLONG_MIN );
    printf("ULLONG_MAX  %llu\n", ULLONG_MAX);
    printf("SIZE_MAX    %u\n", SIZE_MAX  );
    
    printf("U8_MAX      %u\n", U8_MAX  );
    printf("S8_MAX      %d\n", S8_MAX  );
    printf("S8_MIN      %d\n", S8_MIN  );
    printf("U16_MAX     %u\n", U16_MAX );
    printf("S16_MAX     %d\n", S16_MAX );
    printf("S16_MIN     %d\n", S16_MIN );
    printf("U32_MAX     %u\n", U32_MAX );
    printf("S32_MAX     %d\n", S32_MAX );
    printf("S32_MIN     %d\n", S32_MIN );
    printf("U64_MAX     %llu\n", U64_MAX );
    printf("S64_MAX     %lld\n", S64_MAX );
    printf("S64_MIN     %lld\n", S64_MIN );
    
    return 0;
}