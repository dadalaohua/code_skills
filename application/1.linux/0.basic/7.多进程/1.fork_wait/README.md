# 多进程函数系列fork(), wait()

https://blog.csdn.net/Linux_ever/article/details/50316905

## fork():
fork()用来创建一个子进程，该子进程是执行该函数的父进程的一个复制的映像；

```c
#include <unistd.h>
pid_t fork(void);
```

注意：fork(）函数有一个特点是一次调用返回两个值；
如果返回值为0，则是子进程；如果返回值大于0，则是父进程（此时返回值就是子进程的PID）;(如果返回值为-1，则创建子进程失败)
问题就在于为什么这个fork()函数会返回两个不同的值呢？？？
当执行了该函数的时候已经创建了一个子进程的进程空间，fork()会在父进程空间返回一个值（子进程PID），同样也会在子进程空间中返回一个值（0）；

## wait():
wait函数是在父进程中使用，用来获取子进程的状态；

```c
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
```

wait系统调用会使父进程暂停执行，直到它的等待的子进程结束为止。也就是说wait是阻塞的。
wait可以返回两个信息，直接返回子进程的PID，还有status（注意这个值不是在子进程中调用exit函数中的退出码，下面有专门的宏使用该status)，子进程的退出状态信息存放在wait的参数status指向的内存中。
WIFEXITED(status)//如果子进程正常退出，那么返回1；见实例输出结果；
WEXITSTATUS(status)//返回子进程的退出码；如果退出码的值很大，那么它只会返回退出码的低八位

```shell
 WIFEXITED(status)
              returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main().
 WEXITSTATUS(status)
        returns  the  exit status of the child.  This consists of the least significant 8 bits of the status argument that the child specified in a
        call to exit(3) or _exit(2) or as the argument for a return statement in main().  This macro should be employed only if WIFEXITED  returned
        true.
 WIFSIGNALED(status)
        returns true if the child process was terminated by a signal.
 WTERMSIG(status)
        returns  the  number  of the signal that caused the child process to terminate.  This macro should be employed only if WIFSIGNALED returned
        true.
 WCOREDUMP(status)
        returns true if the child produced a core dump.  This macro should be employed only if WIFSIGNALED returned true.  This macro is not speci‐
        fied  in POSIX.1-2001 and is not available on some UNIX implementations (e.g., AIX, SunOS).  Only use this enclosed in #ifdef WCOREDUMP ...
        #endif.
 WIFSTOPPED(status)
        returns true if the child process was stopped by delivery of a signal; this is possible only if the call was done using WUNTRACED  or  when
        the child is being traced (see ptrace(2)).
 WSTOPSIG(status)
        returns the number of the signal which caused the child to stop.  This macro should be employed only if WIFSTOPPED returned true.
 WIFCONTINUED(status)
        (since Linux 2.6.10) returns true if the child process was resumed by delivery of SIGCONT.
```



## waitpid():
waitpid用来等待某个特定进程的结束，可以指定等待子进程的PID；

参数options：允许改变waitpid的行为，最有用的一个选项是WNOHANG,它的作用是防止waitpid把调用者的执行挂起，也就是说父进程不会暂停执行；也就是说waitpid此时是非阻塞的：如果pid指定的目标子进程还没有结束或意外终止，则waitpid立即返回0；如果目标子进程确实正常退出了，在返回该子进程的pid。waitpid调用失败时返回-1并设置errno。

如果waitpid函数中的pid为-1，那么它就和wait函数一样，即等待任意一个子进程结束。

参数的status的含义是一样的。


