#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

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
    printf("SIZE_MAX    %zu\n", SIZE_MAX  );
    printf("SSIZE_MAX    %zd\n", SSIZE_MAX  );
    
    printf("UINT8_MAX   %u\n", UINT8_MAX  );
    printf("INT8_MAX    %d\n", INT8_MAX  );
    printf("INT8_MIN    %d\n", INT8_MIN  );
    printf("UINT16_MAX  %u\n", UINT16_MAX );
    printf("INT16_MAX   %d\n", INT16_MAX );
    printf("INT16_MIN   %d\n", INT16_MIN );
    printf("UINT32_MAX  %" PRIu32 "\n", UINT32_MAX );
    printf("INT32_MAX   %" PRId32 "\n", INT32_MAX );
    printf("INT32_MIN   %" PRId32 "\n", INT32_MIN );
    printf("UINT64_MAX  %" PRIu64 "\n", UINT64_MAX );
    printf("INT64_MAX   %" PRId64 "\n", INT64_MAX );
    printf("INT64_MIN   %" PRId64 "\n", INT64_MIN );
    
    return 0;
}