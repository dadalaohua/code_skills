#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "microtar.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define TEST_MAXLEN 1048576

static unsigned char testin[TEST_MAXLEN];

void pack(void) {
    mtar_t tar;
    FILE *fp_src;
    int src_len;
    
    /* Open archive for writing */
    mtar_open(&tar, "test.tar", "w");
    
    fp_src = fopen("microtar.c","r");
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //写入文件名和文件长度
    mtar_write_file_header(&tar, "microtar.c", src_len);
    
    fseek(fp_src, 0, SEEK_SET);
    
    //支持分段写入
    fread(testin, 1, src_len / 2, fp_src);
    mtar_write_data(&tar, testin, src_len / 2);
    
    fread(testin, 1, src_len - src_len / 2, fp_src);
    mtar_write_data(&tar, testin, src_len - src_len / 2);
    
    fclose(fp_src);
    
    fp_src = fopen("microtar.h","r");
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    fseek(fp_src, 0, SEEK_SET);
    fread(testin, 1, src_len, fp_src);
    
    mtar_write_file_header(&tar, "microtar.h", src_len);
    mtar_write_data(&tar, testin, src_len);

    fclose(fp_src);
    
    /* Finalize -- this needs to be the last thing done before closing */
    mtar_finalize(&tar);

    /* Close archive */
    mtar_close(&tar);
}

void pick(void) {
    mtar_t tar;
    mtar_header_t h;

    /* Open archive for reading */
    mtar_open(&tar, "test.tar", "r");

    /* Print all file names and sizes */
    while ( (mtar_read_header(&tar, &h)) != MTAR_ENULLRECORD ) {
        printf("%s (%d bytes)\n", h.name, h.size);
        mtar_next(&tar);
    }

    /* Close archive */
    mtar_close(&tar);
}

void unpack(void) {
    mtar_t tar;
    mtar_header_t h, h1;
    FILE *fp_src;
    char filename[256];
    
    /* Open archive for reading */
    mtar_open(&tar, "test.tar", "r");

    /* 解包所有文件 */
    while ( (mtar_read_header(&tar, &h)) != MTAR_ENULLRECORD ) {
        printf("%s (%d bytes)\n", h.name, h.size);
        mtar_find(&tar, h.name, &h1);
        mtar_read_data(&tar, testin, h.size);
        
        sprintf(filename, "tmp/%s", h.name);
        fp_src = fopen(filename,"w+");
        fwrite(testin, 1, h.size, fp_src);
        fclose(fp_src);
        
        mtar_next(&tar);
    }
    
    /* Close archive */
    mtar_close(&tar);
}

int main(int argc, char* argv[])
{
    //打包成tar文件
    pack();
    
    //查看tar文件内包含的文件
    pick();
    
    //解包tar文件
    unpack();
}
