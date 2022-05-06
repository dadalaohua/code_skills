描述
C 库函数 size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) 从给定流 stream 读取数据到 ptr 所指向的数组中。
声明
下面是 fread() 函数的声明。
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
参数
ptr -- 这是指向带有最小尺寸 size*nmemb 字节的内存块的指针。
size -- 这是要读取的每个元素的大小，以字节为单位。
nmemb -- 这是元素的个数，每个元素的大小为 size 字节。
stream -- 这是指向 FILE 对象的指针，该 FILE 对象指定了一个输入流。
返回值
成功读取的元素总数会以 size_t 对象返回，size_t 对象是一个整型数据类型。如果总数与 nmemb 参数不同，则可能发生了一个错误或者到达了文件末尾。
