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

    fp = fopen("file.txt","w");
    fputs("This is test code", fp);
   
    //设置到文件的开头
    rewind(fp);
    char ch;
    while(1) {
        ch = fgetc(fp);
        //如果设置了与流关联的错误标识符，该函数返回一个非零值，否则返回一个零值。
        if(ferror(fp)) {
            perror("error:");
            break;
        }
        
        //判断是否结束，是否识别到文件结束标识符
        if(feof(fp))
            break;
        
        printf("%c", ch);
    }
    printf("\n");

    fclose(fp);
    
    return 0;
}