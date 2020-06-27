#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char dest[] = "oldstring";
    const char src[]  = "newstring";

    printf("Before memmove dest = %s, src = %s\n", dest, src);//Before memmove dest = oldstring, src = newstring
    memmove(dest, src, 9);
    printf("After memmove dest = %s, src = %s\n", dest, src);//After memmove dest = newstring, src = newstring

    return 0;
}