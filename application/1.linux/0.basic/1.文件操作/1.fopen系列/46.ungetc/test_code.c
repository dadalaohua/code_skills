#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    int c;

    fp = fopen("file.txt", "r");
    if(fp == NULL) {
        perror("error:");
        return -1;
    }
    
    while(1) {
        c = fgetc(fp);
        if(feof(fp))
            break ;
        
        //把字符 char 推入到指定的流 stream 中，这个字符是下一个被读取到的字符
        if( c == 'C' )
            ungetc ('+', fp);
         
        printf("%c", c);
    }

    fclose(fp);

    return 0;
}