代码2

#include<stdio.h>
int main(void)
{
    int i = 10;
    printf("%zu\n",sizeof(i++));
    printf("%zu\n",sizeof(++i));
    printf("%d\n",i);
    return 0;
}
输出结果：

4
4
10
sizeof实际作用的对象是类型。sizeof中的表达式本身并不会被执行。