编译该程序，并以后台方式运行。
在另一终端向该进程发送信号(运行kill -s 44 pid，SIGRTMIN+10为44)，
查看结果可以看出几个关键函数的运行机制，信号集相关操作比较简单。