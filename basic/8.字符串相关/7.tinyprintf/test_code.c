#include <stdio.h>
#include <unistd.h>

#define TINYPRINTF_DEFINE_TFP_PRINTF 1
#define TINYPRINTF_DEFINE_TFP_SPRINTF 1
#define TINYPRINTF_OVERRIDE_LIBC 0

#include "tinyprintf.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
static void stdout_putf(void *unused, char c)
{
    (void)(unused);
    putchar(c);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
该实现支持的格式是:
'c' 'd' 'i' 'o' 'p' 'u' 's' 'x' 'X'.
*/
int main(int argc, char* argv[])
{
    //取代标准库的printf
    
    //初始化
    init_printf(NULL, stdout_putf);
    
    //把111打印出来
    tfp_printf("%d\n", 111); //产生"111"
    tfp_printf("%i\n", 111); //产生"111"
    tfp_printf("%u\n", 111); //产生"111"
    
    //把-111打印出来
    tfp_printf("%d\n", -111); //产生"-111"
    tfp_printf("%i\n", -111); //产生"-111"
    tfp_printf("%u\n", -111); //产生"4294967185"

    //把整数123 整数4567 打印出来。不足的左边补空格
    tfp_printf("%4d%4d\n", 123,4567); //产生：“ 1234567"
    
    //两个整数形成带小数点的字符串，极大的方便了不支持做浮点运算，且需要小数点
    tfp_printf("%d%c%d\n", 1,'.',345); //产生：1.345
    
    //不支持浮点型数据，只能用上面的方法
    tfp_printf("%4.2f\n", 1234.244); //产生：““
    
    //输出字符
    tfp_printf("%c %c\n", 'G', 'O'); //产生：“G O“
    
    //输出字符串
    tfp_printf("%s\n", "Hello World"); //产生：“Hello World“
    
    int val = 15;
    //输出八进制
    tfp_printf("%o\n", val); //产生：“17“
    //输出小写十六进制
    tfp_printf("%x\n", val); //产生：“f“
    //输出大写十六进制
    tfp_printf("%X\n", val); //产生：“F“
    //输出地址
    tfp_printf("%p\n", &val); //产生：“0x7ffff98fbf38“
    
/************************************************************************/
    //取代标准库的snprintf
    
    char str[10] = {0};
    
    //取代标志库的sprintf
    
    //把111存储到了str数组中，存储为“111”
    tfp_sprintf(str, "%d", 111); //产生"111"
    
    printf("test 1:%s\n", str);

    //把整数123 整数4567 打印成一个字符串保存在str 中。不足的左边补空格
    tfp_sprintf(str, "%4d%4d", 123,4567); //产生：“ 1234567"
    
    printf("test 2:%s\n", str);
    
    //两个整数形成带小数点的字符串，极大的方便了不支持做浮点运算，且需要小数点
    tfp_sprintf(str, "%d%c%d", 1,'.',345); //产生：1.345
    
    printf("test 3:%s\n", str);
    
    //不支持浮点型数据，只能用上面的方法
    tfp_sprintf(str, "%4.2f", 1234.244); //产生：““
    
    printf("test 4:%s\n", str);

    
/************************************************************************/
    //取代标准库的snprintf

    //把111存储到了str数组中，存储为“111”
    tfp_snprintf(str, 10, "%d", 111); //产生"111"
    
    printf("test 1:%s\n", str);

    //把整数123 整数4567 打印成一个字符串保存在str 中。不足的左边补空格
    tfp_snprintf(str, 10, "%4d%4d", 123,4567); //产生：“ 1234567"
    
    printf("test 2:%s\n", str);
    
    //两个整数形成带小数点的字符串，极大的方便了不支持做浮点运算，且需要小数点
    tfp_snprintf(str, 10, "%d%c%d", 1,'.',345); //产生：1.345
    
    printf("test 3:%s\n", str);
    
    //不支持浮点型数据，只能用上面的方法
    tfp_snprintf(str, 10, "%4.2f", 1234.244); //产生：““
    
    printf("test 4:%s\n", str);
    
    return 0;
}