#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char dest[20];
    char src[20];
    int len;

    strcpy(src, "W3C School");
    len = strxfrm(dest, src, 20);

    printf("字符串 |%s| 的长度是： |%d|\n", dest, len);//字符串 |W3C School| 的长度是： |10|
    
    return 0;
}