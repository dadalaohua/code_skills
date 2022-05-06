#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    int len;

    fp = fopen("file.txt", "r");
    if(fp == NULL) 
    {
        perror ("打开文件错误");
        return(-1);
    }
    fseek(fp, 0, SEEK_END);

    len = ftell(fp);
    fclose(fp);

    printf("file.txt 的总大小 = %d 字节\n", len);

    return 0;
}