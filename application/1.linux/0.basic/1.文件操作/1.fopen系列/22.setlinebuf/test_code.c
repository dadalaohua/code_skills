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
    //关闭缓冲区，变为无缓冲区
    setbuf(stdout, NULL);
    printf("hello world"); //无缓冲区，直接输出
    sleep(2);
    
    //修改缓冲区
    setlinebuf(stdout); //修改为行缓冲。
    printf("hello world"); //由于是行缓冲，没有换行符或者缓冲区满不会输出
    sleep(2);
    fflush(stdout); 
    
    return 0;
}