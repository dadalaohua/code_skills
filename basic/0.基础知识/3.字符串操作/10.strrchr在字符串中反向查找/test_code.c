#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[] = "hello world";
    char *str2;
    
    str2 = strrchr(str1, 'l');
    
    printf("%s\n", str2);
    
    return 0;
}