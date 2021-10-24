#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rc4.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char key[] = "1234";
    unsigned char myinput[100] = "hello world!";
    int i = 0, len = 0;
    
    printf("orignal text:%s\n", myinput);

    len = strlen((char *)myinput);
    
    //加密
    RC4_Sample(key, strlen((char *)key), myinput, len);
    
    printf("secret string:");
    for(i = 0; i < len; i++)
    {
        printf("0x%x ",myinput[i]);
    }
    printf("\ndecrypt the secret string,the result is:");
    
     //解密
    RC4_Sample(key, strlen((char *)key), myinput, len);
    printf("%s\n", myinput);
    
    return 0;
}