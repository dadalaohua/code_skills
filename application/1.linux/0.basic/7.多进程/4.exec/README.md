# exec系列函数

https://blog.csdn.net/Linux_ever/article/details/50316905

当我们调用fork()创建了一个进程之后，通常将子进程替换成新的进程映象，这可以用exec系列的函数来进行。当然，exec系列的函数也可以将当前进程替换掉。

```c
#include <unistd.h>
extern char **environ;

int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ..., char * const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *file, char *const argv[], char *const envp[]);
```

总结：函数名字中l(函数中的字母l不是数字1)代表可变参数列表，函数名字中p代表在path环境变量中搜索file文件。envp代表环境变量
