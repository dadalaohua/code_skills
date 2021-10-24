#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "WjCryptLib_Sha256.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char encrypt[200];     //存放于加密的信息
    Sha256Context   sha256Context;
    SHA256_HASH     sha256Hash;
    int i = 0;
    
    Sha256Initialise(&sha256Context);   //初始化

    printf("输入加密的字符:");
    scanf("%s", encrypt);           //输入加密的字符
    
    Sha256Update(&sha256Context, encrypt, (uint32_t)strlen((char *)encrypt));   //对欲加密的字符进行加密
    Sha256Finalise(&sha256Context, &sha256Hash);                                  //获得最终结果
     
    printf("加密前:%s\n", encrypt);
    
    printf("加密后:");
    for(i = 0; i < sizeof(sha256Hash); i++)
    {
        printf("%2.2x", sha256Hash.bytes[i]);
    }
     
    printf("\n加密结束!\n");
    
    return 0;
}