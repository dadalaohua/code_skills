#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WjCryptLib_AesOfb.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_function_1(void)
{
    uint8_t         key_128[AES_KEY_SIZE_128] = {0};
    uint8_t         IV[AES_OFB_IV_SIZE];
    uint8_t         InBuffer[1024] = {0};
    uint8_t         OutBuffer[1024] = {0};
    uint32_t        i;

    //设置密码
    printf("key:\n");
    for(i = 0; i  < sizeof(key_128); i++)
    {
        key_128[i] = i;
    }
    // Display
    for(i = 0; i < sizeof(key_128); i++)
    {
        printf("%2.2x", key_128[i]);
    }
    printf("\n");
    //设置数据块的内容
    printf("InBuffer:\n");
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        InBuffer[i] = i;
    }
    // Display
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf("\n");
    
    AesOfbXorWithKey(key_128, AES_KEY_SIZE_128, IV, InBuffer, OutBuffer, sizeof(InBuffer));
    printf("Encrypt:\n");
    for(i = 0; i < sizeof(OutBuffer); i++)
    {
        printf("%2.2x", OutBuffer[i]);
    }
    printf( "\n" );
    
    AesOfbXorWithKey(key_128, AES_KEY_SIZE_128, IV, OutBuffer, InBuffer, sizeof(InBuffer));
    printf("\n");
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf( "\n" );
}

void test_function_2(void)
{
    AesOfbContext   aesOfb;
    uint8_t         key_128[AES_KEY_SIZE_128] = {0};
    uint8_t         IV[AES_OFB_IV_SIZE];
    uint8_t         InBuffer[1024] = {0};
    uint32_t        i;

    //设置密码
    printf("key:\n");
    for(i = 0; i  < sizeof(key_128); i++)
    {
        key_128[i] = i;
    }
    // Display
    for(i = 0; i < sizeof(key_128); i++)
    {
        printf("%2.2x", key_128[i]);
    }
    printf("\n");
    //设置数据块的内容
    printf("InBuffer:\n");
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        InBuffer[i] = i;
    }
    // Display
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf("\n");
    
    AesOfbInitialiseWithKey(&aesOfb, key_128, AES_KEY_SIZE_128, IV);
    AesOfbOutput(&aesOfb, InBuffer, sizeof(InBuffer));
    // Display
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf( "\n" );
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    test_function_1();
    test_function_2();
    
    return 0;
}