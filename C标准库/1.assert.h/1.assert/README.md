# C 库宏 - assert()
## 描述
C 库宏 **void assert(int expression)** 允许诊断信息被写入到标准错误文件中。换句话说，它可用于在 C 程序中添加诊断。
## 声明
下面是 assert() 宏的声明。
```c
void assert(int expression);
```
## 参数
- **expression** --  这可以是一个变量或任何 C 表达式。如果 **expression** 为 TRUE，assert() 不执行任何动作。如果 **expression** 为 FALSE，assert() 会在标准错误 stderr 上显示错误消息，并中止程序执行。
## 返回值
这个宏不返回任何值。