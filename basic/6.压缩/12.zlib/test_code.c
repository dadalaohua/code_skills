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
int file_default_compress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len;

    fp_src = fopen("src.bin","r");
    fp_dst = fopen("dst.bin", "w+");
    
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
    
    uLongf zcomplen = src_len;
    int err = compress2((unsigned char*)testout, &zcomplen, (unsigned char*)testin, src_len, Z_DEFAULT_COMPRESSION);
    if (err == Z_OK)
    {
        fwrite(testout, 1, zcomplen, fp_dst);
    }
    
    printf("Compressing was completed: %d -> %ld (%.2f%%)\n", src_len, zcomplen, (100.0 * zcomplen) / src_len);

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_best_compress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len;

    fp_src = fopen("src.bin","r");
    fp_dst = fopen("dst.bin", "w+");
    
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
    
    uLongf zcomplen = src_len;
    int err = compress2((unsigned char*)testout, &zcomplen, (unsigned char*)testin, src_len, Z_BEST_COMPRESSION);
    if (err == Z_OK)
    {
        fwrite(testout, 1, zcomplen, fp_dst);
    }
    
    printf("Compressing was completed: %d -> %ld (%.2f%%)\n", src_len, zcomplen, (100.0 * zcomplen) / src_len);

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_best_speed_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len;

    fp_src = fopen("src.bin","r");
    fp_dst = fopen("dst.bin", "w+");
    
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
    
    uLongf zcomplen = src_len;
    int err = compress2((unsigned char*)testout, &zcomplen, (unsigned char*)testin, src_len, Z_BEST_SPEED);
    if (err == Z_OK)
    {
        fwrite(testout, 1, zcomplen, fp_dst);
    }
    
    printf("Compressing was completed: %d -> %ld (%.2f%%)\n", src_len, zcomplen, (100.0 * zcomplen) / src_len);

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_no_compress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len;

    fp_src = fopen("src.bin","r");
    fp_dst = fopen("dst.bin", "w+");
    
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
    
    uLongf zcomplen = src_len;
    int err = compress2((unsigned char*)testout, &zcomplen, (unsigned char*)testin, src_len, Z_NO_COMPRESSION);
    if (err == Z_OK)
    {
        fwrite(testout, 1, zcomplen, fp_dst);
    }
    
    printf("Compressing was completed: %d -> %ld (%.2f%%)\n", src_len, zcomplen, (100.0 * zcomplen) / src_len);

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_decompress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;

    unsigned int src_len;

    fp_src = fopen("dst.bin","r");
    fp_dst = fopen("ver.bin", "w+");
    
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
    
    uLongf zdecomplen = sizeof(testout);
    int err = uncompress((unsigned char*)testout, &zdecomplen, (unsigned char*)testin, src_len); 
    if (err == Z_OK)
    {
        fwrite(testout, 1, zdecomplen, fp_dst);
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
    //默认压缩参数
    file_default_compress_test_function();
    file_decompress_test_function();
    
    //最佳压缩
    // file_best_compress_test_function();
    // file_decompress_test_function();
    
    //最佳速度
    // file_best_speed_test_function();
    // file_decompress_test_function();
    
    //不压缩
    // file_no_compress_test_function();
    // file_decompress_test_function();
    
    return 0;
}