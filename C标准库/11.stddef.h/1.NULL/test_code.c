#include <stdio.h>
#include <stddef.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    FILE *fp;

    fp = fopen("file.txt", "r");
    if( fp != NULL ) 
    {
        printf("成功打开文件 file.txt\n");
        fclose(fp);
    }
    else
    {
        printf("不能打开文件 nofile.txt\n");
    }
   
    return 0;
}