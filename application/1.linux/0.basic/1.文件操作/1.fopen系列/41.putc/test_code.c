#include <stdio.h>
#include <string.h>

/*
 *  fputc 与 putc的区别
 *  把参数 char 指定的字符（一个无符号字符）写入到指定的流 stream 中，
 *  区别在于调用putc函数时所用的参数stream不能是有副作用的表达式，
 *  而fputc函数则可以，也就是说，putc可以被当作宏来调用，而fputc只能作为函数来调用。 
 */
int main(int argc, char* argv[])
{
    FILE *fp;
    int ch;

    fp = fopen("file.txt", "w+");
    for(ch = '0'; ch <= '9'; ch++)
    {
        putc(ch, fp);
    }
    putc('\n', fp);
    fclose(fp);

    return 0;
}