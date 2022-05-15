# rewinddir

https://www.man7.org/linux/man-pages/man3/rewinddir.3.html

## NAME

rewinddir - reset directory stream

rewinddir - 重置目录流

## SYNOPSIS

```c
#include <sys/types.h>
#include <dirent.h>

void rewinddir(DIR *dirp);
```

## DESCRIPTION

The `rewinddir()` function resets the position of the directory stream `dirp` to the beginning of the directory.

`rewinddir()`函数将目录流`dirp`的位置重置为目录的开始。

## RETURN VALUE

The `rewinddir()` function returns no value.

`rewinddir()`函数没有返回值。

## ATTRIBUTES

For an explanation of the terms used in this section, see attributes(7).

关于本节所用术语的解释，见属性（7）。

       ┌──────────────────────────────────────┬───────────────┬─────────┐
       │Interface                             │ Attribute     │ Value   │
       ├──────────────────────────────────────┼───────────────┼─────────┤
       │rewinddir()                           │ Thread safety │ MT-Safe │
       └──────────────────────────────────────┴───────────────┴─────────┘


## CONFORMING TO

POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.