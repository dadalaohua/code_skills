#include <stdio.h>
#include "shell.h"

//EXPOTRFUNC( 函数别名命令行调用的名字 |真正的函数名 | 函数传参的格式字符串 |这个函数的简介)
void simplefunction(char* str,unsigned int sum,float dee,char ch)
{
    printf("接收到的字符串是:%s,\n\
接收到的字符是: %c \n\
接受到的数字是 %d\n\
接收到的小数是 %f __ \n ",str,ch,sum,dee);
}

void showcircle(char ch,int r)
{
    for(int i = 1; i<=(2*r); i++)
    {
        for(int j = 1; j<(2*r); j++)
        {
            if(((i-r)*(i-r)+(j-r)*(j-r))<=(r*r))
                printf("%c ",ch);
            else
                printf("%c ",' ');
        }
        printf("\n");
    }
}

void show(int i)
{
    for(int qq = 1;qq<= i;qq++)
    {
        for(int j = 1;j<=qq;j++)
        {
            printf("%dx%d=%2d  ",j,qq,j*qq);
        }
        printf("\n");
    }
}
