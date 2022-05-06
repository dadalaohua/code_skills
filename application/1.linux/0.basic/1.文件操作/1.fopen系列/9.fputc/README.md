描述
C 库函数 int fputc(int char, FILE *stream) 把参数 char 指定的字符（一个无符号字符）写入到指定的流 stream 中，并把位置标识符往前移动。

声明
下面是 fputc() 函数的声明。
int fputc(int char, FILE *stream)

参数
char -- 这是要被写入的字符。该字符以其对应的 int 值进行传递。
stream -- 这是指向 FILE 对象的指针，该 FILE 对象标识了要被写入字符的流。

返回值
如果没有发生错误，则返回被写入的字符。如果发生错误，则返回 EOF，并设置错误标识符。
