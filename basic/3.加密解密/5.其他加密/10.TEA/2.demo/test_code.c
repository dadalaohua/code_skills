#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void EncryptTEA(unsigned int *firstChunk, unsigned int *secondChunk, unsigned int* key)
{
    unsigned int y = *firstChunk;
    unsigned int z = *secondChunk;
    unsigned int sum = 0;

    unsigned int delta = 0x9e3779b9;

    for (int i = 0; i < 8; i++)//8轮运算(需要对应下面的解密核心函数的轮数一样)
    {
        sum += delta;
        y += ((z << 4) + key[0]) ^ (z + sum) ^ ((z >> 5) + key[1]);
        z += ((y << 4) + key[2]) ^ (y + sum) ^ ((y >> 5) + key[3]);
    }

    *firstChunk = y;
    *secondChunk = z;
}

void DecryptTEA(unsigned int *firstChunk, unsigned int *secondChunk, unsigned int* key)
{
    unsigned int  sum = 0;
    unsigned int  y = *firstChunk;
    unsigned int  z = *secondChunk;
    unsigned int  delta = 0x9e3779b9;

    sum = delta << 3; //32轮运算，所以是2的5次方；16轮运算，所以是2的4次方；8轮运算，所以是2的3次方

    for (int i = 0; i < 8; i++) //8轮运算
    {
        z -= (y << 4) + key[2] ^ y + sum ^ (y >> 5) + key[3];
        y -= (z << 4) + key[0] ^ z + sum ^ (z >> 5) + key[1];
        sum -= delta;
    }

    *firstChunk = y;
    *secondChunk = z;
}

//buffer：输入的待加密数据buffer，在函数中直接对元数据buffer进行加密；size：buffer长度；key是密钥；
void EncryptBuffer(char* buffer, int size, unsigned int* key)
{
    char *p = buffer;

    int leftSize = size;

    while (p < buffer + size &&
        leftSize >= sizeof(unsigned int) * 2)
    {
        EncryptTEA((unsigned int *)p, (unsigned int *)(p + sizeof(unsigned int)), key);
        p += sizeof(unsigned int) * 2;

        leftSize -= sizeof(unsigned int) * 2;
    }
}

//buffer：输入的待解密数据buffer，在函数中直接对元数据buffer进行解密；size：buffer长度；key是密钥；
void DecryptBuffer(char* buffer, int size, unsigned int* key)
{
    char *p = buffer;

    int leftSize = size;

    while (p < buffer + size &&
        leftSize >= sizeof(unsigned int) * 2)
    {
        DecryptTEA((unsigned int *)p, (unsigned int *)(p + sizeof(unsigned int)), key);
        p += sizeof(unsigned int) * 2;

        leftSize -= sizeof(unsigned int) * 2;
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    //-----设置密钥，必须需要16个字符或以上
    unsigned int *key = (unsigned int *)"testkey123456789";
    char pBuffer[] = "Hello World";
    int i;
    
    //-----对原始文件进行加密
    EncryptBuffer(pBuffer, strlen(pBuffer), key);
    for(i = 0; i < sizeof(pBuffer); i++)
    {
        printf("0x%x ",(unsigned char)pBuffer[i]);
    }
    printf("\n");
    
    //如果是已经加密过的文件，则对应为解密函数
    DecryptBuffer(pBuffer, strlen(pBuffer), key);
    printf("%s\n",pBuffer);
    
    return 0;
}