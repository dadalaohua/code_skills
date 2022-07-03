# scandir

https://www.man7.org/linux/man-pages/man3/scandir.3.html

## NAME

scandir, scandirat, alphasort, versionsort - scan a directory for matching entries

scandir, scandirat, alphasort, versionsort - 扫描一个目录中的匹配条目

## SYNOPSIS

```
       #include <dirent.h>

       int scandir(const char *restrict dirp,
                   struct dirent ***restrict namelist,
                   int (*filter)(const struct dirent *),
                   int (*compar)(const struct dirent **,
                                 const struct dirent **));

       int alphasort(const struct dirent **a, const struct dirent **b);
       int versionsort(const struct dirent **a, const struct dirent **b);

       #include <fcntl.h>          /* Definition of AT_* constants */
       #include <dirent.h>

       int scandirat(int dirfd, const char *restrict dirp,
                   struct dirent ***restrict namelist,
                   int (*filter)(const struct dirent *),
                   int (*compar)(const struct dirent **,
                                 const struct dirent **));

   Feature Test Macro Requirements for glibc (see
   feature_test_macros(7)):

       scandir(), alphasort():
           /* Since glibc 2.10: */ _POSIX_C_SOURCE >= 200809L
               || /* Glibc <= 2.19: */ _BSD_SOURCE || _SVID_SOURCE

       versionsort():
           _GNU_SOURCE

       scandirat():
           _GNU_SOURCE
```

## DESCRIPTION

The `scandir()` function scans the directory `dirp`, calling `filter()` on each directory entry.  Entries for which `filter()` returns nonzero are stored in strings allocated via `malloc(3)`, sorted using `qsort(3)` with the comparison function `compar()`, and collected in array `namelist` which is allocated via `malloc(3)`.  If `filter` is NULL, all entries are selected.

`scandir()`函数扫描目录`dirp`，对每个目录条目调用`filter()`。 `filter()`返回非零的条目被存储在通过`malloc(3)`分配的字符串中，使用`qsort(3)`和比较函数`compar()`进行排序，并收集在通过`malloc(3)`分配的数组`namelist`中。 如果`filter`为NULL，所有条目都被选中。

The `alphasort()` and `versionsort()` functions can be used as the comparison function `compar()`.  The former sorts directory entries using `strcoll(3)`, the latter using `strverscmp(3)` on the strings `(*a)->d_name` and `(*b)->d_name`.

`alphasort()`和`versionsort()`函数可以作为比较函数`compar()`使用。 前者使用`strcoll(3)`对目录条目进行排序，后者使用`strverscmp(3)`对字符串`（*a）->d_name`和`（*b）->d_name`进行排序。

### scandirat()

The `scandirat()` function operates in exactly the same way as `scandir()`, except for the differences described here.

`scandirat()`函数的操作方式与`scandir()`完全相同，除了这里描述的区别。

If the pathname given in `dirp` is relative, then it is interpreted relative to the directory referred to by the file descriptor `dirfd` (rather than relative to the current working directory of the calling process, as is done by `scandir()` for a relative pathname).

如果`dirp`中给出的路径名是相对的，那么它被解释为相对于文件描述符`dirfd`所指的目录（而不是相对于调用进程的当前工作目录，正如`scandir()`对相对路径名所做的）。

If `dirp` is relative and `dirfd` is the special value `AT_FDCWD`, then `dirp` is interpreted relative to the current working directory of the calling process (like `scandir()`).

如果`dirp`是相对的，并且`dirfd`是特殊值`AT_FDCWD`，那么`dirp`被解释为相对于调用进程的当前工作目录（像`scandir()`）。

If `dirp` is absolute, then `dirfd` is ignored.

如果`dirp`是绝对的，那么`dirfd`就被忽略了。

See `openat(2)` for an explanation of the need for `scandirat()`.

关于`scandirat()`的必要性，请看`openat(2)`的解释。


