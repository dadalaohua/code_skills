描述
C 库函数 int fputs(const char *str, FILE *stream) 把字符串写入到指定的流 stream 中，但不包括空字符。

声明
下面是 fputs() 函数的声明。
int fputs(const char *str, FILE *stream)

参数
str -- 这是一个数组，包含了要写入的以空字符终止的字符序列。
stream -- 这是指向 FILE 对象的指针，该 FILE 对象标识了要被写入字符串的流。

返回值
该函数返回一个非负值，如果发生错误则返回 EOF。
