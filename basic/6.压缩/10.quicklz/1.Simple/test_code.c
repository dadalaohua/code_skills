#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "quicklz.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
#if QLZ_STREAMING_BUFFER > 0
    #error Define QLZ_STREAMING_BUFFER to 0 for this demo
#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    qlz_state_compress *state_compress = (qlz_state_compress *)malloc(sizeof(qlz_state_compress));
    qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));
    char original[] = "LZ compression is based on finding repeated strings: Five, six, seven, eight, nine, fifteen, sixteen, seventeen, fifteen, sixteen, seventeen.";

    // Always allocate size + 400 bytes for the destination buffer when compressing.
    char *compressed = (char *)malloc(strlen(original) + 400);
    char *decompressed = (char *)malloc(strlen(original));
    int r;

    r = qlz_compress(original, compressed, strlen(original), state_compress);
    printf("Compressed %d bytes into %d bytes.\n", strlen(original), r);

    r = qlz_decompress(compressed, decompressed, state_decompress);
    printf("Decompressed back to %d bytes.\n", r);

    return 0;
}