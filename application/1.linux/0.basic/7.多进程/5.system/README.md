# system函数：

https://blog.csdn.net/Linux_ever/article/details/50316905

system执行参数中的可执行文件；也是运行起来另外一个进程；

调用该函数会创建一个shell来执行系统命令或可执行文件；父进程被挂起，直到子进程结束且system()调用返回；

```c
#include <stdlib.h>
int system(const char *command);
```

