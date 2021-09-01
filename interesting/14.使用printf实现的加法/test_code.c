#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//Since the printf() function returns the number of characters that it prints, we could use this to add numbers as shown below:
//由于printf()函数返回它打印的字符数，我们可以使用它来相加数字如下所示
// int add(int a,int b)
// {
    // if(a!=0&&b!=0)
        // return printf("%*c%*c",a,'r',b,'r');
    // else
        // return a!=0 ? a : b;
// }

//On success, the total number of characters written is returned.
//printf函数在成功调用后，会返回写入的字符总数
//*:The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.
//*用于标示宽度，宽度不是在格式字符串中指定的，而是作为必须格式化的参数前面的一个附加整数值参数。
//下面的示例中，传入的参数a，就是第一个字符0的宽度，传入的参数b，就是第一个字符0的宽度
//所以返回值就是宽度a加上宽度b的总和
int add(int a, int b)
{
    if(a!=0&&b!=0)
        return printf("%*c%*c",a,'0',b,'0');
    else
        return a!=0 ? a : b;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int A = 0, B = 0;
    printf("Enter the two numbers to add\n");
    scanf("%d %d",&A,&B);
    printf("\nRequired sum is %d\n",add(A,B));
    return 0;
}