#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha1.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char inputbuf[200];
    unsigned char encrypt[20];     //存放于加密的信息
    SHA1_CTX ctx;
    int i = 0;
    
    SHA1Init(&ctx);                 //初始化

    printf("输入加密的字符:");
    scanf("%s", inputbuf);           //输入加密的字符
    
    SHA1Update(&ctx, inputbuf, strlen((char *)inputbuf));   //对欲加密的字符进行加密
    SHA1Final(encrypt, &ctx);   //获得最终结果
     
    printf("加密前:%s\n", inputbuf);
    
    printf("加密后:");
    for(i = 0; i < sizeof(encrypt); i++)
    {
        printf("%2.2x", encrypt[i]);
    }
     
    printf("\n加密结束!\n");
    
    return 0;
}