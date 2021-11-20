#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <errno.h>
 
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
可以使用ipcs命令时，查看消息队列、共享内存以及信号量相关的信息

使用ipcrm -q msqid命令释放指定id的消息队列资源
例如：ipcrm -q 98305
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define PATHNAME    "../README.md"  //路径名
#define PROJ_ID     0x6666          //整数标识符
#define SIZE        4096            //共享内存的大小

#define MAX_TEXT 512
 
struct msg_st
{
    long int msg_type;
    char text[MAX_TEXT];
};

int main(int argc, char* argv[])
{
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0;   // 表示获取队列中第一个可用的消息
    
    key_t key = ftok(PATHNAME, PROJ_ID); //获取key值
    if (key < 0) {
        perror("ftok");
        return 1;
    }
 
    // 建立消息队列
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed width error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
 
    // 从队列中获取消息，直到遇到end消息为止
    while (1)
    {
        if (msgrcv(msgid, (void *)&data, BUFSIZ, msgtype, 0) == -1)
        {
            fprintf(stderr, "msgrcv failed width erro: %d", errno);
        }
 
        printf("You wrote: %s\n", data.text);
 
        // 遇到end结束
        if (strncmp(data.text, "end", 3) == 0)
        {
            break;
        }
    }
 
    // 删除消息队列
    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
    }
 
    exit(EXIT_SUCCESS);

    return 0;
}
