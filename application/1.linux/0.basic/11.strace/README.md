# 自己动手写一个 strace

https://mp.weixin.qq.com/s/TkEVUTX6lGAqwPAS5JkhEQ

https://github.com/liexusong/build-strace-by-myself/blob/main/strace.c

这次主要分享一下一个动手的东西，就是自己动手写一个 `strace` 工具。

用过 `strace` 的同学都知道，`strace` 是用来跟踪进程调用的 `系统调用`，还可以统计进程对 `系统调用` 的统计等。`strace` 的使用方式有两种，如下：

- strace `执行的程序`

- strace -p `进程pid`

第一种用于跟踪将要执行的程序，而第二种用于跟踪一个运行中的进程。

## ptrace系统调用

要自己动手写 `strace` 的第一步就是了解 `ptrace()` 系统调用的使用，我们来看看 `ptrace()` 系统调用的定义：

```
int ptrace(long request, long pid, long addr, long data);
```

`ptrace()` 系统调用用于跟踪进程的运行情况，下面介绍一下其各个参数的含义：

- `request`：指定跟踪的动作。也就是说，通过传入不同的 `request` 参数可以对进程进行不同的跟踪操作。其可选值有：

- `PTRACE_TRACEME`

- `PTRACE_PEEKTEXT`

- `PTRACE_POKETEXT`

- `PTRACE_CONT`

- `PTRACE_SINGLESTEP`

- ...

- `pid`：指定要跟踪的进程PID。

- `addr`：指定要读取或者修改的内存地址。

- `data`：对于不同的 `request` 操作，`data` 有不同的作用，下面会介绍。

前面介绍过，使用 `strace` 跟踪进程有两种方式，一种是通过 `strace` 命令启动进程，另外一种是通过 `-p` 指定要跟踪的进程。

`ptrace()` 系统调用也提供了两种 `request` 来实现上面两种方式：

- 第一种通过 `PTRACE_TRACEME` 来实现

- 第二种通过 `PTRACE_ATTACH` 来实现

本文我们主要介绍使用第一种方式。由于第一种方式使用跟踪程序来启动被跟踪的程序，所以需要启动两个进程。通常要创建新进程可以使用 `fork()` 系统调用，所以自然而然地我们也使用 `fork()` 系统调用。

我们新建一个文件 `strace.c`，输入代码如下：

```
int main(int argc, char *argv[])
```

上面的代码通过调用 `fork()` 来创建一个子进程，但是没有做任何事情。之后，我们就会在 `子进程` 中运行被跟踪的程序，而在 `父进程` 中运行跟踪进程的代码。

## 运行被跟踪程序

前面说过，被跟踪的程序需要在子进程中运行，而要运行一个程序，可以通过调用 `execl()` 系统调用。所以可以通过下面的代码，在子进程中运行 `ls` 命令：

```
#include <unistd.h>
```

`execl()` 用于执行指定的程序，如果执行成功就不会返回，所以 `execl(...)` 的下一行代码 `exit(0)` 不会被执行到。

由于我们需要跟踪 `ls` 命令，所以在执行 `ls` 命令前，必须调用 `ptrace(PTRACE_TRACEME, 0, NULL, NULL)` 来告诉系统需要跟踪这个进程，代码如下：

```
#include <sys/ptrace.h>
```

这样，被跟踪进程部分的代码就完成了，接下来开始编写跟踪进程部分代码。

## 编写跟踪进程代码

如果编译运行上面的代码，会发现什么效果也没有。这是因为当在子进程调用 `ptrace(PTRACE_TRACEME, 0, NULL, NULL)` 后，并且调用 `execl()` 系统调用，那么子进程会发送一个 `SIGCHLD` 信号给父进程（跟踪进程）并且自己停止运行，直到父进程发送调试命令，才会继续运行。

