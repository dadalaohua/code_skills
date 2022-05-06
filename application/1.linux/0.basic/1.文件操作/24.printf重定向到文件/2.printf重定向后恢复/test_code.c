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
    char ttyName[128] = {0};
    ttyname_r(1, ttyName, 128); // 1为标准输出
    //将标准输出stdout重定向到test.log文件
    FILE *fp = freopen("test.log", "w", stdout);
    if(NULL == fp) {
        printf("reopen failed\n");
        return -1;
    }
    printf("Hello world\n");
    
    //恢复
    freopen(ttyName, "w+", stdout);
    printf("std out to %s\n",ttyName);
    
    fclose(fp);
    
    return 0;
}