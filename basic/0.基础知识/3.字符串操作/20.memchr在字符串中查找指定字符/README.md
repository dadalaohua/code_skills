描述
C 库函数 void *memchr(const void *str, int c, size_t n) 在参数 str 所指向的字符串的前 n 个字节中搜索第一次出现字符 c（一个无符号字符）的位置。
声明
下面是 memchr() 函数的声明。
void *memchr(const void *str, int c, size_t n)
参数
str -- 指向要执行搜索的内存块。
c -- 以 int 形式传递的值，但是函数在每次字节搜索时是使用该值的无符号字符形式。
n -- 要被分析的字节数。
返回值
该函数返回一个指向匹配字节的指针，如果在给定的内存区域未出现字符，则返回 NULL。
