#include <stdio.h>

int main(int argc, char* argv[])
{ 
    int i = 10;
    printf("%zu\n", sizeof(i++));
    printf("%zu\n", sizeof(++i));
    printf("%d\n", i);
    
    return 0;
}