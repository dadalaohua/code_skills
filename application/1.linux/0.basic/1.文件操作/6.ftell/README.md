描述
C 库函数 long int ftell(FILE *stream) 返回给定流 stream 的当前文件位置。

声明
下面是 ftell() 函数的声明。
long int ftell(FILE *stream)

参数
stream -- 这是指向 FILE 对象的指针，该 FILE 对象标识了流。

返回值
该函数返回位置标识符的当前值。如果发生错误，则返回 -1L，全局变量 errno 被设置为一个正值。
