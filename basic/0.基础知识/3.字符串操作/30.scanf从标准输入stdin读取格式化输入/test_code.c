#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    int a;
    char b;
    char str[20];
    
    printf("请输入一个字符：");
    scanf("%c", &b); 
    printf("%c\n", b);
    
    printf("请输入一个数字：");
    scanf("%d", &a); 
    printf("%d\n", a);

    printf("请输入一个字符串：");
    scanf("%s", str); 
    printf("%s\n",str);
   
    return 0;
}