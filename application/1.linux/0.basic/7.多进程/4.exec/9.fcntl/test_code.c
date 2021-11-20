#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//
//int fcntl(int fd, int cmd, ... /* arg */ );
//
//File descriptor flags
//      The following commands manipulate the  flags  associated  with  a  file
//      descriptor.   Currently, only one such flag is defined: FD_CLOEXEC, the
//      close-on-exec flag.  If the FD_CLOEXEC bit is 0,  the  file  descriptor
//      will remain open across an execve(2), otherwise it will be closed.
//
//     //如果FD_CLOEXEC标识位为0，则通过execve调用后fd依然是打开的，否则为关闭的
//
//      F_GETFD (void)
//             Read the file descriptor flags; arg is ignored.
//
//      F_SETFD (long)
//             Set the file descriptor flags to the value specified by arg.
//
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("Entering main ...\n");
    int ret = fcntl(1, F_SETFD, FD_CLOEXEC);    //1关闭（标准输出关闭）
    if (ret == -1)
        perror("fcntl error");
    int val;
    val =execlp("ls", "ls", "-l", NULL);    //由于标准输出被关闭，ls -l无法将结果显示在标准输出，提示ls: write error: Bad file descriptor
    if(val == -1)
        perror("execl error");
    printf("Exiting main ...\n");
    
    return 0;
}