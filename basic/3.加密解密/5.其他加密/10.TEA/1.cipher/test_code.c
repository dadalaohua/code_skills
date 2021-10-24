#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tea.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char plain[] = "my plain";//要进行加密的文本
    int plain_len = 8;
    unsigned char *key = (unsigned char *) "the secret key...";
    unsigned char *iv = (unsigned char *) "01020304";
    unsigned char crpypt[16] = {0};
    unsigned char decryptPlain[8+1] = {0};
    int i;
    
    TeaEncryptCBC(crpypt, plain, plain_len, iv, key);
    for(i = 0; i < sizeof(crpypt); i++)
    {
        printf("0x%x ",crpypt[i]);
    }
    printf("\n");
    
    TeaDecryptCBC(decryptPlain, crpypt, strlen((char *)crpypt), iv, key);
    printf("%s\n", decryptPlain);
    for(i = 0; i < sizeof(decryptPlain); i++)
    {
        printf("0x%x ",decryptPlain[i]);
    }
    printf("\n");
    
    return 0;
}