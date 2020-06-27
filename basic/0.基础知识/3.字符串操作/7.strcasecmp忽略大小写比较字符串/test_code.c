#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[] = "hello";
    char str2[] = "world";
    char str3[] = "hella";
    char str4[] = "helloa";
    char str5[] = "hello";
    char str6[] = "HELLO";
    char str7[] = "hElLo";
    
    printf("%d\n", strcasecmp(str1, str2));
    printf("%d\n", strcasecmp(str1, str3));
    printf("%d\n", strcasecmp(str1, str4));
    printf("%d\n", strcasecmp(str1, str5));
    printf("%d\n", strcasecmp(str1, str6));
    printf("%d\n", strcasecmp(str1, str7));
    
    return 0;
}