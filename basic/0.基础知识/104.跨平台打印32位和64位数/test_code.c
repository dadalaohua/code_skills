#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int8_t i8_val = INT8_MAX;
    uint8_t u8_val = UINT8_MAX;
    int16_t i16_val = INT16_MAX;
    uint16_t u16_val = UINT16_MAX;
    int32_t i32_val = INT32_MAX;
    uint32_t u32_val = UINT32_MAX;
    int64_t i64_val = INT64_MAX;
    uint64_t u64_val = UINT64_MAX;
    
    printf("a = %" PRId8 "\n", i8_val);     //有符号
    printf("b = %" PRIu8 "\n", u8_val);     //无符号
    printf("c = 0x%" PRIx8 "\n", u8_val);   //16进制
    printf("d = 0x%" PRIX8 "\n", u8_val);   //大写16进制
    printf("e = 0%" PRIo8 "\n", u8_val);    //8进制
    printf("\n");
    
    printf("a = %" PRId16 "\n", i16_val);
    printf("b = %" PRIu16 "\n", u16_val);
    printf("c = 0x%" PRIx16 "\n", u16_val);
    printf("d = 0x%" PRIX16 "\n", u16_val);
    printf("e = 0%" PRIo16 "\n", u16_val);
    printf("\n");
    
    printf("a = %" PRId32 "\n", i32_val);
    printf("b = %" PRIu32 "\n", u32_val);
    printf("c = 0x%" PRIx32 "\n", u32_val);
    printf("d = 0x%" PRIX32 "\n", u32_val);
    printf("e = 0%" PRIo32 "\n", u32_val);
    printf("\n");
    
    printf("a = %" PRId64 "\n", i64_val);
    printf("b = %" PRIu64 "\n", u64_val);
    printf("c = 0x%" PRIx64 "\n", u64_val);
    printf("d = 0x%" PRIX64 "\n", u64_val);
    printf("e = 0%" PRIo64 "\n", u64_val);
    printf("\n");
    
    printf("PRId64 = %s\n", PRId64);
    printf("PRIu64 = %s\n", PRIu64);
    printf("\n");
    
    return 0;
}