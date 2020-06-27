#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    int len;
    const char str1[] = "ABCDEFG019874";
    const char str2[] = "ABCD";

    len = strspn(str1, str2);

    printf("初始段匹配长度 %d\n", len );//初始段匹配长度 4
    
    return 0;
}