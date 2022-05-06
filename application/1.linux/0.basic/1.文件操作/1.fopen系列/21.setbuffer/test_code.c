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
    char buffer[BUFSIZ];
    //修改缓冲区
    setbuffer(stdout, buffer, BUFSIZ); //指向长度为BUFSIZ长度的缓冲区，并且是行缓冲。
    printf("hello world"); //由于是行缓冲，没有换行符或者缓冲区满不会输出
    sleep(3);
    fflush(stdout); 
    
    sleep(3);
    
    //修改缓冲区
    setbuffer(stdout, buffer, 5); //指向长度为5长度的缓冲区，并且是行缓冲。
    printf("hello world"); //缓冲区会满，直接输出
    sleep(3);
    fflush(stdout); 
    
    sleep(3);
    
    //关闭缓冲区，变为无缓冲区
    setbuffer(stdout, NULL, 0);
    printf("hello world"); //无缓冲区，直接输出
    sleep(3);
    
    return 0;
}