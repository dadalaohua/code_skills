#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "divsufsort_private.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
void divsufsort_test(void)
{
    // intput data
    char *Text = "abracadabra";
    int n = strlen(Text);
    int i, j;

    // allocate
    int *SA = (int *)malloc(n * sizeof(int));

    // sort
    divsufsort((unsigned char *)Text, SA, n);

    // output
    for(i = 0; i < n; ++i) {
        printf("SA[%2d] = %2d: ", i, SA[i]);
        for(j = SA[i]; j < n; ++j) {
            printf("%c", Text[j]);
        }
        printf("$\n");
    }

    // deallocate
    free(SA);
}

void divbwt_test(void)
{
    // intput data
    char *Text = "abracadabra";
    int n = strlen(Text);

    // allocate
    int *SA = (int *)malloc(n * sizeof(int));
    char *TextOut = (char *)malloc(n * sizeof(char));
    // bwt
    divbwt((unsigned char *)Text, (unsigned char *)TextOut, SA, n);

    // output
    printf("%s\n", TextOut);

    // deallocate
    free(SA);
    free(TextOut);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    divsufsort_test();
    
    divbwt_test();
    
    return 0;
}