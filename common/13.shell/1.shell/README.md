# shell

在shell.c中
```c
uint8_t shellGetChar(char *recCh); /*需要自己提供获取一个字符的函数，获取到字符返回1，反之返回0 */
void shellSendChar(char ch); /*需要提供发送一个字符的函数*/
```
添加发送与接收函数

在shell_cmd.c中
添加用户自定义函数
最后还要添加到sysCmd中
