#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str1[15];
    char str2[] = "hello world!";
    
    strcpy(str1, str2); //将str2字符数组复制到str1中，str1的容量必须比str2大
    
    printf("%s\n",str1);
    
    return 0;
}