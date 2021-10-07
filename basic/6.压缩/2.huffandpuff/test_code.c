#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "huffman.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define HUFFANDPUFF_TEST_MAXLEN 1048576
#define HUFFANDPUFF_TEST_ITER 1024

static unsigned char testin[HUFFANDPUFF_TEST_MAXLEN];
static unsigned char testout[HUFFANDPUFF_TEST_MAXLEN * 2];
static unsigned char testver[HUFFANDPUFF_TEST_MAXLEN];
static unsigned char huffbuf[HUFFHEAP_SIZE];

int demo_test_function(void)
{
	unsigned long i,k,l,cl,dcl;
	int v;
	unsigned char mask;

	srand(time(0));

	for(k=0;k<HUFFANDPUFF_TEST_ITER;++k) {
		l = (rand() % HUFFANDPUFF_TEST_MAXLEN) + 1;
		mask = (rand() & 0xff);
		for(i=0;i<l;++i)
			testin[i] = (unsigned char)(rand() & 0xff) & mask;
		cl = huffman_compress(testin,l,testout,sizeof(testout),huffbuf);
		if (cl) {
			memset(testver,0,sizeof(testver));
			dcl = huffman_decompress(testout,cl,testver,sizeof(testver),huffbuf);
			v = ((dcl)&&(!memcmp(testver,testin,l)));
			printf("[%d] in: %d, out: %d, verified: %s\n",(int)k,(int)l,(int)cl,(v) ? "OK" : "FAIL");
		} else printf("[%d] in: %d, out: FAIL\n",(int)k,(int)l);
	}

	printf("\nFuzzing decompress function...\n");
	for(;;) {
		l = (rand() % HUFFANDPUFF_TEST_MAXLEN) + 1;
		mask = (rand() & 0xff);
		for(i=0;i<l;++i)
			testin[i] = (unsigned char)(rand() & 0xff) & mask;
		huffman_decompress(testin,l,testver,sizeof(testver),huffbuf);
		printf("."); fflush(stdout);
	}

	return 0;
}

int file_compress_test_function(void)
{
    FILE *fp_src;
    FILE *fp_dst;
    
    int src_len;
    unsigned long cl;

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
    
    printf("compress before file len %d\n", src_len);
    
    fread(testin, 1, src_len, fp_src);
    
    cl = huffman_compress(testin, src_len, testout, sizeof(testout), huffbuf);
    if (cl) {
        fwrite(testout, 1, cl, fp_dst);
    }
    
    printf("compress after file len %ld\n", cl);

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
    unsigned long cl;

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
    
    cl = huffman_decompress(testin, src_len, testout, sizeof(testout), huffbuf);
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
    demo_test_function();
    //file_compress_test_function();
    //file_decompress_test_function();
    
    return 0;
}