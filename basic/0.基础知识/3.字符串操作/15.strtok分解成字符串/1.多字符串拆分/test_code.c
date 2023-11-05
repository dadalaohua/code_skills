#include <stdio.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void function1(void) {
    char sentence1[100] = "This is test website";
    char sentence2[100] = "adfgvds bd cga dgtjj";
    char *token1 = strtok(sentence1, " ");
    char *token2 = strtok(sentence2, " ");
    char *offset1 = sentence1;
    char *offset2 = sentence2;
    printf( "sentence1:\n" );
    while( token1 != NULL )
    {
        printf( "%s\n", token1 );
        offset1 += strlen(token1) + 1;
        token1 = strtok(offset1, " ");
    }
    printf( "\n" );
    printf( "sentence2:\n" );
    while( token2 != NULL )
    {
        printf( "%s\n", token2 );
        offset2 += strlen(token2) + 1;
        token2 = strtok(offset2, " ");
    }
    printf( "\n" );
}

void function2(void) {
    char sentence1[100] = "This is test website";
    char sentence2[100] = "adfgvds bd cga dgtjj";
    int len1 = strlen(sentence1), len2 = strlen(sentence2);
    char *words1[len1], *words2[len2];
    int words1Size = 0, words2Size = 0;
    char *p = strtok(sentence1, " ");
    while (p != NULL) {
        words1[words1Size++] = p;
        p = strtok(NULL, " ");
    }
    p = strtok(sentence2, " ");
    while (p != NULL) {
        words2[words2Size++] = p;
        p = strtok(NULL, " ");
    }
    printf( "sentence1:\n" );
    for(int i = 0; i < words1Size; i++) {
        printf( "%s\n", words1[i] );
    }
    printf( "\n" );
    printf( "sentence2:\n" );
    for(int i = 0; i < words2Size; i++) {
        printf( "%s\n", words2[i] );
    }
    printf( "\n" );
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    function1();
    function2();
    return 0;
}