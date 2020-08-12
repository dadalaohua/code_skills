#include <stdio.h>
#include <string.h>
#include "md5.h"

int main(int argc, char* argv[])
{
    unsigned char encrypt[200];     //存放于加密的信息
    unsigned char decrypt[17];      //存放加密后的结果
    int i = 0;
    MD5_CTX md5;
    
    MD5Init(&md5);                  //初始化用于md5加密的结构

    printf("输入加密的字符:");
    scanf("%s", encrypt);           //输入加密的字符
    
    MD5Update(&md5, encrypt, strlen((char *)encrypt));  //对欲加密的字符进行加密
    MD5Final(decrypt, &md5);                            //获得最终结果
     
    printf("加密前:%s\n",encrypt);
    
    printf("加密后16位:");
    for(i = 4; i < 12; i++)
        printf("%2.2x", decrypt[i]);
     
    printf("\n加密结束!\n");
    
    printf("加密后32位:");
    for(i = 0; i < 16; i++)
        printf("%2.2x", decrypt[i]);
     
    printf("\n加密结束!\n");
    
    return 0;
}