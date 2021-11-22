#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_funvtion(void)
{
    char str1[] = "Hello World";
    char *str;
    
    str = strdupa(str1);
    
    printf("%s\n", str);
}

int main(int argc, char* argv[])
{ 
    test_funvtion();
    
    return 0;
}