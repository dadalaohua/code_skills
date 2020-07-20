代码1

#include<stdio.h>
int main(void)
{
    printf("%m\n");
    return 0;
}
输出结果：

Success
等价于：

printf("%s\n",stderr(errno));
由于你的代码前面并没有执行出错设置errno，因此errno会是0，而对应的描述信息就是Success。