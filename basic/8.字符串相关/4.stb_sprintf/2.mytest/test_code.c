#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define STB_SPRINTF_IMPLEMENTATION

#include "stb_sprintf.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char str[10] = {0};
    
    //stbsp_sprintf用于取代sprintf
    
    //把111存储到了str数组中，存储为“111”
    stbsp_sprintf(str, "%d", 111); //产生"111"
    
    printf("test 1:%s\n", str);

    //把整数123 整数4567 打印成一个字符串保存在str 中。不足的左边补空格
    stbsp_sprintf(str, "%4d%4d", 123,4567); //产生：“ 1234567"
    
    printf("test 2:%s\n", str);
    
    //两个整数形成带小数点的字符串，极大的方便了不支持做浮点运算，且需要小数点
    stbsp_sprintf(str, "%d%c%d", 1,'.',345); //产生：1.345
    
    printf("test 3:%s\n", str);
    
    //一个浮点型数据形成浮点型字符串
    stbsp_sprintf(str, "%4.2f", 1234.244); //产生：“1234.24“
    
    printf("test 4:%s\n", str);
    
    //一个浮点型数据形成浮点型字符串，后添加单位
    stbsp_sprintf(str, "%4.2f%s", 1234.244,"cm"); //产生：“1234.24cm”
    
    printf("test 5:%s\n", str);
    
/************************************************************************/
    //stbsp_snprintf用于取代snprintf

    //把111存储到了str数组中，存储为“111”
    stbsp_snprintf(str, 10, "%d", 111); //产生"111"
    
    printf("test 1:%s\n", str);

    //把整数123 整数4567 打印成一个字符串保存在str 中。不足的左边补空格
    stbsp_snprintf(str, 10, "%4d%4d", 123,4567); //产生：“ 1234567"
    
    printf("test 2:%s\n", str);
    
    //两个整数形成带小数点的字符串，极大的方便了不支持做浮点运算，且需要小数点
    stbsp_snprintf(str, 10, "%d%c%d", 1,'.',345); //产生：1.345
    
    printf("test 3:%s\n", str);
    
    //一个浮点型数据形成浮点型字符串
    stbsp_snprintf(str, 10, "%4.2f", 1234.244); //产生：“1234.24“
    
    printf("test 4:%s\n", str);
    
    //一个浮点型数据形成浮点型字符串，后添加单位
    stbsp_snprintf(str, 10, "%4.2f%s", 1234.244,"cm"); //产生：“1234.24cm”
    
    printf("test 5:%s\n", str);
    
    return 0;
}