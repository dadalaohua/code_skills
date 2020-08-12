#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rsa.h"

#define DECRYPT_FILE "RSA加密密文.txt"
#define ENCRYPT_FILE "RSA解密明文.txt"
//! 约束文件最大2M
#define MAX_FILE 1024*1024*2

// 名称：usage
// 功能：帮助信息
//  参数：应用程序名称
// 返回：提示信息

void Usage( const char *appname )
{
    printf( "\n\tusage: rsa -k 素数P 素数Q\n" );
    printf( "\tusage: rsa -e 明文文件 公钥e 公钥n\n" );
    printf( "\tusage: rsa -d 密文文件 私钥d 私钥n\n" );
}

// 名称：IsNumber
// 功能：判断数字字符数组
//  参数：strNumber:字符数组
// 返回：数字字组数组返回true，否则返回false;

bool IsNumber( const char *strNumber )
{
    unsigned int i;

    if( !strNumber )
        return false;

    for ( i = 0 ; i < strlen(strNumber) ; i++ )
    {
        if ( strNumber[i] < '0' || strNumber[i] > '9' )
        return false;
    }

    return true;
}

// 名称：IsPrimeNumber
// 功能：判断素数
//  参数：num: 输入整数
// 返回：素数返回true，否则返回false;

bool IsPrimeNumber( unsigned int num )
{
    unsigned int i;
    unsigned int sqr;
    
    if( num <= 1 )
        return false;

    sqr = (unsigned int)sqrt((double)num);
    for( i = 2; i <= sqr; i++ )
    {
        if( num % i == 0 )
        return false;
    }

    return true;
}

// 名称：FileIn
// 功能：读取磁盘文件到内存
//  参数：strFile:文件名称；inBuff:指向文件内容缓冲区
// 返回：实际读取内容大小(字节)

int FileIn(const char *strFile, unsigned char *inBuff)
{
    FILE *fp;
    int iFileLen = 0;
    
    fp = fopen(strFile, "r");  
    if(fp == NULL){  
        printf("打开文件 %s 失败!\n", strFile);  
        return;  
    }
    
    fseek(fp, 0, SEEK_END);

    iFileLen = ftell(fp);
    
    if(iFileLen > MAX_FILE)
    {
        printf( "文件长度不能大于 %dM,!\n", MAX_FILE/(1024*1024) );
        goto out;
    }
    
    fseek(fp, 0, SEEK_SET);
    
    fread(inBuff, iFileLen, 1, fp);
    
out:
    fclose(fp);
    
    return iFileLen;
}

// 名称：FileOut
// 功能：加/解密结果输出到当前目录磁盘文件中
//  参数：strOut指向输出字符缓冲区，输出大小len，strFile为输出文件
// 返回：无

void FileOut(const void *strOut, int len, const char *strFile)
{
    FILE *fp;

    fp = fopen(strFile, "w");  
    if(fp == NULL){  
        printf("打开文件 %s 失败!\n", strFile);  
        return;  
    }
    
    fwrite(strOut, len, 1, fp);
    
    fclose(fp);
}

// 名称：CheckParse
// 功能：校验应用程序入口参数
//  参数：argc等于main主函数argc参数，argv指向main主函数argv参数
// 返回：若参数合法返回true，否则返回false
//  备注：简单的入口参数校验

bool CheckParse( int argc, char** argv )
{
    bool bRes = false;

    if( argc != 4 && argc != 5 )
    {   
        Usage(*argv);
        goto out;
    }

    if( argc == 4 && argv[1][1] == 'k' )
    {
        //! 生成公、私钥对
        if( !IsNumber( argv[2] ) || 
        !IsNumber( argv[3] ) ||
        atoi( argv[2] ) > MAX_PRIME ||
        atoi( argv[3] ) > MAX_PRIME )
        goto out;
    }
    else if( (argc == 5) && (argv[1][1] == 'e' || argv[1][1] == 'd') )
    {
        //! 加密、解密操作
        if( !IsNumber( argv[3] ) ||
        !IsNumber( argv[4] ) ||
        atoi( argv[3] ) > MAX_NUM ||
        atoi( argv[4] ) > MAX_NUM )
        goto out;
    }
    else
        Usage(*argv);
    
    bRes = true;

    out:
    return bRes;
}

// 名称：kOption1
// 功能：程序k选项操作：由素数P、Q生成私钥d集合
//  参数：uiP: 程序入口参数P; uiQ: 程序入口参数Q
// 返回：执行正确返回生成私钥数目，否则返回0

unsigned int kOption1( unsigned int uiP, unsigned int uiQ )
{
    unsigned int uiRes = 0;

    if( !IsPrimeNumber( uiP ) )
    {
        printf( "P输入错误，P必须为(0, %d]素数\n", MAX_PRIME );
        return uiRes;
    }
    if( !IsPrimeNumber( uiQ ) )
    {
        printf( "Q输入错误，Q必须为(0, %d]素数\n", MAX_PRIME );
        return uiRes;
    }
    if( uiP == uiQ )
    {
        printf( "素数P与素数Q相同，很容易根据公钥n开平方得出素数P和Q，这种加密不安全，请更换素数!\n" );
        return uiRes;
    }
    printf( "正在生成私钥d集合......\n" );
    uiRes = MakePrivatedKeyd( uiP, uiQ );

    return uiRes;
}
/****************************/

int main(int argc, char* argv[])
{
    unsigned int p, q, d, n, e;//two prime p & q, public key(n, e) , private key(n, d)
    
    CheckParse(argc, argv);

    d = 600;//4828; //uid
    if(argc == 4)
    {
        unsigned int size = 0;
        unsigned int tn, td, te;
        
        p = atoi(argv[2]);
        q = atoi(argv[3]);
        size = kOption1(p, q);
        if(size)
        {
            MakePairkey(p, q, d);
            
            tn = GetPairKey(&td, &te);
            printf("PrivatedKeyd(p, q): (%d,%d) size:%d\n", p, q, size);
            printf("PrivatedKeyd: %d\n", GetPrivateKeyd(d));
            printf("PublicKey(e, n): (%d,%d)\n", te, tn);
            printf("PrivateKey(d, n): (%d,%d)\n", td, tn);
        }
    }
    else if(argc == 5)
    {
        char FileName[20];
        strcpy(FileName, argv[2]);
        int len;
        if(argv[1][1] == 'e' )
        {
            unsigned char *inBuffer = (unsigned char *)malloc(MAX_FILE); //输入缓冲区
            int *cw = (int *)malloc(MAX_FILE);
            len = FileIn(FileName , inBuffer);
            e = atoi(argv[3]);
            n = atoi(argv[4]);
            rsa_encrypt(n, e, (char *)inBuffer, len, cw);
            FileOut(cw, 4*len, DECRYPT_FILE);
        }
        else if(argv[1][1] == 'd')
        {
            char *Buffer = (char *)malloc(MAX_FILE); //输入缓冲区
            int *cw = (int *)malloc(MAX_FILE);
            len = FileIn(FileName, (unsigned char *)cw);
            d = atoi(argv[3]);
            n = atoi(argv[4]);
            rsa_decrypt( n, d, cw, len, Buffer );
            FileOut( Buffer, len/4, ENCRYPT_FILE );
        }
    }
    
    return 0;
}