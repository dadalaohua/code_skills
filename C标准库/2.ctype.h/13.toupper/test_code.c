#include <stdio.h>
#include <ctype.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    int i = 0;
    char str[] = "hello world!!!";

    while(str[i]) 
    {
        putchar(toupper(str[i]));
        i++;
    }
    
    printf("\n");

    return 0;
}