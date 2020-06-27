描述
C 库函数 int memcmp(const void *str1, const void *str2, size_t n)) 把存储区 str1 和存储区 str2 的前 n 个字节进行比较。
声明
下面是 memcmp() 函数的声明。
int memcmp(const void *str1, const void *str2, size_t n)
参数
str1 -- 指向内存块的指针。
str2 -- 指向内存块的指针。
n -- 要被比较的字节数。
返回值
如果返回值 < 0，则表示 str1 小于 str2。
如果返回值 > 0，则表示 str2 小于 str1。
如果返回值 = 0，则表示 str1 等于 str2。
