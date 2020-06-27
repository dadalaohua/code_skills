描述
C 库函数 void *memcpy(void *str1, const void *str2, size_t n) 从存储区 str2 复制 n 个字节到存储区 str1。
声明
下面是 memcpy() 函数的声明。
void *memcpy(void *str1, const void *str2, size_t n)
参数
str1 -- 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。
str2 -- 指向要复制的数据源，类型强制转换为 void* 指针。
n -- 要被复制的字节数。
返回值
该函数返回一个指向目标存储区 str1 的指针。