5、使用 select 来提供精确定时和休眠

int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

　　n 指监视的文件描述符范围，通常设为所要select的fd＋1；readfds，writefds 和 exceptfds分别是读，写和异常文件描述符集；timeout 为超时时间。

　　可能用到的关于文件描述符集操作的宏有：

    FD_CLR(int fd, fd_set *set);   // 清除fd
    FD_ISSET(int fd, fd_set *set); // 测试fd是否设置
    FD_SET(int fd, fd_set *set);   //设置fd
    FD_ZERO(fd_set *set);          //清空描述符集 

　　我们此时用不到这些宏，因为我们并不关心文件描述符的状态，我们关心的是select超时。所以我们需要把 readfds，writefds 和 exceptfds 都设为 NULL，只指定 timeout 时间就行了。至于 n 我们可以不关心，所以你可以把它设为任何非负值。实现代码如下：

 int msSleep(long ms) 
 {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = ms;
​
    return select(0, NULL, NULL, NULL, &tv);
 }

　　怎么样，是不是很简单？ setitimer 和 select 都能实现进程的精确休眠，这里给出了一个简单的基于 select 的实现。我不推荐使用 setitimer，因为 Linux 系统提供的 timer 有限（每个进程至多能设3个不同类型的 timer），而且 setitimer 实现起来没有 select 简单。