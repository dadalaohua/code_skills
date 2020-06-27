#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    const char str1[] = "abcde2fghi3jk4l";
    const char str2[] = "34";
    char *ret;

    ret = strpbrk(str1, str2);
    if(ret) 
    {
        printf("第一个匹配的字符是： %c\n", *ret);//一个匹配的字符是： 3
    }
    else 
    {
        printf("未找到字符");
    }
    
    return 0;
}