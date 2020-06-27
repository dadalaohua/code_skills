#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[20] = "hello";
    
    printf("%d\n", strlen(str1));
    printf("%d\n", strlen("world!"));
    
    return 0;
}