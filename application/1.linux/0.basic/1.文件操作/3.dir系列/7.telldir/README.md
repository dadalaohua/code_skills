# telldir

https://www.man7.org/linux/man-pages/man3/telldir.3.html

## NAME

telldir - return current location in directory stream

telldir - 返回目录流中的当前位置

## SYNOPSIS

```
       #include <dirent.h>

       long telldir(DIR *dirp);

   Feature Test Macro Requirements for glibc (see
   feature_test_macros(7)):

       telldir():
           _XOPEN_SOURCE
              || /* Glibc since 2.19: */ _DEFAULT_SOURCE
              || /* Glibc <= 2.19: */ _BSD_SOURCE || _SVID_SOURCE
```

## DESCRIPTION

The telldir() function returns the current location associated with the directory stream dirp.

telldir()函数返回与目录流dirp相关的当前位置。

## RETURN VALUE

On success, the telldir() function returns the current location in the directory stream.  On error, -1 is returned, and errno is set to indicate the error.

成功时，telldir()函数返回目录流中的当前位置。 出错时，返回-1，并设置`errno`以指示错误。

## ERRORS

### EBADF  

Invalid directory stream descriptor dirp.

无效的目录流描述符dirp。


## ATTRIBUTES

For an explanation of the terms used in this section, seeattributes(7).

关于本节中使用的术语的解释，见attributes(7)。

       ┌──────────────────────────────────────┬───────────────┬─────────┐
       │Interface                             │ Attribute     │ Value   │
       ├──────────────────────────────────────┼───────────────┼─────────┤
       │telldir()                             │ Thread safety │ MT-Safe │
       └──────────────────────────────────────┴───────────────┴─────────┘


## CONFORMING TO

POSIX.1-2001, POSIX.1-2008, 4.3BSD.

## NOTES

In glibc up to version 2.1.1, the return type of telldir() was off_t.  POSIX.1-2001 specifies long, and this is the type used since glibc 2.1.2.

在glibc到2.1.1版本中，`telldir()`的返回类型是`off_t`。 POSIX.1-2001规定为`long`，这是从glibc 2.1.2开始使用的类型。

In early filesystems, the value returned by telldir() was a simple file offset within a directory.  Modern filesystems use tree or hash structures, rather than flat tables, to represent directories.  On such filesystems, the value returned by telldir() (and used internally by readdir(3)) is a "cookie" that is used by the implementation to derive a position within a directory.  Application programs should treat this strictly as an opaque value, making no assumptions about its contents.

在早期的文件系统中，telldir()返回的值是一个目录中简单的文件偏移。 现代文件系统使用树形或哈希结构，而不是平面表来表示目录。 在这样的文件系统中，由`telldir()`返回的值（并由`readdir(3)`在内部使用）是一个 "cookie"，被实现者用来推导目录中的位置。 应用程序应该严格地把它当作一个不透明的值，对其内容不做任何假设。