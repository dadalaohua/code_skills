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
    FILE *fp;
    fpos_t position;

    fp = fopen("test.log", "w+");
    //获取流 stream 的当前文件位置，并把它写入到 pos。
    fgetpos(fp, &position);
    fputs("Hello World!", fp);

    //设置给定流 stream 的文件位置为给定的位置
    fsetpos(fp, &position);
    fputs("Goodbye World!", fp);
    
    fclose(fp);
    
    return 0;
}