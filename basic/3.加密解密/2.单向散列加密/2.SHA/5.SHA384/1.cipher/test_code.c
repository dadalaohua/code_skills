#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha384.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char inputbuf[200];
    unsigned char encrypt[64] = {0};     //存放于加密的信息
    int i = 0;
    
    printf("输入加密的字符:");
    scanf("%s", inputbuf);           //输入加密的字符
    
    //对欲加密的字符进行加密
    SHA384_Simple(inputbuf, strlen((char *)inputbuf), encrypt);
     
    printf("加密前:%s\n", inputbuf);
    
    printf("加密后:");
    for(i = 0; i < 48; i++)
    {
        printf("%2.2x", encrypt[i]);
    }
     
    printf("\n加密结束!\n");
    
    return 0;
}