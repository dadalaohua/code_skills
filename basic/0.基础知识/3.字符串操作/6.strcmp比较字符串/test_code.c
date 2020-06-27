#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[] = "hello";
    char str2[] = "world";
    char str3[] = "hella";
    char str4[] = "helloa";
    char str5[] = "hello";
    
    printf("%d\n", strcmp(str1, str2));
    printf("%d\n", strcmp(str1, str3));
    printf("%d\n", strcmp(str1, str4));
    printf("%d\n", strcmp(str1, str5));
    
    return 0;
}