由于上面的代码中，父进程（跟踪进程）并没有发送任何调试命令就退出运行，所以子进程（被跟踪进程）在没有运行的情况下就跟着父进程一起退出了，那么就不会看到任何效果。

现在我们开始编写跟踪进程的代码。

由于被跟踪进程会发送一个 `SIGCHLD` 信息给跟踪进程，所以我们先要在跟踪进程的代码中接收 `SIGCHLD` 信号，接收信号通过使用 `wait()` 系统调用完成，代码如下：

```
#include <sys/ptrace.h>
```

上面的代码通过调用 `wait()` 系统调用来接收被跟踪进程发送过来的 `SIGCHLD` 信号，接下来需要开始向被跟踪进程发送调试命令，来对被跟踪进程进行调试。

由于本文介绍怎么跟踪进程调用了哪些 `系统调用`，所以我们需要使用 `ptrace()` 的 `PTRACE_SYSCALL` 命令，代码如下：

```
#include <sys/ptrace.h>
```

从上面的代码可以发现，我们调用了两次 `ptrace(PTRACE_SYSCALL, child, NULL, NULL)`，这是因为跟踪系统调用时，需要跟踪系统调用前的环境（比如获取系统调用的参数）和系统调用后的环境（比如获取系统调用的返回值），所以就需要调用两次 `ptrace(PTRACE_SYSCALL, child, NULL, NULL)`。

## 获取进程寄存器的值

Linux系统调用是通过 `CPU寄存器` 来传递参数的，所以要想获取调用了哪个系统调用，必须获取进程寄存器的值。获取进程寄存器的值，可以通过 `ptrace()` 系统调用的 `PTRACE_GETREGS` 命令来实现，代码如下：

```
#include <sys/ptrace.h>
```

上面的代码通过调用 `ptrace(PTRACE_GETREGS, child, 0, &regs)` 来获取进程寄存器的值，`PTRACE_GETREGS` 命令需要在 `data` 参数传入类型为 `user_regs_struct` 结构的指针，`user_regs_struct` 结构定义如下（在文件 `sys/user.h` 中）：

```
struct user_regs_struct {
```

其中 `user_regs_struct` 结构的 `orig_rax` 保存了系统调用号，所以我们可以通过 `orig_rax` 的值来知道调用了哪个系统调用。

编译运行上面的代码，会输出结果：`orig_rax: 12`，就是说当前调用的是编号为 12 的系统调用。那么编号为 12 的系统调用是哪个系统调用呢？可以通过下面链接来查看：

> https://www.cnblogs.com/gavanwanggw/p/6920826.html

通过查阅系统调用表，可以知道编号 12 的系统调用为 `brk()`，如下：

```
系统调用号     函数名     入口点     源码
```

上面的程序只跟踪了一个系统调用，那么怎么跟踪所有的系统调用呢？很简单，只需要把跟踪的代码放到一个无限循环中即可。代码如下：

```
#include <sys/ptrace.h>
```

`if (WIFEXITED(status)) ...` 这行代码用于判断子进程（被跟踪进程）是否已经退出，如果退出了就停止跟踪。现在可以编译并运行这个程序，输出结果如下：

```
[root@localhost liexusong]$ ./strace
```

从执行结果来看，只是打印系统调用号不太直观，那么我们怎么优化呢？

我们可以定义一个系统调用号与系统调用名的对应表来实现更清晰的输出结果，如下：

```
#include <sys/ptrace.h>
```

上面例子添加了一个函数 `find_syscall_symbol()` 来获取系统调用号对应的系统调用名，实现也比较简单。编译运行后输出结果如下：

```
[root@localhost liexusong]$ ./strace
```

从执行结果来看，现在可以打印系统调用的名字了，但我们知道 `strace` 命令还会打印系统调用参数的值，我们可以通过 `ptrace()` 系统调用的 `PTRACE_PEEKTEXT` 和 `PTRACE_PEEKDATA` 来获取参数的值，所以有兴趣的就自己实现这个效果了。
