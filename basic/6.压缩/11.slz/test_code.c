#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "slz.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define TEST_MAXLEN 1048576

static unsigned char testin[TEST_MAXLEN];
static unsigned char testout[TEST_MAXLEN * 2];

#define  MIN(x, y) ((x) < (y) ? (x) : (y))
/************************************************************************/
/*                                                                      */
/************************************************************************/
int64_t lzbench_slz_compress(char *inbuf, size_t insize, char *outbuf, size_t outsize, size_t level, size_t param2)
{
    struct slz_stream strm;
    size_t outlen = 0;
    size_t window = 8192 << ((level & 3) * 2);
    size_t len;
    size_t blk;

    if (param2 == 0)
        slz_init(&strm, !!level, SLZ_FMT_GZIP);
    else if (param2 == 1)
        slz_init(&strm, !!level, SLZ_FMT_ZLIB);
    else
        slz_init(&strm, !!level, SLZ_FMT_DEFLATE);

    do {
        blk = MIN(insize, window);

        len = slz_encode(&strm, outbuf, inbuf, blk, insize > blk);
        outlen += len;
        outbuf += len;
        inbuf += blk;
        insize -= blk;
    } while (insize > 0);

    outlen += slz_finish(&strm, outbuf);
    return outlen;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int file_compress_gzip_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len, cl;

    fp_src = fopen("src.bin","r");
    fp_dst = fopen("gzip_dst.bin", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    //得到原始文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    cl = lzbench_slz_compress((char *)testin, src_len, (char *)testout, sizeof(testout), 1, 0);
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }
    
    printf("gzip Compressing was completed: %d -> %d (%.2f%%)\n", src_len, cl, (100.0 * cl) / src_len);

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_compress_zlib_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len, cl;

    fp_src = fopen("src.bin","r");
    fp_dst = fopen("zlib_dst.bin", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    //得到原始文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    cl = lzbench_slz_compress((char *)testin, src_len, (char *)testout, sizeof(testout), 1, 1);
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }
    
    printf("gzip Compressing was completed: %d -> %d (%.2f%%)\n", src_len, cl, (100.0 * cl) / src_len);

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_compress_deflate_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len, cl;

    fp_src = fopen("src.bin","r");
    fp_dst = fopen("deflate_dst.bin", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    //得到原始文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    cl = lzbench_slz_compress((char *)testin, src_len, (char *)testout, sizeof(testout), 1, 2);
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }
    
    printf("gzip Compressing was completed: %d -> %d (%.2f%%)\n", src_len, cl, (100.0 * cl) / src_len);

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_no_compress_gzip_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len, cl;

    fp_src = fopen("src.bin","r");
    fp_dst = fopen("no_compress_gzip_dst.bin", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    //得到原始文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    cl = lzbench_slz_compress((char *)testin, src_len, (char *)testout, sizeof(testout), 0, 0);
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }
    
    printf("gzip Compressing was completed: %d -> %d (%.2f%%)\n", src_len, cl, (100.0 * cl) / src_len);

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
    file_compress_gzip_test_function();
    file_compress_zlib_test_function();
    file_compress_deflate_test_function();
    
    //不压缩
    file_no_compress_gzip_test_function();
    
    return 0;
}