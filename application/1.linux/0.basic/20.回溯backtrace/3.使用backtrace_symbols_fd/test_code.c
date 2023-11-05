#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <execinfo.h>

#define USE_BACKTRACE_SYMBOLS_FD

//函数原型
//void backtrace_symbols_fd(void *const *buffer, int size, int fd);
//backtrace_symbols_fd()的参数buffer、size同backtrace_symbos()，
//不同之处在于，backtrace_symbols_fd()并不会返回一个字符串数组给调用者，
//而是将字符串写入fd对应文件。
//backtrace_symbols_fd()也不会调用malloc分配二维数组空间，
//因此可应用于malloc可能会失败的情形。

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
#ifndef USE_BACKTRACE_SYMBOLS_FD
    char **strings;
    int i;
#endif
    printf("%s\n", sig);
    signal(SIGALRM, sigroutine);
    alarm(5);
    size = backtrace (array, 32);
    printf("size %zu\n", size);
    
#ifdef USE_BACKTRACE_SYMBOLS_FD
    backtrace_symbols_fd(array, size, STDOUT_FILENO);
    alarm(0);
#else
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
#endif
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
    // signal(dunno, SIG_DFL);
    // kill(getpid(), dunno);
    exit(0);
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
    
    https://blog.csdn.net/qq_34548075/article/details/122601857
    backtrace()和backtrace_symbols_fd()不显式调用malloc()，
    但它们是libgcc的一部分，libgcc第一次使用时会动态加载。
    动态加载通常会触发对malloc的调用。
    如果需要对这两个函数进行某些调用而不分配内存（例如，在信号处理程序中），
    则需要确保事先加载libgcc。
    
    代码中增加了
    signal(SIGALRM, sigroutine);//sigset(SIGALRM, sigroutine);
    alarm(5);
    
    保证在 backtrace 失败后，5秒后超时强行exit
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