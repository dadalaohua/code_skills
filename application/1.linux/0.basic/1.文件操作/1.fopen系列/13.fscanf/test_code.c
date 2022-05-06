#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{ 
    FILE* fp;

    fp = fopen("file.txt", "r");
    //文件内容为
    //Hello world 123456
    
    char str1[16], str2[16];
    int num;
    fscanf(fp, "%s %s %d", str1, str2, &num);
    
    printf("str1 %s\n", str1);
    printf("str2 %s\n", str2);
    printf("num %d\n", num);
    
    fclose(fp);

    return 0;
}