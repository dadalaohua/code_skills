# closedir

https://www.man7.org/linux/man-pages/man3/closedir.3.html

## NAME

closedir - close a directory

closedir - 关闭一个目录

## SYNOPSIS

```c
#include <sys/types.h>
#include <dirent.h>

int closedir(DIR *dirp);
```

## DESCRIPTION

The closedir() function closes the directory stream associated with dirp.  A successful call to closedir() also closes the underlying file descriptor associated with dirp.  The directory stream descriptor dirp is not available after this call.

closedir()函数关闭了与dirp相关的目录流。 对closedir()的成功调用也关闭了与dirp相关的底层文件描述符。 在这次调用之后，目录流描述符dirp就不可用了。

## RETURN VALUE

The closedir() function returns 0 on success.  On error, -1 is returned, and errno is set to indicate the error.

closedir()函数成功时返回0。 出错时，返回-1，并设置errno以指示错误。

## ERRORS

### EBADF

Invalid directory stream descriptor dirp.

无效的目录流描述符dirp。

## ATTRIBUTES

For an explanation of the terms used in this section, see attributes(7).

关于本节所用术语的解释，见属性（7）。

       ┌──────────────────────────────────────┬───────────────┬─────────┐
       │Interface                             │ Attribute     │ Value   │
       ├──────────────────────────────────────┼───────────────┼─────────┤
       │closedir()                            │ Thread safety │ MT-Safe │
       └──────────────────────────────────────┴───────────────┴─────────┘


## CONFORMING TO

POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.
