#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <execinfo.h>
#include <pthread.h>

/*
 *linux c 程序异常退出时打印堆栈调用信息
 *
 *https://blog.csdn.net/u014608280/article/details/84974877
 */
/************************************************************************/
/*                                                                      */
/************************************************************************/
void out_stack(char *sig);

void signal_exit(int dunno) 
{ 
    char* signal_str = "";
    char dunno_str[10] = {0};
    sprintf(dunno_str, "%d", dunno);
    switch (dunno) 
    {
        case 1:
            signal_str = "SIGHUP(1)";
            break;
        case 2:
            signal_str = "SIGINT(2:CTRL_C)"; //CTRL_C
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
    exit(0);
}

static void output_addrline(char addr[])
{
    char cmd[256];
    char line[256];
    char addrline[32]={0,};
    char *str1, *str2;
    FILE* file;
    
    str1 = strchr(addr,'[');
    str2 = strchr(addr, ']');
    if(str1 == NULL || str2 == NULL)
    {
        return;
    }
    memcpy(addrline, str1 + 1, str2 -str1);
    snprintf(cmd, sizeof(cmd), "addr2line -e /proc/%d/exe %s ", getpid(), addrline);
    file = popen(cmd, "r");
    if(NULL != fgets(line, 256, file)) 
    {
        printf("%s\n", line);
    }
    pclose(file);
}

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
    signal(SIGALRM, sigroutine);//sigset(SIGALRM, sigroutine);
    alarm(2);
    size = backtrace (array, 32);
    printf("size %zu\n", size);
    
    strings = backtrace_symbols (array, size);
    alarm(0);
    
    if (NULL == strings)
    {
        printf("backtrace_symbols\n");
        return ;
    }
    
    for (i = 0; i < size; i++)
    {
        // printf("%s",strings[i]);
        // output_addrline(strings[i]);
        
        printf("%s\n",strings[i]);
        output_addrline(strings[i]);
    }
    free(strings);
}

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
void *func1()/*1秒钟之后退出*/
{
    sleep(1);
    
    // test1(1);
    
    // int val = 666;
    // char buf[100];

    // for(int i = 1; i < 10000; i++) {
        // buf[i] = buf[i - 1] + val;
        // printf("i %d\n", i);
    // }

    // printf("buf %d\n", buf[0]);
    
    void *pc = malloc(1024);
    free(pc);
    free(pc);  //打开注释会导致错误
    
    sleep(1);
    
    printf("线程1（ID：0x%x）退出。\n",(unsigned int)pthread_self());
    pthread_exit((void *)0);
}

int main(int argc, char* argv[])
{
    signal(SIGHUP, signal_exit); 
    signal(SIGINT, signal_exit);
    signal(SIGQUIT, signal_exit);
    signal(SIGABRT, signal_exit);
    signal(SIGKILL, signal_exit);
    signal(SIGTERM, signal_exit);
    signal(SIGSEGV, signal_exit);
    
    pthread_t tid1;

    pthread_create(&tid1, NULL, func1, NULL);
    //test1(1);
    
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