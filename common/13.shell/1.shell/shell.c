#include <stdio.h>
#include <string.h>
#include "shell.h"

char    shellLine[100]                  = {SHELL_LINE_MAX_LEN}; /*用于存储从串口接收到的字符串*/
char    *shellParam[SHELL_LINE_MAX_LEN] = {0};                  /*用于存储接收到的参数（包括命令名字）*/

uint8_t shellGetChar(char *recCh)
{
    // char buf[] = "help\r\n test 8,6.5 \r\n";
    // static int test_count = 0;
    
    // if(test_count <= sizeof(buf))
    // {
        // *recCh = buf[test_count++];
        // return 1;
    // }
        
    /*需要自己提供获取一个字符的函数，获取到字符返回1，反之返回0 */
    return 0;
}

void shellSendChar(char ch)
{
    printf("%c", ch);
    /*需要提供发送一个字符的函数*/
}

/*
 *用于从串口获取一条以回车换行结尾的命令
 */
uint8_t shellGetOneLine(char *line, uint8_t maxLen)
{
    char getChar;
    static uint8_t count=0; /*用于记录除特殊字符外的其他有效字符的数量*/ 
    if(shellGetChar(&getChar))
    {
        if(count>=maxLen) /*长度超限*/
        {
            count = 0; /*清零计数器以便后续使用*/
            return 1;  /*返回有效标志*/
        }
        line[count] = getChar; /*记录数据*/
        switch(getChar)
        {   
            case 0x08:
            case 0x7F: /*退格键或者删除键*/
            {
                if(count>0)
                {
                    count--; /*删除上一个接收到的字符*/
                }
            }break;
            
            case '\r':
            case '\n': /*接收到回车换行，证明已经收到一个完整的命令*/
            {
                line[count] = '\0'; /*添加字符串结束符，刚好可以去掉'\r'或者'\n'*/
                count = 0; /*清零计数器以便后续使用*/
                return 1; /*返回有效标志*/
            }break;
            
            default:
                count++;
        }
        shellSendChar(getChar); /*把收到的字符输出到串口*/
    }
    return 0;
}

/*从命令字符串中解析到命令和其参数
 * 获取到的paramArry[0]为要允许的命令名
 * 其他的为命令参数
 * 返回值为获取到的参数的个数（包括一个命令名）
 */
uint8_t shellGetParam(char* line, char *paramArry[], uint8_t arryLen)
{
    uint8_t i,ret;
    char *ptr = NULL;
    ptr = strtok(line, " ");
    for(i=0; ptr!=NULL &&i<arryLen; i++)
    {
        paramArry[i] = ptr;
        ptr = strtok(NULL, ",");
    }
    ret = i;
    return ret;
}

uint8_t shellMain(void)
{
    uint8_t paramNum = 0;

    if(shellGetOneLine(shellLine, SHELL_LINE_MAX_LEN))
    {
        paramNum = shellGetParam(shellLine, shellParam, SHELL_PARAM_MAX_NUM);
        if(paramNum)
        {
            uint8_t i=0;
            for(i=0; sysCmd[i]; i++) /*查找命令名字*/
            {
                if(strcmp(sysCmd[i]->name, shellParam[0]) == 0)
                {
                    int value = sysCmd[i]->fun(paramNum-1, &shellParam[1]); /*运行命令函数*/
                    printf("value %d = 0x%x\r\n", value, value); /*打印运行结果*/
                    return 1;
                }
            }
            if(sysCmd[i] == NULL) /*没有找到命令*/
            {
                printf("C interp: unknown symbol name \'%s\' \r\n",shellLine); /*打印错误信息*/
            }
        }
        printf("->");
    }
    return 0;
}

/*
 * 提供int字符串转int
 */
int shellStr2Int(const char *str, uint8_t* ok)
{
    int ret;
    if(str == NULL)
    {
        ok = 0;
        return 0;
    }
    *ok=(uint8_t)sscanf(str,"%d", &ret);
    if(*ok != 1)
    {
        *ok = 0;
        return 0;
    }
    return ret;
}

/*
 * 提供flaot字符串转浮点数功能
 */
float shellStr2Float(const char *str, uint8_t* ok)
{
    float ret;
    if(str == NULL)
    {
        ok = 0;
        return 0;
    }
    *ok=(uint8_t)sscanf(str,"%f", &ret);
    if(*ok != 1)
    {
        *ok = 0;
        return 0.0;
    }
    return ret;
}

/*
 * 提供16进制字符串转数字的功能
 */
int shellStr2Hex(const char *str, uint8_t* ok)
{
    int ret;
    if(str == NULL)
    {
        ok = 0;
        return 0;
    }
    *ok=(uint8_t)sscanf(str,"%X", &ret);
    if(*ok != 1)
    {
        *ok = 0;
        return 0;
    }
    return ret;
}
