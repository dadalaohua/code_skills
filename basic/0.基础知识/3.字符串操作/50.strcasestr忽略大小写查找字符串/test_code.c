#define _GNU_SOURCE  

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[] = "Hello World";
    char str2[] = "world";
    char *str;
    
    str = strcasestr(str1, str2);
    
    printf("%s\n", str);//World
    
    return 0;
}