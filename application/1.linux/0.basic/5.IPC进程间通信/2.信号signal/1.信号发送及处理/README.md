˵���������в���Ϊ�ź�ֵ����̨����sigreceive signo &���ɻ�øý��̵�ID������Ϊpid��Ȼ������һ�ն�������kill -s signo pid��֤�źŵķ��ͽ��ռ�����ͬʱ������֤�źŵ��Ŷ����⡣

����:
./test_code 10 &

ps
  PID TTY          TIME CMD
22536 pts/2    00:00:00 bash
23492 pts/2    00:00:00 test_code
23493 pts/2    00:00:00 ps

kill -s 10 23492

���Գ�����յ�
receive signal 10

