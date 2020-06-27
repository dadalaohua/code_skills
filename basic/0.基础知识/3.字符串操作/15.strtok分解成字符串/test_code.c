#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str[80] = "This is - test - website";
    const char s[2] = "-";
    char *token;

    /* 获取第一个子字符串 */
    token = strtok(str, s);

    /* 继续获取其他的子字符串 */
    while( token != NULL )
    {
        printf( "%s\n", token );

        token = strtok(NULL, s);
    }
    printf("\n%s\n",str);
    
    return 0;
}