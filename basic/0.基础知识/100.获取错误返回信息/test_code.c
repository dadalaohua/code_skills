#include <stdio.h>  //void perror(const char *msg);
#include <string.h> //char *strerror(int errnum);
#include <errno.h>  //errno

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
errno 是错误代码，在 errno.h头文件中；
perror是错误输出函数，输出格式为：msg:errno对应的错误信息(加上一个换行符)；
strerror 是通过参数 errnum （就是errno），返回对应的错误信息。
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    FILE *fp;
    fp = fopen("./hello", "r");
    if(fp == NULL) {
        perror("error");
        printf("strerror: %s\n", strerror(errno)); //转换错误码为对应的错误信息
        return -1;
    }
    fclose(fp);
    return 0;
}