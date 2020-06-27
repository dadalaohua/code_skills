#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[15];
    char str2[] = "hello world!";
    
    memset(str1, 0, sizeof(str1));
    
    strncpy(str1, str2, 5); ////将前5个字符复制到str1中
    
    printf("%s\n", str1);
    
    return 0;
}