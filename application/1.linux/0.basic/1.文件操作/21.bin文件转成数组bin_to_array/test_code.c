#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    FILE * rfp;
    FILE * wfp;
    char str[50];
    unsigned char c;
    
    rfp = fopen("./Ring04.mp3", "r");
    if(rfp == NULL)
        return -1;
    
    wfp = fopen("./Ring04.c", "w");
    if(wfp == NULL)
        return -1;
    
    strcpy(str, "const unsigned char array[] = {");
    fwrite(str, 1, strlen(str), wfp);
    
    while(1) {
        c = fgetc(rfp);
        if(feof(rfp))
            break ;
        
        sprintf(str, "0x%02x,", c);
        fwrite(str, 1, strlen(str), wfp);
    }
    
    strcpy(str, "};");
    fwrite(str, 1, strlen(str), wfp);

    fclose(rfp);
    fclose(wfp);
    
    return 0;
}
