#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bitio.h"
#include "lz77.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/
int file_compress_test_function(void)
{
    FILE *file = NULL;
    struct bitFILE *bitF = NULL;
    int la_size = -1, sb_size = -1; /* default size */
    
    la_size = 15;       //Lookahead size (default 15)
    sb_size = 4095;     //Search-buffer size (default 4095)
    
    if ((file = fopen("src.bin", "rb")) == NULL){
        return -1;
    }
    if ((bitF = bitIO_open("dst.bin", BIT_IO_W)) == NULL) {
        fclose(file);
        return -1;
    }
    encode(file, bitF, la_size, sb_size);
    
    fclose(file);
    bitIO_close(bitF);
    
    return 0;
}

int file_decompress_test_function(void)
{
    FILE *file = NULL;
    struct bitFILE *bitF = NULL;

    if ((bitF = bitIO_open("dst.bin", BIT_IO_R)) == NULL) {
        return -1;
    }
    if ((file = fopen("ver.bin", "w")) == NULL){
        bitIO_close(bitF);
        return -1;
    }
    decode(bitF, file);
    
    fclose(file);
    bitIO_close(bitF);
    
    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    file_compress_test_function();
    file_decompress_test_function();
    
    return 0;
}