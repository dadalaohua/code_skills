#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdes.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char key[16]={"key"};
    char encpt[100];
    char result[100];
    char plain[] = "1234567890";
    int len = strlen(plain);
    int i;
    
    cipher2(key, plain, encpt, len);
    for(i = 0; i < sizeof(encpt); i++)
    {
        printf("0x%x ", (unsigned char)encpt[i]);
    }
    printf("\n");
    
    decipher2(key, result, encpt, strlen(encpt));
    printf("%s\n", result);
    
/************************************************************************/
    
    cipher3(key, plain, encpt, len);
    for(i = 0; i < sizeof(encpt); i++)
    {
        printf("0x%x ", (unsigned char)encpt[i]);
    }
    printf("\n");
    
    decipher3(key, result, encpt, strlen(encpt));
    printf("%s\n", result);
    
    return 0;
}