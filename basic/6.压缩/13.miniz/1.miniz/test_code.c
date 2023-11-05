#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "miniz.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define TEST_MAXLEN 1048576

static unsigned char testin[TEST_MAXLEN];
static unsigned char testout[TEST_MAXLEN * 2];

/************************************************************************/
/*                                                                      */
/************************************************************************/
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

static char filename[260];
static unsigned char read_buf[1024 * 256];

static const size_t filename_max = sizeof(filename);
static const size_t read_buf_size = sizeof(read_buf);
static const size_t data_max = 1024 * 256;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if(size > data_max) return 0;

    int ret = 0;
    mz_zip_archive zip;
    mz_zip_zero_struct(&zip);

    mz_uint flags = 0;

    if(!mz_zip_reader_init_mem(&zip, data, size, flags)) return 0;

    mz_uint i, files;

    files = mz_zip_reader_get_num_files(&zip);

    for(i=0; i < files; i++)
    {
        mz_zip_clear_last_error(&zip);

        if(mz_zip_reader_is_file_a_directory(&zip, i)) continue;

        mz_zip_validate_file(&zip, i, MZ_ZIP_FLAG_VALIDATE_HEADERS_ONLY);

        if(mz_zip_reader_is_file_encrypted(&zip, i)) continue;

        mz_zip_clear_last_error(&zip);

        mz_uint ret = mz_zip_reader_get_filename(&zip, i, filename, filename_max);

        if(mz_zip_get_last_error(&zip)) continue;

        mz_zip_archive_file_stat file_stat = {0};
        mz_bool status = mz_zip_reader_file_stat(&zip, i, &file_stat) != 0;

        if ((file_stat.m_method) && (file_stat.m_method != MZ_DEFLATED)) continue;

        //mz_bool retb = mz_zip_reader_extract_to_file(&zip, file_stat.m_file_index, file_stat.m_filename, 0);
        mz_bool retb = mz_zip_reader_extract_file_to_file(&zip, file_stat.m_filename, file_stat.m_filename, 0);
        // mz_zip_reader_extract_file_to_mem(&zip, file_stat.m_filename, read_buf, read_buf_size, 0);
        printf("filename %s comp_size %ld uncomp_size %ld retb %d\n", file_stat.m_filename, file_stat.m_comp_size, file_stat.m_uncomp_size, retb);
        
        // FILE *fp_dst;
        // fp_dst = fopen(file_stat.m_filename, "w+");
        
        // if(fp_dst == NULL) {
            // continue;
        // }
        
        // fwrite(read_buf, 1, file_stat.m_uncomp_size, fp_dst);

        // fclose(fp_dst);
    }

cleanup:
    mz_zip_reader_end(&zip);

    return ret;
}

int file_decompress_test_function_2(void)
{
    FILE *fp_src;

    unsigned int src_len;

    fp_src = fopen("README12345.zip","r");
    
    if(fp_src == NULL) {
        return -1;
    }
    
    //得到文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    LLVMFuzzerTestOneInput(testin, src_len);

    //关闭文件
    fclose(fp_src);
    
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    //file_decompress_test_function();
    file_decompress_test_function_2();
    return 0;
}