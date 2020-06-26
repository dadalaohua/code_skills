说明，命令行参数为信号值，后台运行sigreceive signo &，可获得该进程的ID，假设为pid，然后再另一终端上运行kill -s signo pid验证信号的发送接收及处理。同时，可验证信号的排队问题。

例如:
./test_code 10 &

ps
  PID TTY          TIME CMD
22536 pts/2    00:00:00 bash
23492 pts/2    00:00:00 test_code
23493 pts/2    00:00:00 ps

kill -s 10 23492

测试程序会收到
receive signal 10

