#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 64

int main(int argc, char* argv[])
{ 
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];
    char test[] = "test\n";

    write(STDOUT_FILENO, test, sizeof(test));
    
    if(pipe(fd) != 0){                 /* 先建立管道得到一对文件描述符 */
        printf("pipe(fd) != 0\n");
        exit(0);
    }
    
    pid = fork();

    if(pid == -1){            /* 父进程把文件描述符复制给子进程 */
        printf("fork error\n");
        exit(1);
    }
    else if(pid > 0){                /* 父进程写 */
        close(fd[0]);                /* 关闭读描述符 */
        write(fd[1], "\nhello world\n", 14);    /*fd[1]用于写入数据，写入时必须关闭读取端，即close(fd[0])。*/
    }
    else{                            /* 子进程读 */
        close(fd[1]);                /* 关闭写端 */
        n = read(fd[0], line, MAXLINE);    /*fd[0]用于读出数据，读取时必须关闭写入端，即close(fd[1])。*/
        write(STDOUT_FILENO, line, n);
    }
    
    exit(0);

    return 0;
}