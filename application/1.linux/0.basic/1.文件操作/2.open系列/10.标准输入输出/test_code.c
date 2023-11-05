#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    
    
    readlen = read(STDIN_FILENO, buf, 128);     // STDIN_FILENO 标准输入
    printf("readlen %d, %s\n", readlen, buf);
    
    writelen = write(STDOUT_FILENO, buf, readlen); // STDOUT_FILENO 标准输出
    printf("writelen %d\n", writelen);
    
    errlen = write(STDERR_FILENO, buf, readlen); // STDERR_FILENO 标准错误
    printf("errlen %d\n", errlen);
    
    return 0;
}