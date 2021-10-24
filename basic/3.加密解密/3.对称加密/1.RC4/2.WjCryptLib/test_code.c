#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WjCryptLib_Rc4.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    uint32_t        dropN = 0;
    uint8_t         key[] = "1234";
    uint8_t         myinput[100] = "hello world!";
    int             i = 0;
    //加密
    Rc4XorWithKey(key, strlen((char *)key), dropN, myinput, myinput, strlen((char *)myinput));
    for(i = 0; i < strlen((char *)myinput); i++)
    {
        printf("0x%x ",myinput[i]);
    }
    printf("\n");
    
    //解密
    Rc4XorWithKey(key, strlen((char *)key), dropN, myinput, myinput, strlen((char *)myinput));
    printf("data:%s\n", myinput);
    
    return 0;
}