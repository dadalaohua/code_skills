代码4

#include <stdio.h>
int main(void)  
{
    printf("%c\n",4["hello world"]);
    return 0;
}
输出结果：

o
等价于：

char *str = "hello world";
printf("%c\n",str[4]);