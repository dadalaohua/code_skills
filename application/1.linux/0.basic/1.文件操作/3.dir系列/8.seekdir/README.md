# seekdir

https://www.man7.org/linux/man-pages/man3/seekdir.3.html

## NAME

seekdir - set the position of the next readdir() call in the directory stream.

seekdir - 设置下一次 readdir() 调用在目录流中的位置。

## SYNOPSIS

```
       #include <dirent.h>

       void seekdir(DIR *dirp, long loc);

   Feature Test Macro Requirements for glibc (see
   feature_test_macros(7)):

       seekdir():
           _XOPEN_SOURCE
               || /* Glibc since 2.19: */ _DEFAULT_SOURCE
               || /* Glibc <= 2.19: */ _BSD_SOURCE || _SVID_SOURCE
```

## DESCRIPTION

The seekdir() function sets the location in the directory stream from which the next readdir(2) call will start.  The loc argument should be a value returned by a previous call to telldir(3).

seekdir() 函数设置了目录流中的位置，下一次 readdir(2) 调用将从这个位置开始。 loc 参数应该是先前调用 telldir(3) 所返回的值。

## RETURN VALUE

The seekdir() function returns no value.

seekdir()函数不返回任何值。

## ATTRIBUTES

For an explanation of the terms used in this section, see attributes(7).

关于本节所用术语的解释，见属性（7）。

       ┌──────────────────────────────────────┬───────────────┬─────────┐
       │Interface                             │ Attribute     │ Value   │
       ├──────────────────────────────────────┼───────────────┼─────────┤
       │seekdir()                             │ Thread safety │ MT-Safe │
       └──────────────────────────────────────┴───────────────┴─────────┘


## CONFORMING TO

POSIX.1-2001, POSIX.1-2008, 4.3BSD.

## NOTES

In glibc up to version 2.1.1, the type of the loc argument was off_t.  POSIX.1-2001 specifies long, and this is the type used since glibc 2.1.2.  See telldir(3) for information on why you should be careful in making any assumptions about the value in this argument.

在2.1.1版之前的glibc中，loc参数的类型是off_t。 POSIX.1-2001规定为long，这是从glibc 2.1.2开始使用的类型。 参见telldir(3)，以了解为什么在对这个参数的值做任何假设时要小心。