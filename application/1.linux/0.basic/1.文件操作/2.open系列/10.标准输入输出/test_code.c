#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char buf[128];
    
    int readlen = read(0, buf, 128);     // 0 标准输入
    printf("readlen %d, %s\n", readlen, buf);
    
    int writelen = write(1, buf, readlen); // 1 标准输出
    printf("writelen %d\n", writelen);
    
    int errlen = write(2, buf, readlen); // 2 标准错误
    printf("errlen %d\n", errlen);
    
    return 0;
}