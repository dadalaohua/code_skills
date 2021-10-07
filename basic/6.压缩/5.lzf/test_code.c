#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lzf.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define TEST_MAXLEN 1048576

static unsigned char testin[TEST_MAXLEN];
static unsigned char testout[TEST_MAXLEN * 2];

/************************************************************************/
/*                                                                      */
/************************************************************************/
int file_compress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len, cl;

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
    
    cl = lzf_compress(testin, src_len, testout, sizeof(testout));
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }
    
    printf("Compressing was completed: %d -> %d (%.2f%%)\n", src_len, cl, (100.0 * cl) / src_len);

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_compress_very_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;

    long src_len, cl;

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
    
    cl = lzf_compress_very(testin, src_len, testout, sizeof(testout));
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }
    
    printf("Compressing was completed: %ld -> %ld (%.2f%%)\n", src_len, cl, (100.0 * cl) / src_len);
    
    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_decompress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;

    unsigned int src_len, cl;

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
    
    cl = lzf_decompress(testin, src_len, testout, sizeof(testout));
    if (cl) {
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
    //file_compress_test_function();
    //file_compress_very_test_function();
    file_decompress_test_function();
    
    return 0;
}