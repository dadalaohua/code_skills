代码0：

#include<stdio.h>
int main(void)
{
    int c = 5;
    switch(c)
    {
        case 0 ... 10:
            printf("0-->10\n");
            break;
        case 11 ... 20:
            printf("11-->20\n");
            break;
        default:
            printf("other\n");
    }
    return 0;
}
输出结果：

0-->10
以上特性被常见编译器支持，但是标准中并未提到。