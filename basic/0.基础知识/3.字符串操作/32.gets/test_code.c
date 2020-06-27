#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str[50];

    printf("请输入一个字符串：");
    gets(str);

    printf("您输入的字符串是：%s\n", str);
   
    return 0;
}