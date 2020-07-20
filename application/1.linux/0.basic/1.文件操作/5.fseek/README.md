描述
C 库函数 int fseek(FILE *stream, long int offset, int whence) 设置流 stream 的文件位置为给定的偏移 offset，参数 offset 意味着从给定的 whence 位置查找的字节数。

声明
下面是 fseek() 函数的声明。
int fseek(FILE *stream, long int offset, int whence)

参数
stream -- 这是指向 FILE 对象的指针，该 FILE 对象标识了流。
offset -- 这是相对 whence 的偏移量，以字节为单位。
whence -- 这是表示开始添加偏移 offset 的位置。它一般指定为下列常量之一：

常量              描述
SEEK_SET        文件的开头
SEEK_CUR        文件指针的当前位置
SEEK_END        文件的末尾

返回值
如果成功，则该函数返回零，否则返回非零值。
