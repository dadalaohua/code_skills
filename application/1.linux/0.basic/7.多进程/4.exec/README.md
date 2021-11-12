# exec系列函数

https://blog.csdn.net/Linux_ever/article/details/50316905

当我们调用fork()创建了一个进程之后，通常将子进程替换成新的进程映象，这可以用exec系列的函数来进行。exec系列的函数会将当前进程替换掉。

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



```c
#include <unistd.h>

int execve(const char *filename, char *const argv[], char *const envp[]);
```



```c
#include <unistd.h>

int fexecve(int fd, char *const argv[], char *const envp[]);
```



总结：函数名字中l(函数中的字母l不是数字1)代表可变参数列表，函数名字中p代表在path环境变量中搜索file文件。envp代表环境变量

**函数返回值：**

成功： 函数不会返回

出错： 返回-1，失败原因记录在error中。

**函数之间的区别是：**

**这些函数之间的第一个区别就是execl、execle、execv函数取路径作为参数，execlp、execvp、execvpe取文件名作为参数，当指定的filaname作为参数时：**
1、如果filename中包含/，则将视为路径名
2、如果不包含/，则按照PATH环境变量，在它所指定的各个目录中搜寻可执行文件。
**第二个区别与参数表的传递有关（l表示列表list，v表示矢量vector）**
1、函数execl、execlp、execle要求将新程序的每个命令行参数都说明为一个单独的参数，这种参数以空指针结束。
2、函数execv、execvp、execvpe应该先构造一个指向各个参数的指针数组，然后将该数组的地址作为函数的参数。
在使用ISO C原型之前，对execl、execle、execlp三个函数的表示命令行参数的一般方法是：
char *arg0, char *arg1, ..., char *argn, (char *)0
需要在最后一个命令行参数之后跟一个char *的空指针，比如上面的表示方法(char *)0
如果不转换成(char *)的指针，那么exec函数的实际参数出错。
**第三个区别与向新程序传递环境表有关。**
1、execle可以传递一个直线环境字符串指针数组的指针
2、其他的函数则使用进程中的environ变量为新程序复制现有的环境。
通常，一个进程允许将其中环境传播给器子程序，但有时也会有，进程想要为子进程指定某一个确定的环境。在使用ISO C原型之前，execle的参数是：

```c
char *path, char *arg0, ..., char *argn, (char *)0, char *envp[]
```



所以，最后一个参数时指向环境字符串的各个字符串构成的数组的指针
**关于exec函数，其中名称中的不同字符代表不同的意思：**
1、字母p标识改函数去filename作为参数，并且用PATH环境变量寻找你可执行的文件。
2、字母l表示该函数取一个参数表，与字母v互斥，v表示该函数取一个argv[]矢量。
3、字母e表示该函数取envp[]数组，而不是用当前环境。

在这种安排中，库函数execlp和execvp使用PATH环境变量，查找、第一个包含名为filename的可置信文件的路径名前缀，fexecv库函数使用/proc吧文件描述符参数转换为路径名，execve用该路径去执行程序。
https://blog.csdn.net/songshuai0223/article/details/88175377
