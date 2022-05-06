#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    int c;
    
    //getchar等价于getc(stdin)
    printf("输入字符:");
    c = getchar();
    printf("打印输入的字符:");
    //putchar等价于putc(c, stdout);
    putchar(c);
    putchar('\n');

    return 0;
}