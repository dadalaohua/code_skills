#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[] = "hello world";
    char str2[] = "world";
    char *str;
    
    str = strstr(str1, str2);
    
    printf("%s\n", str);//world
    
    return 0;
}