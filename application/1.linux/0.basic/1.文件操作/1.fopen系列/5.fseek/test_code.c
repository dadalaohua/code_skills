#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;

    fp = fopen("file.txt","w+");
    fputs("This is test code", fp);

    //文件开头开始的第7个Byte的位置
    fseek(fp, 7, SEEK_SET);
    fputs(" C Programming Langauge", fp);
    
    //文件开头的位置
    fseek(fp, 0, SEEK_SET);
    fputs("ABCD", fp);
    
    //文件当前位置的倒数第3个Byte的位置
    fseek(fp, -2, SEEK_CUR);
    fputs("XY", fp);
    
    //文件末尾的位置
    fseek(fp, 0, SEEK_END);
    fputs("???", fp);
    
    //文件末尾开始的倒数第3个Byte的位置
    fseek(fp, -3, SEEK_END);
    fputs("!!!", fp);
    
    fclose(fp);

    return 0;
}