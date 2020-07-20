代码4

#include <stdio.h>
int main(void)  
{
    int a = 10;
    switch(a)
    {
        int b = 20;
        case 10:
            printf("%d\n",a + b);
            break;
        default:
            printf("%d\n",a + b);
            break;
    }
    return 0;
}
输出结果：

10
switch中的int b = 20，并不会被执行，你编译时就会发现有警告。

在gcc下编译不会报错，b不会被初始化，会是一个随机数值