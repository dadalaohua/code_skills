#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sds.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
//创建字符串
//printf 直接就可以打印 sds，这就是说 sds 本身就是 C 语言的字符串类型
//sds 是能兼容 libc 里字符串处理函数 (例如strcpy, strcat...)的
//当不再使用 sds 字符串时，就算是空串，也要通过 sdsfree 销毁字符串
void test_function_1(void)
{
    sds mystr = sdsnew("Hello World!");
    printf("%s\n", mystr);
    sdsfree(mystr);
}

//获取字符串长度
//和 strlen() 有 2 点不同：
//运行时长固定，sds 内部有数据结构保存着字符串的长度
//长度与字符串内是否有 NULL 无关
void test_function_2(void)
{
    char buf[3];
    sds mystring;

    buf[0] = 'A';
    buf[1] = 'B';
    buf[2] = 'C';
    mystring = sdsnewlen(buf,3);
    printf("%s of len %d\n", mystring, (int) sdslen(mystring));
    
    sdsfree(mystring);
}

//拼接字符串
//sdscat 接受的参数是以 NULL 结尾的字符串，如果想摆脱这个限制，可以用 sdscatsds()
void test_function_3(void)
{
    //sdscat
    sds s = sdsempty();
    s = sdscat(s, "Hello ");
    s = sdscat(s, "World!");
    printf("%s\n", s);
    
    sdsfree(s);
    
    //sdscatsds
    sds s1 = sdsnew("aaa");
    sds s2 = sdsnew("bbb");
    s1 = sdscatsds(s1, s2);
    sdsfree(s2);
    printf("%s\n", s1);
    sdsfree(s1);
}

//扩展字符串长度
void test_function_4(void)
{
    sds s = sdsnew("Hello");
    s = sdsgrowzero(s,6);
    s[5] = '!'; /* We are sure this is safe*/
    printf("%s\n", s);
    sdsfree(s);
}

//格式化字符串
void test_function_5(void)
{
    sds s;
    int a = 10, b = 20;
    s = sdsnew("The sum is: ");
    s = sdscatprintf(s, "%d+%d = %d", a, b, a+b);
    printf("%s\n", s);
    sdsfree(s);
}

//截取字符串
//去掉了空格和换行符
void test_function_6(void)
{
    sds s = sdsnew("         my string\n\n  ");
    sdstrim(s," \n");
    printf("-%s-\n",s);
    sdsfree(s);
}

//截取指定范围内的字符串
void test_function_7(void)
{
    sds s = sdsnew("Hello World!");
    sdsrange(s, 1, 4);
    printf("-%s-\n", s);
    sdsfree(s);
}

//字符串分割(Tokenization)
//sdssplitlen() 第3和4个参数指定分割符为空格
void test_function_8(void)
{
    sds *tokens;
    int count, j;

    sds line = sdsnew("Hello World!");
    tokens = sdssplitlen(line, sdslen(line), " ", 1, &count);

    for (j = 0; j < count; j++)
        printf("%s\n", tokens[j]);
    
    sdsfreesplitres(tokens, count);
    sdsfree(line);
}

//字符串合并(String joining)
void test_function_9(void)
{
    char *tokens[3] = {"foo", "bar", "zap"};
    sds s = sdsjoin(tokens, 3, "|");
    printf("%s\n", s);
    sdsfree(s);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    test_function_1();
    test_function_2();
    test_function_3();
    test_function_4();
    test_function_5();
    test_function_6();
    test_function_7();
    test_function_8();
    test_function_9();
    
    return 0;
}