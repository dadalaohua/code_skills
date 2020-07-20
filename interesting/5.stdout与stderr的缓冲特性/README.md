代码3

#include <stdio.h>
#include <unistd.h>
int main(void)  
{
    while(1)
    {
        fprintf(stdout,"一号打印");
        fprintf(stderr,"二号输出");
        sleep(10);
    }
    return 0;
}
输出结果：

二号输出二号输出二号输出

为什么不会输出一号打印呢？原因在于标准输入默认是行缓冲，而标准错误是无缓冲。