#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "slz.h"
#include "microtar.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define TEST_MAXLEN 1048576

static unsigned char testin[TEST_MAXLEN];
static unsigned char testout[TEST_MAXLEN * 2];

#define  MIN(x, y) ((x) < (y) ? (x) : (y))

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

int main(int argc, char* argv[])
{
    /***********
        打包
    ***********/
    
    mtar_t tar;
    FILE *fp_src;
    int src_len;
    
    
    /* Open archive for writing */
    mtar_open(&tar, "test.tar", "w");
    
    fp_src = fopen("README.md","r");
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    fseek(fp_src, 0, SEEK_SET);
    
    mtar_write_file_header(&tar, "README.md", src_len);
    
    //可以分段打包
    fread(testin, 1, src_len / 2, fp_src);
    mtar_write_data(&tar, testin, src_len / 2);
    
    fread(testin, 1, src_len - src_len / 2, fp_src);
    mtar_write_data(&tar, testin, src_len - src_len / 2);
    
    fclose(fp_src);
    
    fp_src = fopen("Makefile","r");
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    fseek(fp_src, 0, SEEK_SET);
    fread(testin, 1, src_len, fp_src);
    
    mtar_write_file_header(&tar, "Makefile", src_len);
    mtar_write_data(&tar, testin, src_len);

    fclose(fp_src);
    
    /* Finalize -- this needs to be the last thing done before closing */
    mtar_finalize(&tar);

    /* Close archive */
    mtar_close(&tar);
    
    /***********
        压缩
    ***********/
    
    // FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int cl;

    fp_src = fopen("test.tar","r");
    fp_dst = fopen("test.tar.gz", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) {
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
