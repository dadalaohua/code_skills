# 父进程用SIGCHLD来处理子进程


https://blog.csdn.net/Linux_ever/article/details/50316905
我们知道在事件已经发生的情况下执行非阻塞的调用才能提高程序的效率。对于waitpid函数而言，我们最好在某个子进程退出之后再调用它。那么父进程怎么知道子进程退出了呢？这个可以靠信号SIGCHLD来解决。当一个进程结束时，它将给其父进程发送一个SIGCHLD信号。我们可以在父进程中捕获SIGCHLD信号，并在信号处理函数中调用非阻塞的waitpid以彻底结束一个子进程。
