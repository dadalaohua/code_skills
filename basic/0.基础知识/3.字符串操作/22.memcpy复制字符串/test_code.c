#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char src[] = "***";
    char dest[] = "abcdefg";
    
    printf("使用 memcpy 前: %s\n", dest);//使用 memcpy 前: abcdefg
    
    memcpy(dest, src, strlen(src));
    
    printf("使用 memcpy 后: %s\n", dest);//使用 memcpy 后: ***defg

    return 0;
}