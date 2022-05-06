#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    char buf[128];
    
    printf("输入字符串:");
    //相当于fgets(buf, strlen(buf), stdin);
    gets(buf);
    printf("打印输入的字符串:");
    //相当于fputs(buf, stdout);
    puts(buf);
    putchar('\n');

    return 0;
}