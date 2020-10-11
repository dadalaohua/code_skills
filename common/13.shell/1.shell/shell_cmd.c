#include <stdio.h>
#include "shell.h"

int helpCmdFun(int argc, char*argv[]) /*命令函数*/
{
    uint8_t i;
    for(i = 0; sysCmd[i]; i++)
    {
        printf("%-15s %s\r\n",sysCmd[i]->name, sysCmd[i]->help);
    }
    
    return 0;
}
T_ShellCmd helpCmd= /*命令描述*/
{
    .name = "help",
    .help = "show all cmd list",
    .fun = helpCmdFun
};

/*例程，此例程序可以接收两个参数，int a，float b*/
int paramTestCmdFun(int argc, char *argv[]) /*命令函数*/
{
    uint8_t reti,retf;
    int vali;
    float valf;
    printf("get param num %d\r\n", argc); /*如果用户输入的参数不够cmd函数使用，将传入一个默认的地址，其内容为 '\0' */
    vali = shellStr2Int(argv[0], &reti); /*提供的字符串转int函数*/
    valf = shellStr2Float(argv[1], &retf); /**/
    printf("int[%d]:%d\r\n", reti,vali );
    printf("float[%d]:%f\r\n",retf,valf );
    return argc;
}
T_ShellCmd paramTestCmd = /*命令描述结构体*/
{
    .name= "test",
    .help = "(int a=0, float b=0) show tow param val", /*参数提示,使用函数参数书写方式，有等于号表明默认参数，无参数不提示参数项*/ 
    .fun = paramTestCmdFun
};

T_ShellCmd *sysCmd[] = 
{
    &helpCmd, /*只存放命令结构体的指针减少对存储的占用*/
    &paramTestCmd, /*按照help的方式建立的其他命令*/
    NULL /*用于标记命令数组的结尾*/
};
