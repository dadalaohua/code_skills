#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Alloc.h"
#include "LzmaDec.h"
#include "LzmaEnc.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define TEST_MAXLEN 1048576

static unsigned char testin[TEST_MAXLEN] = {0};
static unsigned char testout[TEST_MAXLEN * 2] = {0};

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/
int file_compress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    unsigned int src_len, cl;
    
    CLzmaEncProps props;
    int res;
    size_t headerSize = LZMA_PROPS_SIZE;
    SizeT out_len = sizeof(testout) - LZMA_PROPS_SIZE;

    fp_src = fopen("src.bin","r");
    fp_dst = fopen("dst.bin", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    memset(testin, 0x00, sizeof(testin));
    memset(testout, 0x00, sizeof(testout));
    
    //得到原始文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    LzmaEncProps_Init(&props);
    //props.level = 5;
    LzmaEncProps_Normalize(&props);
    
    res = LzmaEncode((Byte*)testout+LZMA_PROPS_SIZE, &out_len, (Byte*)testin, src_len, &props, (Byte*)testout, &headerSize, 0/*int writeEndMark*/, NULL, &g_Alloc, &g_Alloc);
    if (res != SZ_OK) return 0;
    
    if (out_len) {
        fwrite(testout, 1, LZMA_PROPS_SIZE + out_len, fp_dst);
    }
    
    cl = LZMA_PROPS_SIZE + out_len;
    printf("Compressing was completed: %d -> %d (%.2f%%)\n", src_len, cl, (100.0 * cl) / src_len);

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int file_decompress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;

    unsigned int cl;
    
    int res;
	SizeT out_len = sizeof(testout);
	SizeT src_len;
	ELzmaStatus status;

    fp_src = fopen("dst.bin","r");
    fp_dst = fopen("ver.bin", "w+");
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    memset(testin, 0x00, sizeof(testin));
    memset(testout, 0x00, sizeof(testout));
    
    //得到文件大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    fread(testin, 1, src_len, fp_src);
    
    //src_len = src_len - LZMA_PROPS_SIZE;
    
    res = LzmaDecode((Byte*)testout, &out_len, (Byte*)testin+LZMA_PROPS_SIZE, &src_len, (Byte*)testin, LZMA_PROPS_SIZE, LZMA_FINISH_END, &status, &g_Alloc);
    printf("res == %d\n", res);
    //if (res != SZ_OK) return 0;
    cl = out_len;
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}

int lzbench_lzma_compress(char *inbuf, size_t insize, char *outbuf, size_t outsize, size_t level)
{
	CLzmaEncProps props;
	int res;
    size_t headerSize = LZMA_PROPS_SIZE;
	SizeT out_len = outsize - LZMA_PROPS_SIZE;
	
	LzmaEncProps_Init(&props);
	props.level = level;
	LzmaEncProps_Normalize(&props);
  /*
  p->level = 5;
  p->dictSize = p->mc = 0;
  p->reduceSize = (UInt64)(Int64)-1;
  p->lc = p->lp = p->pb = p->algo = p->fb = p->btMode = p->numHashBytes = p->numThreads = -1;
  p->writeEndMark = 0;
  */
  
  	res = LzmaEncode((unsigned char*)outbuf+LZMA_PROPS_SIZE, &out_len, (unsigned char*)inbuf, insize, &props, (unsigned char*)outbuf, &headerSize, 0/*int writeEndMark*/, NULL, &g_Alloc, &g_Alloc);
	if (res != SZ_OK) return 0;
	
//	printf("out_len=%u LZMA_PROPS_SIZE=%d headerSize=%d\n", (int)(out_len + LZMA_PROPS_SIZE), LZMA_PROPS_SIZE, (int)headerSize);
	return LZMA_PROPS_SIZE + out_len;
}

int lzbench_lzma_decompress(char *inbuf, size_t insize, char *outbuf, size_t outsize)
{
	int res;
	SizeT out_len = outsize;
	SizeT src_len = insize - LZMA_PROPS_SIZE;
	ELzmaStatus status;
	
//	SRes LzmaDecode(Byte *dest, SizeT *destLen, const Byte *src, SizeT *srcLen, const Byte *propData, unsigned propSize, ELzmaFinishMode finishMode, ELzmaStatus *status, ISzAlloc *alloc)
	res = LzmaDecode((unsigned char*)outbuf, &out_len, (unsigned char*)inbuf+LZMA_PROPS_SIZE, &src_len, (unsigned char*)inbuf, LZMA_PROPS_SIZE, LZMA_FINISH_END, &status, &g_Alloc);
	if (res != SZ_OK) return 0;
	
//	printf("out_len=%u\n", (int)(out_len + LZMA_PROPS_SIZE));	
    return out_len;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    file_compress_test_function();
    file_decompress_test_function();
    //char *buf = "The following results are obtained with `lzbench 1.8` with the `-t16,16 -eall` options using 1 core of Intel Core i7-8700K, Ubuntu 18.04.3 64-bit, and clang 9.0.1 with ["silesia.tar"](https://drive.google.com/file/d/0BwX7dtyRLxThenZpYU9zLTZhR1k/view?usp=sharing) which contains tarred files from [Silesia compression corpus](http://sun.aei.polsl.pl/~sdeor/index.php?page=silesia). The results are sorted by ratio. The results in **bold** show pareto frontier on compression ratio." ;
    // char *buf = "Lossless compression algorithm history-entropy coding was the first to appear, followed by LZX these compression algorithms";
    // int len;
    
    // memset(testin, 0x00, sizeof(testin));
    // memset(testout, 0x00, sizeof(testout));
    
    // memcpy(testin, buf, strlen(buf));
    
    // len = lzbench_lzma_compress((char*)testin, strlen(buf) + 1, (char*)testout, sizeof(testout), 5);
    
    // printf("lzbench_lzma_compress %d\n", len);
    
    // memset(testin, 0x00, sizeof(testin));
    
    // printf("lzbench_lzma_decompress %d\n", lzbench_lzma_decompress((char*)testout, len, (char*)testin, sizeof(testin)));
    
    // printf("%s\n", testin);
    
    return 0;
}