#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lzrw.h"

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

    struct compress_identity *identity;
    unsigned char *memory;
    
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
    
    lzrw2_compress(COMPRESS_ACTION_IDENTITY, NULL, testin, src_len, testout, (uint32_t *)&identity);
    printf("id:             %d\n", identity->id);
    printf("memory:         %d\n", identity->memory);
    printf("name:           %s\n", identity->name);
    printf("version:        %s\n", identity->version);
    printf("date:           %s\n", identity->date);
    printf("copyright:      %s\n", identity->copyright);
    printf("author:         %s\n", identity->author);
    printf("affiliation:    %s\n", identity->affiliation);
    printf("vendor:         %s\n", identity->vendor);
    
    memory = (unsigned char *)malloc(identity->memory);
    if(memory == NULL)
        return -1;
    
    lzrw2_compress(COMPRESS_ACTION_COMPRESS, memory, testin, src_len, testout, &cl);
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }
    
    printf("Compressing was completed: %d -> %d (%.2f%%)\n", src_len, cl, (100.0 * cl) / src_len);

    free(memory);
    
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
    
    struct compress_identity *identity;
    unsigned char *memory;
    
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
    
    lzrw2_compress(COMPRESS_ACTION_IDENTITY, NULL, testin, src_len, testout, (uint32_t *)&identity);
    printf("id:             %d\n", identity->id);
    printf("memory:         %d\n", identity->memory);
    printf("name:           %s\n", identity->name);
    printf("version:        %s\n", identity->version);
    printf("date:           %s\n", identity->date);
    printf("copyright:      %s\n", identity->copyright);
    printf("author:         %s\n", identity->author);
    printf("affiliation:    %s\n", identity->affiliation);
    printf("vendor:         %s\n", identity->vendor);
    
    memory = (unsigned char *)malloc(identity->memory);
    if(memory == NULL)
        return -1;
    
    lzrw2_compress(COMPRESS_ACTION_DECOMPRESS, memory, testin, src_len, testout, &cl);
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }
    
    free(memory);

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
    file_decompress_test_function();
    
    return 0;
}