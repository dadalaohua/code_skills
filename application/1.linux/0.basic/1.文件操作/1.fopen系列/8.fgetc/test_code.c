#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    int c;

    fp = fopen("file.txt","r");
    if(fp == NULL) 
    {
        perror("打开文件时发生错误");
        return(-1);
    }
    do
    {
        c = fgetc(fp);
        if( feof(fp) )
        {
            break ;
        }
        printf("%c", c);
    }while(1);

    fclose(fp);

    return 0;
}