#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WjCryptLib_Md5.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char encrypt[200];     //存放于加密的信息
    Md5Context      md5Context;
    MD5_HASH        md5Hash;
    int i = 0;
    
    Md5Initialise(&md5Context);   //初始化

    printf("输入加密的字符:");
    scanf("%s", encrypt);           //输入加密的字符
    
    Md5Update(&md5Context, encrypt, (uint32_t)strlen((char *)encrypt));   //对欲加密的字符进行加密
    Md5Finalise(&md5Context, &md5Hash);                                  //获得最终结果
     
    printf("加密前:%s\n", encrypt);
    
    printf("加密后:");
    for(i = 0; i < sizeof(md5Hash); i++)
    {
        printf("%2.2x", md5Hash.bytes[i]);
    }
     
    printf("\n加密结束!\n");
    
    return 0;
}