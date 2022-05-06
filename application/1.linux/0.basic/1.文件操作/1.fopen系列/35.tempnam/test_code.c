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
    char *ptr;
    char *pfx = "test";

    //调用tempnam(const char* dir, const char * pfx) 函数后也返回保存临时文件名的数组指针 ，失败返回NULL。
    //该函数与tmpnam(char * s)区别在于可以指定临时文件的存放目录以及文件名前缀。
    ptr = tempnam("./", pfx);
    printf("%s\n", ptr);
    
    ptr = tempnam(NULL, "");
    printf("%s\n", ptr);
    
    return 0;
}