#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[] = "Hello World";
    char *str;
    
    str = strdup(str1);
    
    printf("%s\n", str);
    
    free(str);
    
    return 0;
}