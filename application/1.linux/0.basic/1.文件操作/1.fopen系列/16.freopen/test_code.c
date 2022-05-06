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
    //将标准输出stdout重定向到test.log文件
    FILE *fp = freopen("test.log", "w", stdout);
    if(NULL == fp) {
        printf("reopen failed\n");
        return -1;
    }
    printf("Hello world\n");
    
    fclose(fp);
    
    return 0;
}