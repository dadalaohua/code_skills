#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "minilzo.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
/* We want to compress the data block at 'in' with length 'IN_LEN' to
 * the block at 'out'. Because the input block may be incompressible,
 * we must provide a little more output space in case that compression
 * is not possible.
 */

#define IN_LEN      (128*1024ul)
#define OUT_LEN     (IN_LEN + IN_LEN / 16 + 64 + 3)

static unsigned char __LZO_MMODEL in  [ IN_LEN ];
static unsigned char __LZO_MMODEL out [ OUT_LEN ];


/* Work-memory needed for compression. Allocate memory in units
 * of 'lzo_align_t' (instead of 'char') to make sure it is properly aligned.
 */

#define HEAP_ALLOC(var,size) \
    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);


/************************************************************************/
/*                                                                      */
/************************************************************************/
int file_compress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    int src_len;
    
    int r;
    lzo_uint in_len;
    lzo_uint out_len;

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
    
    fread(in, 1, src_len, fp_src);
    
    in_len = src_len;
    r = lzo1x_1_compress(in,in_len,out,&out_len,wrkmem);
    if (r == LZO_E_OK)
        printf("compressed %lu bytes into %lu bytes\n",
            (unsigned long) in_len, (unsigned long) out_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - compression failed: %d\n", r);
        return 2;
    }
    /* check for an incompressible block */
    if (out_len >= in_len)
    {
        printf("This block contains incompressible data.\n");
        return 0;
    }

    if (out_len) {
        fwrite(out, 1, out_len, fp_dst);
    }

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_decompress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;

    int src_len;
    
    int r;
    lzo_uint out_len;
    lzo_uint new_len;
    
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
    
    fread(out, 1, src_len, fp_src);
    
    out_len = src_len;
    //new_len = src_len;
    r = lzo1x_decompress(out,out_len,in,&new_len,NULL);
    if (r == LZO_E_OK)
        printf("decompressed %lu bytes back into %lu bytes\n",
            (unsigned long) out_len, (unsigned long) new_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - decompression failed: %d\n", r);
        return 1;
    }
    
    if (new_len) {
        fwrite(in, 1, new_len, fp_dst);
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
/*
 * Step 1: initialize the LZO library
 */
    if (lzo_init() != LZO_E_OK)
    {
        printf("internal error - lzo_init() failed !!!\n");
        printf("(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
        return 3;
    }
    
    //file_compress_test_function();
    file_decompress_test_function();
    
    return 0;
}