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
/*
_IOFBF（全缓冲），_IOLBF（行缓冲），_IONBF（不带缓冲）
*/
int main(int argc, char* argv[])
{
    char buffer[BUFSIZ];
    //修改缓冲区
    setvbuf(stdout, buffer, _IOFBF, BUFSIZ); //指向长度为BUFSIZ长度的缓冲区，设置为全缓冲。
    printf("hello world"); //由于是全缓冲，没有缓冲区满不会输出
    sleep(1);
    fflush(stdout);
    
    sleep(1);
    
    setvbuf(stdout, buffer, _IOFBF, BUFSIZ); //指向长度为BUFSIZ长度的缓冲区，设置为全缓冲。
    printf("hello world\n"); //由于是全缓冲，没有缓冲区满不会输出
    sleep(1);
    fflush(stdout);
    
    sleep(1);
    
    setvbuf(stdout, buffer, _IOFBF, 5); //指向长度为BUFSIZ长度的缓冲区，设置为全缓冲。
    printf("hello world\n"); //由于是全缓冲，缓冲区会满，直接输出
    sleep(1);
    fflush(stdout);
    
    sleep(3);
    
    //修改缓冲区
    setvbuf(stdout, buffer, _IOLBF, BUFSIZ); //指向长度为BUFSIZ长度的缓冲区，设置为行缓冲。
    printf("hello world"); //由于是行缓冲，没有换行符或者缓冲区满不会输出
    sleep(1);
    fflush(stdout);
    
    setvbuf(stdout, buffer, _IOLBF, BUFSIZ); //指向长度为BUFSIZ长度的缓冲区，设置为行缓冲。
    printf("hello world\n"); //由于是行缓冲，有换行符，直接输出
    sleep(1);
    fflush(stdout);
    
    setvbuf(stdout, buffer, _IOLBF, 5); //指向长度为5长度的缓冲区，设置为行缓冲。
    printf("hello world"); //由于是行缓冲，缓冲区会满，直接输出
    sleep(1);
    fflush(stdout); 
    
    sleep(3);
    
    //关闭缓冲区，变为无缓冲区
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("hello world"); //无缓冲，直接输出
    sleep(3);
    
    return 0;
}