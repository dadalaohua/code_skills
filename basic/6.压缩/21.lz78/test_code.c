#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lz78.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/
int file_compress_test_function(void)
{
    lz78_instance* lz78;
    uint8_t ret;
    
    int fd_in;
    int fd_out;

    lz78 = lz78_new(LZ78_MODE_COMPRESS, DICT_SIZE_DEFAULT);
    
    fd_in = open("src.bin", ACCESS_READ);
    fd_out = open("dst.bin", ACCESS_WRITE, 0644);
    
    ret = lz78_compress(lz78, fd_in, fd_out);
    printf("compress ret %d\n", ret);
    
    close(fd_in);
    close(fd_out);
    
    lz78_destroy(lz78);
    
    return 0;
}

int file_decompress_test_function(void)
{
    lz78_instance* lz78;
    uint8_t ret;
    
    int fd_in;
    int fd_out;

    lz78 = lz78_new(LZ78_MODE_DECOMPRESS, DICT_SIZE_DEFAULT);
    
    fd_in = open("dst.bin", ACCESS_READ);
    fd_out = open("ver.bin", ACCESS_WRITE, 0644);

    ret = lz78_decompress(lz78, fd_in, fd_out);
    printf("decompress ret %d\n", ret);
    
    close(fd_in);
    close(fd_out);
    
    lz78_destroy(lz78);
    
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