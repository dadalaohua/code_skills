#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "quicklz.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
#if QLZ_STREAMING_BUFFER == 0
    #error Define QLZ_STREAMING_BUFFER to a non-zero value for this demo
#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    qlz_state_compress *state_compress = (qlz_state_compress *)malloc(sizeof(qlz_state_compress));
    qlz_state_decompress *state_decompress = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));

    // Allocate data buffers. 200 and 200 + 400 bytes should be sufficient for our test data packets.
    char *compressed = (char *)malloc(200 + 400);
    char *decompressed = (char *)malloc(200);

    int o = 0;

    // Zero out both states.
    memset(state_compress, 0, sizeof(state_compress));
    memset(state_decompress, 0, sizeof(state_decompress));

    // Always decompress data in the same order as it was compressed. There is no requirement on destination address when decompressing
    // even though we do it consecutively in this example using the o pointer.
    qlz_compress("This is data packet number one, ", compressed, 32, state_compress);
    o += qlz_decompress(compressed, decompressed, state_decompress);

    qlz_compress("this is data packet number two, ", compressed, 32, state_compress);
    o += qlz_decompress(compressed, decompressed + o, state_decompress);

    qlz_compress("and finally data packet number three.", compressed, 37, state_compress);
    o += qlz_decompress(compressed, decompressed + o, state_decompress);

    // printf() needs 0-termination.
    decompressed[o] = 0;
    printf("Concatenated decompressed results: %s\n", decompressed);

    return 0;
}