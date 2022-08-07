#include <stdio.h>

#include <stdlib.h>
#include <execinfo.h>
/*
    gcc -o test_code test_code.c -ldl -Wall -rdynamic
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define _GNU_SOURCE
#include <dlfcn.h>

typedef struct {
   const char *dli_fname;  /* Pathname of shared object that
                              contains address */
   void       *dli_fbase;  /* Base address at which shared
                              object is loaded */
   const char *dli_sname;  /* Name of symbol whose definition
                              overlaps addr */
   void       *dli_saddr;  /* Exact address of symbol named
                              in dli_sname */
} Dl_info;
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
int backtrace(void **buffer, int size);

backtrace() 返回调用程序的回溯（跟踪）信息，存储在由buffer指向的数组中。对于特定程序，backtrace就是一系列当前激活的函数调用（active function call）。

参数
buffer 由buffer指向的数组，每一项都是void*类型，存储的是相应（调用函数的）栈帧的返回地址。
size 指定存储在buffer中的地址最大数量。

返回值
返回buffer中实际地址的数量，应当<=size。如果返回值 < size，那么完整的回溯信息被存储；如果返回值 = size，那么它可能被截断，最旧的栈帧可能没有返回。


char **backtrace_symbols(void *const *buffer, int size);

backtrace() 返回一组地址，backtrace_symbols()象征性地翻译这些地址为一个描述地址的字符串数组。

参数
buffer 一个字符串数组，由backtrace()返回的buffer，每项代表一个函数地址。backtrace_symbols()会用字符串描述每个函数地址，字符串包括：函数名称，一个16进制偏移（offset），实际的返回地址（16进制）。
size 表明buffer中的地址个数。

返回值
成功时，返回一个指向由malloc(3)分配的array；失败时，返回NULl。
arrary是一个二维数组，该数组的每个元素 指向一个代表backtrace()返回的函数地址的符号信息的字符串，数组由函数内部调用malloc分配空间，必须由调用者free。
注意：指向字符串的指针的数组，不必释放，而且不应该释放。应该释放的是返回的二维数组指针。

void backtrace_symbols_fd(void *const *buffer, int size, int fd);

backtrace_symbols_fd()的参数buffer、size同backtrace_symbos()，不同之处在于，backtrace_symbols_fd()并不会返回一个字符串数组给调用者，
而是将字符串写入fd对应文件。backtrace_symbols_fd()也不会调用malloc分配二维数组空间，因此可应用于malloc可能会失败的情形。

注意：

backtrace的实现依赖于栈指针（fp寄存器），编译时，任何非0优化等级（-On），或加入栈指针优化-fomit-frame-pointer参数后，将不能得到正确的程序调用栈信息。
backtrace_symbols的实现需要符号名称的支持，编译时，需要加上-rdynamic选项。
*/
void dump(void)
{
    void *buffer[30] = {0};
    size_t size;
    char **strings = NULL;
    size_t i = 0;

    //int backtrace(void **buffer, int size);
    size = backtrace(buffer, 30);
    fprintf(stdout, "Obtained %zd stack frames.nm\n", size);

    //char **backtrace_symbols(void *const *buffer, int size);
    strings = backtrace_symbols(buffer, size);
    if (strings == NULL) {
        perror("backtrace_symbols.");
        return;
    }

    for (i = 0; i < size; i++) {
        fprintf(stdout, "%s\n", strings[i]);
    }

    free(strings);
    strings = NULL;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    https://gcc.gnu.org/onlinedocs/gcc/Return-Address.html
    void * __builtin_return_address (unsigned int level)
    此函数返回当前函数或其调用者之一的返回地址
    
    https://man7.org/linux/man-pages/man3/dladdr.3.html
    int dladdr(const void *addr, Dl_info *info);
    获取某个地址的符号信息
*/
void task3(void) {
    void* addr = __builtin_return_address(0);
    
    printf("task3 return address %p\n", addr);
    
    Dl_info info;
    dladdr((void*)addr, &info);
    printf("task3 is called of %s\n", info.dli_sname);
    //printf("%s\n", info.dli_fname);
    
    //void backtrace_symbols_fd(void *const *buffer, int size, int fd);
    backtrace_symbols_fd(addr, 1, 1);
    
    dump();
}

void task2(void) {
    task3();
    
    void* addr = __builtin_return_address(0);
    
    printf("task2 return address %p\n", addr);
    
    Dl_info info;
    dladdr((void*)addr, &info);
    printf("task2 is called of %s\n", info.dli_sname);
}

void task1(void) {
    task2();
    
    void* addr = __builtin_return_address(0);
    
    printf("task1 return address %p\n", addr);
    
    Dl_info info;
    dladdr((void*)addr, &info);
    printf("task1 is called of %s\n", info.dli_sname);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    task1();
    return 0;
}