## RETURN VALUE

The scandir() function returns the number of directory entries selected.  On error, -1 is returned, with errno set to indicate the error.

scandir()函数返回所选择的目录条目的数量。 出错时，返回-1，并设置errno以表示错误。

The alphasort() and versionsort() functions return an integer less than, equal to, or greater than zero if the first argument is considered to be respectively less than, equal to, or greater than the second.

alphasort()和versionort()函数返回一个小于、等于或大于0的整数，如果第一个参数被认为分别小于、等于或大于第二个参数。

## ERRORS

### EBADF

(`scandirat()`) dirp is relative but dirfd is neither `AT_FDCWD` nor a valid file descriptor.

(`scandirat()`) dirp是相对的，但dirfd既不是`AT_FDCWD`也不是有效的文件描述符。

### ENOENT

The path in dirp does not exist.

dirp中的路径不存在。

### ENOMEM

Insufficient memory to complete the operation.

没有足够的内存来完成操作。

### ENOTDIR

The path in dirp is not a directory.

dirp中的路径不是一个目录。

### ENOTDIR

(`scandirat()`) dirp is a relative pathname and dirfd is a file descriptor referring to a file other than a directory.

(`scandirat()`) dirp是一个相对路径名，dirfd是一个文件描述符，指的是一个目录以外的文件。

## VERSIONS

`versionsort()` was added to glibc in version 2.1.

`versionsort()`在2.1版本中被添加到glibc。

`scandirat()` was added to glibc in version 2.15.

`scandirat()`在2.15版中被加入到glibc中。

## ATTRIBUTES

For an explanation of the terms used in this section, see attributes(7).

关于本节中使用的术语的解释，参见attributes(7)。

       ┌───────────────────────────────┬───────────────┬────────────────┐
       │Interface                      │ Attribute     │ Value          │
       ├───────────────────────────────┼───────────────┼────────────────┤
       │scandir(), scandirat()         │ Thread safety │ MT-Safe        │
       ├───────────────────────────────┼───────────────┼────────────────┤
       │alphasort(), versionsort()     │ Thread safety │ MT-Safe locale │
       └───────────────────────────────┴───────────────┴────────────────┘


## CONFORMING TO

alphasort(), scandir(): 4.3BSD, POSIX.1-2008.

versionsort() and scandirat() are GNU extensions.

## NOTES

Since glibc 2.1, alphasort() calls strcoll(3); earlier it used strcmp(3).

从glibc 2.1开始，alphasort()调用strcoll(3)；早期使用strcmp(3)。

Before glibc 2.10, the two arguments of `alphasort()` and `versionsort()` were typed as `const void *`.  When `alphasort()` was standardized in POSIX.1-2008, the argument type was specified as the type-safe `const struct dirent **`, and glibc 2.10 changed the definition of `alphasort()` (and the nonstandard `versionsort()`) to match the standard.

在glibc 2.10之前，`alphasort()`和`versionsort()`的两个参数的类型为`const void *`。 当`alphasort()`在POSIX.1-2008中被标准化时，参数类型被指定为类型安全的`const struct dirent **`，glibc 2.10改变了`alphasort()`（和非标准的`versionsort()`）的定义以符合标准。

## EXAMPLES

The program below prints a list of the files in the current directory in reverse order.

下面的程序按相反的顺序打印出当前目录下的文件列表。

Program source

```c
       #define _DEFAULT_SOURCE
       #include <dirent.h>
       #include <stdio.h>
       #include <stdlib.h>

       int
       main(void)
       {
           struct dirent **namelist;
           int n;

           n = scandir(".", &namelist, NULL, alphasort);
           if (n == -1) {
               perror("scandir");
               exit(EXIT_FAILURE);
           }

           while (n--) {
               printf("%s\n", namelist[n]->d_name);
               free(namelist[n]);
           }
           free(namelist);

           exit(EXIT_SUCCESS);
       }
```