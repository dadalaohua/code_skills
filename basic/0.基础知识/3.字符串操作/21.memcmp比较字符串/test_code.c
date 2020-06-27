#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[15];
    char str2[15];
    int ret;

    memcpy(str1, "abcdef", 6);
    memcpy(str2, "ABCDEF", 6);

    ret = memcmp(str1, str2, 5);

    if(ret > 0)
    {
        printf("str2 小于 str1\n");
    }
    else if(ret < 0) 
    {
        printf("str1 小于 str2\n");
    }
    else 
    {
        printf("str1 等于 str2\n");
    }

    return 0;
}