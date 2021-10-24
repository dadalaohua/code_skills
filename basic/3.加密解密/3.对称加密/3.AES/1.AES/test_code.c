#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "WjCryptLib_Aes.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    AesContext      aesContext;
    uint8_t         key_128[AES_KEY_SIZE_128] = {0};
    uint8_t         key_192[AES_KEY_SIZE_192] = {0};
    uint8_t         key_256[AES_KEY_SIZE_256] = {0};
    uint8_t         block[AES_BLOCK_SIZE] = {0};
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
    printf("block:\n");
    for(i = 0; i  < AES_BLOCK_SIZE; i++)
    {
        block[i] = i;
    }
    // Display
    for(i = 0; i < sizeof(block); i++)
    {
        printf("%2.2x", block[i]);
    }
    printf("\n");
    
    //加密128bit
    AesInitialise(&aesContext, key_128, AES_KEY_SIZE_128);
    AesEncryptInPlace(&aesContext, block);
    // Display
    printf("Encrypt:\n");
    for(i = 0; i < sizeof(block); i++)
    {
        printf("%2.2x", block[i]);
    }
    printf( "\n" );
    
    //解密128bit
    AesInitialise(&aesContext, key_128, AES_KEY_SIZE_128);
    AesDecryptInPlace(&aesContext, block);
    // Display
    printf("Decrypt:\n");
    for(i = 0; i < sizeof(block); i++)
    {
        printf("%2.2x", block[i]);
    }
    printf("\n\n");
    
/************************************************************************/
    //设置密码
    printf("key:\n");
    for(i = 0; i  < AES_KEY_SIZE_192; i++)
    {
        key_192[i] = i;
    }
    // Display
    for(i = 0; i < AES_KEY_SIZE_192; i++)
    {
        printf("%2.2x", key_192[i]);
    }
    printf("\n");
    //设置数据块的内容
    printf("block:\n");
    for(i = 0; i  < AES_BLOCK_SIZE; i++)
    {
        block[i] = i;
    }
    // Display
    for(i = 0; i < sizeof(block); i++)
    {
        printf("%2.2x", block[i]);
    }
    printf("\n");
    
    //加密192bit
    AesInitialise(&aesContext, key_192, AES_KEY_SIZE_192);
    AesEncryptInPlace(&aesContext, block);
    // Display
    printf("Encrypt:\n");
    for(i = 0; i < sizeof(block); i++)
    {
        printf("%2.2x", block[i]);
    }
    printf( "\n" );
    
    //解密192bit
    AesInitialise(&aesContext, key_192, AES_KEY_SIZE_192);
    AesDecryptInPlace(&aesContext, block);
    // Display
    printf("Decrypt:\n");
    for(i = 0; i < sizeof(block); i++)
    {
        printf("%2.2x", block[i]);
    }
    printf("\n\n");

/************************************************************************/
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
    printf("block:\n");
    for(i = 0; i  < AES_BLOCK_SIZE; i++)
    {
        block[i] = i;
    }
    // Display
    for(i = 0; i < sizeof(block); i++)
    {
        printf("%2.2x", block[i]);
    }
    printf("\n");
    
    //加密256bit
    AesInitialise(&aesContext, key_256, AES_KEY_SIZE_256);
    AesEncryptInPlace(&aesContext, block);
    // Display
    printf("Encrypt:\n");
    for(i = 0; i < sizeof(block); i++)
    {
        printf("%2.2x", block[i]);
    }
    printf( "\n" );
    
    //解密256bit
    AesInitialise(&aesContext, key_256, AES_KEY_SIZE_256);
    AesDecryptInPlace(&aesContext, block);
    // Display
    printf("Decrypt:\n");
    for(i = 0; i < sizeof(block); i++)
    {
        printf("%2.2x", block[i]);
    }
    printf("\n\n");

    return 0;
}