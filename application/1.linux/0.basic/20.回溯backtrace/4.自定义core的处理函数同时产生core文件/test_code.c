#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <execinfo.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void sigroutine(int signo)
{
    switch (signo){
        case SIGALRM:
            // signal(SIGALRM, sigroutine);
            printf("backtrace failed\n");
            exit(0);
            
            break;
    }
    return;
}

void out_stack(char *sig)
{
    void *array[32];
    size_t size;
    char **strings;
    int i;
    
    printf("%s\n", sig);
    signal(SIGALRM, sigroutine);
    alarm(5);
    size = backtrace (array, 32);
    printf("size %zu\n", size);
    
    strings = backtrace_symbols (array, size);
    alarm(0);
    
    if (NULL == strings) {
        printf("backtrace_symbols\n");
        return ;
    }
    
    for (i = 0; i < size; i++) {
        printf("%s\n",strings[i]);
    }
    
    free(strings);
}

void signal_exit(int dunno) 
{ 
    char* signal_str = "";
    switch (dunno) 
    {
        case 1:
            signal_str = "SIGHUP(1)";
            break;
        case 2:
            signal_str = "SIGINT(2:CTRL_C)"; //CTRL_C
            //out_stack(signal_str);
            break;
        case 3:
            signal_str = "SIGQUIT(3)";
            break;
        case 6:
        {
            signal_str = "SIGABRT(6)";
            out_stack(signal_str);
        }
        break;
        case 9:
            signal_str = "SIGKILL(9)";
            break;
        case 15:
            signal_str = "SIGTERM(15 KILL)"; //kill
            break;
        case 11:
        {
            signal_str = "SIGSEGV(11)"; //SIGSEGV
            out_stack(signal_str);
        }
        break;
        default:
            signal_str = "OTHER";
            break;
    }
    //触发core dump
    signal(dunno, SIG_DFL);
    kill(getpid(), dunno);
    //exit(0);
}

void backtrace_init(void)
{
    signal(SIGHUP, signal_exit); 
    signal(SIGINT, signal_exit);
    signal(SIGQUIT, signal_exit);
    signal(SIGABRT, signal_exit);
    signal(SIGKILL, signal_exit);
    signal(SIGTERM, signal_exit);
    signal(SIGSEGV, signal_exit);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void test3(int n)
{
    char *str;
    printf("in test3 [%d]\n", n);
    strcpy(str, "123");
}

void test2(int n)
{
    printf("in test2 [%d]\n", n);
    test3(3);
}

void test1(int n)
{
    printf("in test1 [%d]\n", n);
    test2(2);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    backtrace_init();
    
    test1(1);
    
/*
 * 该错误会导致无法 backtrace, 参考下列文章
 * Linux 多线程程序调用malloc，backtrace引发死锁问题的调试
 * https://blog.csdn.net/DaliATOM/article/details/78293024
    
    代码中增加了
    signal(SIGALRM, sigroutine);//sigset(SIGALRM, sigroutine);
    alarm(2);
    
    保证在 backtrace 失败后，2秒后超时强行exit
 */
    
    // int val = 666;
    // char buf[100];
    // while(1) {
        // for(int i = 1; i < 10000; i++) {
            // buf[i] = buf[i - 1] + val;
        // }
        // break;
    // }
    // printf("buf %d\n", buf[0]);

    while(1) {
        sleep(1);
    }
    
    return 0;
}