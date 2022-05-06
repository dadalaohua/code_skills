描述
C 库函数 int fgetc(FILE *stream) 从指定的流 stream 获取下一个字符（一个无符号字符），并把位置标识符往前移动。

声明
下面是 fgetc() 函数的声明。
int fgetc(FILE *stream)

参数
stream -- 这是指向 FILE 对象的指针，该 FILE 对象标识了要在上面执行操作的流。

返回值
该函数以无符号 char 强制转换为 int 的形式返回读取的字符，如果到达文件末尾或发生读错误，则返回 EOF。
