# opendir

https://www.man7.org/linux/man-pages/man3/opendir.3.html

## NAME

opendir, fdopendir - open a directory

opendir, fdopendir - 打开一个目录

## SYNOPSIS

```
       #include <sys/types.h>
       #include <dirent.h>

       DIR *opendir(const char *name);
       DIR *fdopendir(int fd);

   Feature Test Macro Requirements for glibc (see
   feature_test_macros(7)):

       fdopendir():
           Since glibc 2.10:
               _POSIX_C_SOURCE >= 200809L
           Before glibc 2.10:
               _GNU_SOURCE
```

## DESCRIPTION

The opendir() function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.  The stream is positioned at the first entry in the directory.
opendir() 函数打开一个目录名对应的目录流，并返回一个指向目录流的指针。 流位于目录中的第一个条目。
The fdopendir() function is like opendir(), but returns a directory stream for the directory referred to by the open file descriptor fd.  After a successful call to fdopendir(), fd is used internally by the implementation, and should not otherwise be used by the application.

fdopendir() 函数类似于 opendir()，但返回一个目录流，用于打开文件描述符 fd 所引用的目录。 在成功调用 fdopendir() 后，fd 由实现在内部使用，并且不应由应用程序使用。


## RETURN VALUE

The opendir() and fdopendir() functions return a pointer to the directory stream.  On error, NULL is returned, and errno is set to indicate the error.

opendir() 和 fdopendir() 函数返回一个指向目录流的指针。 出错时返回 NULL，并设置 errno 以指示错误。

## ERRORS

### EACCES

Permission denied.

没有权限。

### EBADF

fd is not a valid file descriptor opened for reading.

fd 不是为读取而打开的有效文件描述符。

### EMFILE

The per-process limit on the number of open file descriptors has been reached.

已达到打开文件描述符数量的每个进程限制。

### ENFILE

The system-wide limit on the total number of open files has been reached.

已达到打开文件总数的系统范围限制。

### ENOENT

Directory does not exist, or name is an empty string.

目录不存在，或名称为空字符串。

### ENOMEM

Insufficient memory to complete the operation.

内存不足，无法完成操作。

### ENOTDIR

name is not a directory.

name 不是目录。


## VERSIONS

fdopendir() is available in glibc since version 2.4.

fdopendir()在glibc中从2.4版本开始可用。

## ATTRIBUTES

For an explanation of the terms used in this section, see attributes(7).

关于本节所用术语的解释，见属性（7）。    

       ┌──────────────────────────────────────┬───────────────┬─────────┐
       │Interface                             │ Attribute     │ Value   │
       ├──────────────────────────────────────┼───────────────┼─────────┤
       │opendir(), fdopendir()                │ Thread safety │ MT-Safe │
       └──────────────────────────────────────┴───────────────┴─────────┘


## CONFORMING TO

opendir() is present on SVr4, 4.3BSD, and specified in POSIX.1-2001.  fdopendir() is specified in POSIX.1-2008.

opendir()出现在SVr4，4.3BSD中，并在POSIX.1-2001中指定。 fdopendir()在POSIX.1-2008中指定。

## NOTES

Filename entries can be read from a directory stream using readdir(3).

文件名条目可以用 readdir(3) 从目录流中读取。

The underlying file descriptor of the directory stream can be obtained using dirfd(3).

目录流的底层文件描述符可以用dirfd(3)获得。

The opendir() function sets the close-on-exec flag for the file descriptor underlying the DIR * .  The fdopendir() function leaves the setting of the close-on-exec flag unchanged for the file descriptor, fd.  POSIX.1-200x leaves it unspecified whether a successful call to fdopendir() will set the close-on-exec flag for the file descriptor, fd.

opendir()函数为DIR *的底层文件描述符设置了执行时关闭的标志。 fdopendir()函数对文件描述符fd的执行时关闭标志的设置保持不变。 POSIX.1-200x没有说明成功调用fdopendir()是否会设置文件描述符fd的执行时关闭标志。