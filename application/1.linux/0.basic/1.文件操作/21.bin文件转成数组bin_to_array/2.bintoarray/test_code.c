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
    
    if(argc < 3){
        printf("input: ./test_code testfile.bin testfile.c\n");
        return 0;
    }
    
    rfp = fopen(argv[1], "r");
    if(rfp == NULL)
        return -1;
    
    wfp = fopen(argv[2], "w");
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
