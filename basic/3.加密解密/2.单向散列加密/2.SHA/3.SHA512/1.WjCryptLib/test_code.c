#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WjCryptLib_Sha512.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char encrypt[200];     //存放于加密的信息
    Sha512Context   sha512Context;
    SHA512_HASH     sha512Hash;
    int i = 0;
    
    Sha512Initialise(&sha512Context);   //初始化

    printf("输入加密的字符:");
    scanf("%s", encrypt);           //输入加密的字符
    
    Sha512Update(&sha512Context, encrypt, (uint32_t)strlen((char *)encrypt));   //对欲加密的字符进行加密
    Sha512Finalise(&sha512Context, &sha512Hash);                                  //获得最终结果
     
    printf("加密前:%s\n", encrypt);
    
    printf("加密后:");
    for(i = 0; i < sizeof(sha512Hash); i++)
    {
        printf("%2.2x", sha512Hash.bytes[i]);
    }
     
    printf("\n加密结束!\n");
    
    return 0;
}