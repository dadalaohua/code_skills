#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[20] = "hello";
    char str2[] = " world!";
    
    strncat(str1, str2, 5);
    
    printf("%s\n", str1);
    
    return 0;
}