描述
C 库函数 char *strerror(int errnum) 从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针。strerror 生成的错误字符串取决于开发平台和编译器。
声明
下面是 strerror() 函数的声明。
char *strerror(int errnum)
参数
errnum -- 错误号，通常是 errno。
返回值
该函数返回一个指向错误字符串的指针，该错误字符串描述了错误 errnum。