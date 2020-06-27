描述
C 库函数 char *strtok(char *str, const char *delim) 分解字符串 str 为一组字符串，delim 为分隔符。
声明
下面是 strtok() 函数的声明。
char *strtok(char *str, const char *delim)
参数
str -- 要被分解成一组小字符串的字符串。
delim -- 包含分隔符的 C 字符串。
返回值
该函数返回被分解的第一个子字符串，如果没有可检索的字符串，则返回一个空指针。