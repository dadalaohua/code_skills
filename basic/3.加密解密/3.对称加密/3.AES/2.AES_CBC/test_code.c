#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "WjCryptLib_AesCbc.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_function_1(void)
{
    uint8_t         key_128[AES_KEY_SIZE_128] = {0};
    uint8_t         iv[AES_CBC_IV_SIZE];
    uint8_t         InBuffer[1024] = {0};
    uint8_t         OutBuffer[1024] = {0};
    uint32_t        i;

    //设置密码
    printf("key:\n");
    for(i = 0; i  < AES_KEY_SIZE_128; i++)
    {
        key_128[i] = i;
    }
    // Display
    for(i = 0; i < AES_KEY_SIZE_128; i++)
    {
        printf("%2.2x", key_128[i]);
    }
    printf("\n");
    //设置数据块的内容
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        InBuffer[i] = i % 256;
    }
    // Display
    printf("InBuffer\n");
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf("\n\n");
    
    //加密
    //输入的buff长度要是16的倍数
    AesCbcEncryptWithKey(key_128, AES_KEY_SIZE_128, iv, InBuffer, OutBuffer, sizeof(InBuffer));
    
    printf("Encrypt\n");
    for(i = 0; i < sizeof(OutBuffer); i++)
    {
        printf("%2.2x", OutBuffer[i]);
    }
    printf("\n\n");
    
    AesCbcDecryptWithKey(key_128, AES_KEY_SIZE_128, iv, OutBuffer, InBuffer, sizeof(InBuffer));
    
    printf("Decrypt\n");
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf("\n\n");
}

void test_function_2(void)
{
    uint8_t         key_256[AES_KEY_SIZE_256] = {0};
    uint8_t         iv[AES_CBC_IV_SIZE];
    uint8_t         InBuffer[1024] = {0};
    uint8_t         OutBuffer[1024] = {0};
    uint32_t        i;

    //设置密码
    printf("key:\n");
    for(i = 0; i  < AES_KEY_SIZE_256; i++)
    {
        key_256[i] = i;
    }
    // Display
    for(i = 0; i < AES_KEY_SIZE_256; i++)
    {
        printf("%2.2x", key_256[i]);
    }
    printf("\n");
    //设置数据块的内容
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        InBuffer[i] = i % 256;
    }
    // Display
    printf("InBuffer\n");
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf("\n\n");
    
    //加密
    //输入的buff长度要是16的倍数
    AesCbcEncryptWithKey(key_256, AES_KEY_SIZE_256, iv, InBuffer, OutBuffer, sizeof(InBuffer));
    
    printf("Encrypt\n");
    for(i = 0; i < sizeof(OutBuffer); i++)
    {
        printf("%2.2x", OutBuffer[i]);
    }
    printf("\n\n");
    
    AesCbcDecryptWithKey(key_256, AES_KEY_SIZE_256, iv, OutBuffer, InBuffer, sizeof(InBuffer));
    
    printf("Decrypt\n");
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf("\n\n");
}

void test_function_3(void)
{
    AesCbcContext   aesCbcContext;
    uint8_t         key_128[AES_KEY_SIZE_128] = {0};
    uint8_t         iv[AES_CBC_IV_SIZE];
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
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        InBuffer[i] = i % 256;
    }
    // Display
    printf("InBuffer\n");
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf("\n\n");
    
    //初始化
    AesCbcInitialiseWithKey(&aesCbcContext, key_128, AES_KEY_SIZE_128, iv);
    
    //加密
    //输入的buff长度要是16的倍数
    AesCbcEncrypt(&aesCbcContext, InBuffer, OutBuffer, sizeof(InBuffer));
    
    printf("Encrypt\n");
    for(i = 0; i < sizeof(OutBuffer); i++)
    {
        printf("%2.2x", OutBuffer[i]);
    }
    printf("\n\n");
    
    //解密
    AesCbcDecrypt(&aesCbcContext, OutBuffer, InBuffer, sizeof(OutBuffer));
    
    printf("Decrypt\n");
    for(i = 0; i < sizeof(InBuffer); i++)
    {
        printf("%2.2x", InBuffer[i]);
    }
    printf("\n\n");
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    test_function_1();
    test_function_2();
    test_function_3();

    return 0;
}