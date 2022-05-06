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

    //以二进制更新模式(wb+)创建临时文件。被创建的临时文件会在流关闭的时候或者在程序终止的时候自动删除。
    fp = tmpfile();
    fputs("This is test code", fp);

    //设置到文件的开头，类似于fseek(fp, 0, SEEK_SET);
    rewind(fp);
    fputs("ABCD", fp);
    
    //设置到文件的开头
    rewind(fp);
    char ch;
    while(1) {
        ch = fgetc(fp);
        if( feof(fp) )
            break;
        
        printf("%c", ch);
    }
    printf("\n");

    fclose(fp);
    
    return 0;
}