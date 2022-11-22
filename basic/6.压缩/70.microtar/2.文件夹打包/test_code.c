#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>

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
    
    //创建文件夹
    mtar_write_dir_header(&tar, "tmp");
    
    //放在文件夹里的文件
    fp_src = fopen("tmp/test111.txt","r");
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    fseek(fp_src, 0, SEEK_SET);
    fread(testin, 1, src_len, fp_src);
    
    //放在文件夹里的文件，文件名带有文件夹的名字
    mtar_write_file_header(&tar, "tmp/test111.txt", src_len);
    mtar_write_data(&tar, testin, src_len);

    fclose(fp_src);
    
    //放在文件夹里的文件
    fp_src = fopen("tmp/test222.txt","r");
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    fseek(fp_src, 0, SEEK_SET);
    fread(testin, 1, src_len, fp_src);
    
    //放在文件夹里的文件，文件名带有文件夹的名字
    mtar_write_file_header(&tar, "tmp/test222.txt", src_len);
    mtar_write_data(&tar, testin, src_len);

    fclose(fp_src);
    
    //单独的文件，没有放在文件夹里
    fp_src = fopen("README.md","r");
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    fseek(fp_src, 0, SEEK_SET);
    fread(testin, 1, src_len, fp_src);
    
    mtar_write_file_header(&tar, "README.md", src_len);
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
    
    /* Open archive for reading */
    mtar_open(&tar, "test.tar", "r");

    /* 解包所有文件 */
    while ( (mtar_read_header(&tar, &h)) != MTAR_ENULLRECORD ) {
        printf("%s (%d bytes)\n", h.name, h.size);
        
        if(h.type == MTAR_TDIR) {
            mkdir(h.name, 0777);    //解包出来是文件夹类型，创建一个文件夹
        } else {
            //解包出文件
            mtar_find(&tar, h.name, &h1);
            mtar_read_data(&tar, testin, h.size);
            
            fp_src = fopen(h.name, "w+");
            if(fp_src) {
                fwrite(testin, 1, h.size, fp_src);
                fclose(fp_src);
            } else {
                printf("fp_src NULL\n");
            }
        }
        
        mtar_next(&tar);
    }
    
    /* Close archive */
    mtar_close(&tar);
}

int main(int argc, char* argv[])
{
    //打包成tar文件
    //pack();
    
    //查看tar文件内包含的文件
    pick();
    
    //解包tar文件
    unpack();
}
