#include <stdio.h>
#include <string.h>

/*
 *  fgetc 与 getc的区别
 *  两个都是用来从stream中取得一个字符的，
 *  区别在于调用getc函数时所用的参数stream不能是有副作用的表达式，
 *  而fgetc函数则可以，也就是说，getc可以被当作宏来调用，而fgetc只能作为函数来调用。 
 */
int main(int argc, char* argv[])
{
    FILE *fp;
    int c;
    int n = 0;

    fp = fopen("file.txt","r");
    if(fp == NULL) {
        perror("error:");
        return -1;
    }
    
    while(1) {
        c = getc(fp);
        
        if(feof(fp))
            break ;
        
        printf("%c", c);
    }
    printf("\n");

    fclose(fp);

    return 0;
}