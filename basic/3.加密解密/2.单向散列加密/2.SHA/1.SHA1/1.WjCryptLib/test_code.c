#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "WjCryptLib_Sha1.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char encrypt[200];     //存放于加密的信息
    Sha1Context   sha1Context;
    SHA1_HASH     sha1Hash;
    int i = 0;
    
    Sha1Initialise(&sha1Context);   //初始化

    printf("输入加密的字符:");
    scanf("%s", encrypt);           //输入加密的字符
    
    Sha1Update(&sha1Context, encrypt, (uint32_t)strlen((char *)encrypt));   //对欲加密的字符进行加密
    Sha1Finalise(&sha1Context, &sha1Hash);                                  //获得最终结果
     
    printf("加密前:%s\n", encrypt);
    
    printf("加密后:");
    for(i = 0; i < sizeof(sha1Hash); i++)
    {
        printf("%2.2x", sha1Hash.bytes[i]);
    }
     
    printf("\n加密结束!\n");
    
    return 0;
}