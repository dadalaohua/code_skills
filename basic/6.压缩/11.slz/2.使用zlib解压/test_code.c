#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "zlib.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define TEST_MAXLEN 1048576

static unsigned char testin[TEST_MAXLEN];
static unsigned char testout[TEST_MAXLEN * 2];

/************************************************************************/
/*                                                                      */
/************************************************************************/
/* uses zlib to perform the decompression */
int64_t lzbench_slz_decompress(char *inbuf, size_t insize, char *outbuf, size_t outsize, size_t level, size_t param2)
{
    z_stream stream;
    int err;

    stream.zalloc    = NULL;
    stream.zfree     = NULL;

    stream.next_in   = (unsigned char *)inbuf;
    stream.avail_in  = insize;
    stream.next_out  = (unsigned char *)outbuf;
    stream.avail_out = outsize;

    outsize = 0;

    if (param2 == 0)      // gzip
        err = inflateInit2(&stream, 15 + 16);
    else if (param2 == 1) // zlip
        err = inflateInit2(&stream, 15);
    else                  // deflate
        err = inflateInit2(&stream, -15);

    if (err == Z_OK) {
        if (inflate(&stream, Z_FINISH) == Z_STREAM_END)
            outsize = stream.total_out;
        inflateEnd(&stream);
    }
    return outsize;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int file_gzip_decompress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;

    unsigned int src_len, cl;

    fp_src = fopen("gzip_dst.bin","r");
    fp_dst = fopen("gzip_ver.bin", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    //得到文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    cl = lzbench_slz_decompress((char *)testin, src_len, (char *)testout, sizeof(testout), 1, 0);
    if (cl)
    {
        fwrite(testout, 1, cl, fp_dst);
    }

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_zlip_decompress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;

    unsigned int src_len, cl;

    fp_src = fopen("zlib_dst.bin","r");
    fp_dst = fopen("zlib_ver.bin", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    //得到文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    cl = lzbench_slz_decompress((char *)testin, src_len, (char *)testout, sizeof(testout), 1, 1);
    if (cl)
    {
        fwrite(testout, 1, cl, fp_dst);
    }

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_deflate_decompress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;

    unsigned int src_len, cl;

    fp_src = fopen("deflate_dst.bin","r");
    fp_dst = fopen("deflate_ver.bin", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    //得到文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    cl = lzbench_slz_decompress((char *)testin, src_len, (char *)testout, sizeof(testout), 1, 2);
    if (cl)
    {
        fwrite(testout, 1, cl, fp_dst);
    }

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    file_gzip_decompress_test_function();
    file_zlip_decompress_test_function();
    file_deflate_decompress_test_function();
    
    return 0;
}