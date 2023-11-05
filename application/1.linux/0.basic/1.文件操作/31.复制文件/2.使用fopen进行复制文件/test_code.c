#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int cp_file(const char* src_path, const char* dst_path)
{
    FILE *src_fp, *dst_fp;
    char buff[1024];
    int len;
    
    src_fp = fopen(src_path, "r");
    if(src_fp == NULL) {
        return -1;
    }
    dst_fp = fopen(dst_path, "w+");
    if(dst_fp == NULL) {
        fclose(src_fp);
        return -1;
    }
    
    while((len = fread(buff, 1, sizeof(buff), src_fp))) {
        fwrite(buff, 1, len, dst_fp);
    }
    
    fclose(src_fp);
    fclose(dst_fp);
    
    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("cp file %d \n", cp_file("Makefile", "cpMakefile"));
    return 0;
}