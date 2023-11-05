#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
char mytolower(char c)
{
    return ( c | ' ' );
}

char mytoupper(char c)
{
    return ( c & '_' );
}

char myinvert(char c)
{
    return ( c ^ ' ' );
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    for(char i = 'a'; i <= 'z'; i++) {
        printf("%c to lower %c\n", i, mytolower(i));
        printf("%c to upper %c\n", i, mytoupper(i));
        printf("%c to invert %c\n", i, myinvert(i));
    }
    printf("\n");
    
    for(char i = 'A'; i <= 'Z'; i++) {
        printf("%c to lower %c\n", i, mytolower(i));
        printf("%c to upper %c\n", i, mytoupper(i));
        printf("%c to invert %c\n", i, myinvert(i));
    }
    printf("\n");
    
    return 0;
}