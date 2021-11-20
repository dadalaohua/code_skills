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
    struct msg_st data;
    char buffer[BUFSIZ];
    int msgid = -1;
    
    key_t key = ftok(PATHNAME, PROJ_ID); //获取与server进程相同的key值
    if (key < 0) {
        perror("ftok");
        return 1;
    }
 
    // 建立消息队列
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
 
    // 向消息队里中写消息，直到写入end
    while (1)
    {
        printf("Enter some text: \n");
        fgets(buffer, BUFSIZ, stdin);
        data.msg_type = 1; //设置发送的信息的信息类型，即其发送的信息的类型为1
        strcpy(data.text, buffer);
 
        // 向队列里发送数据
        if (msgsnd(msgid, (void *)&data, MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
 
        // 输入end结束输入
        if (strncmp(buffer, "end", 3) == 0)
        {
            break;
        }
 
        sleep(1);
    }
 
    exit(EXIT_SUCCESS);
    
    return 0;
}