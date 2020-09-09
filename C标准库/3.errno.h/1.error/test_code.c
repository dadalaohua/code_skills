#include <stdio.h>
#include <errno.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
extern int errno;   //可以不写

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    FILE *fp;
    int i;

    fp = fopen("file.txt", "r");
    
    if(fp == NULL) 
    {
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    }
    else 
    {
        fclose(fp);
    }
    
    //打印所有错误类型
    for(i = 0; i < 136; i++)
    {
        printf("errno %d : %s\n", i, strerror(i));
    }
    
    return 0;
}