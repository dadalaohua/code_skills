# readdir

https://www.man7.org/linux/man-pages/man3/readdir.3.html

## NAME

readdir - read a directory

readdir - 读取一个目录


## SYNOPSIS

```c
#include <dirent.h>

struct dirent *readdir(DIR *dirp);
```

## DESCRIPTION

The readdir() function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.  It returns NULL on reaching the end of the directory stream or if an error occurred.

readdir() 函数返回一个指向 `dirent` 结构的指针，该结构表示 `dirp` 指向的目录流中的下一个目录条目。 它在到达目录流的末尾或发生错误时返回 NULL。

In the glibc implementation, the dirent structure is defined as follows:

在glibc实现中，dirent结构定义如下：

```c
struct dirent {
    ino_t          d_ino;       /* Inode number */
    off_t          d_off;       /* Not an offset; see below */
    unsigned short d_reclen;    /* Length of this record */
    unsigned char  d_type;      /* Type of file; not supported
                                              by all filesystem types */
    char           d_name[256]; /* Null-terminated filename */
};
```

The only fields in the dirent structure that are mandated by POSIX.1 are d_name and d_ino.  The other fields are unstandardized, and not present on all systems; see NOTES below for some further details.

POSIX.1 规定的 `dirent` 结构中的唯一字段是 `d_name` 和 `d_ino`。 其他字段未标准化，并非在所有系统上都存在； 有关更多详细信息，请参见下面的注释。

The fields of the dirent structure are as follows:

`dirent`结构的字段如下：

### d_ino

This is the inode number of the file.

这是该文件的inode号。

### d_off

The value returned in d_off is the same as would be returned by calling telldir(3) at the current position in the directory stream.  Be aware that despite its type and name, the d_off field is seldom any kind of directory offset on modern filesystems.  Applications should treat this field as an opaque value, making no assumptions about its contents; see also telldir(3).

d_off中返回的值与在目录流的当前位置调用telldir(3)返回的值相同。 请注意，尽管它的类型和名称，d_off字段在现代文件系统中很少是任何类型的目录偏移。 应用程序应该把这个字段当作一个不透明的值，对它的内容不做任何假设；另见telldir(3)。

### d_reclen

This is the size (in bytes) of the returned record.  This may not match the size of the structure definition shown above; see NOTES.

这是返回记录的大小(字节数)。 这可能与上面显示的结构定义的大小不一致；见NOTES。

### d_type 

This field contains a value indicating the file type,making it possible to avoid the expense of calling lstat(2) if further actions depend on the type of the file.

这个字段包含一个表示文件类型的值，如果进一步的操作取决于文件的类型，就可以避免调用lstat(2)的费用。

When a suitable feature test macro is defined (`_DEFAULT_SOURCE` on glibc versions since 2.19, or `_BSD_SOURCE` on glibc versions 2.19 and earlier), glibc defines the following macro constants for the value returned in `d_type`:

当定义了一个合适的特征测试宏（在2.19以后的glibc版本中为`_DEFAULT_SOURCE`，或在2.19及以前的glibc版本中为`_BSD_SOURCE`），glibc为`d_type`中返回的值定义了以下宏常数。

`DT_BLK` This is a block device.这是一个块设备。

`DT_CHR` This is a character device.这是一个字符设备。

`DT_DIR` This is a directory.这是一个目录。

`DT_FIFO` This is a named pipe (FIFO).这是一个命名的管道（FIFO）。

`DT_LNK` This is a symbolic link.这是一个符号链接。

`DT_REG` This is a regular file.这是一个普通文件。

`DT_SOCK` This is a UNIX domain socket.这是一个UNIX域套接字。

`DT_UNKNOWN` The file type could not be determined.文件类型无法确定。

Currently, only some filesystems (among them: Btrfs, ext2, ext3, and ext4) have full support for returning the file type in d_type.  All applications must properly handle a return of DT_UNKNOWN.
目前，只有一些文件系统（其中包括：Btrfs、ext2、ext3和ext4）完全支持在d_type中返回文件类型。 所有应用程序必须正确处理DT_UNKNOWN的返回。

### d_name

This field contains the null terminated filename.  See NOTES.

这个字段包含空结尾的文件名。 见注释。



The data returned by readdir() may be overwritten by subsequent calls to readdir() for the same directory stream.

readdir()返回的数据可能被同一目录流的后续调用readdir()所覆盖。

## RETURN VALUE

On success, readdir() returns a pointer to a dirent structure.(This structure may be statically allocated; do not attempt to free(3) it.)

成功后，`readdir()` 返回一个指向`dirent 结构的指针。（这个结构可能是静态分配的；不要试图释放(3)它。）

If the end of the directory stream is reached, NULL is returned and errno is not changed.  If an error occurs, NULL is returned and errno is set to indicate the error.  To distinguish end of stream from an error, set errno to zero before calling readdir() and then check the value of errno if NULL is returned.

如果到达目录流的末端，返回NULL，`errno`不改变。 如果发生错误，则返回NULL，并设置`errno`以指示错误。 为了区分流的结束和错误，在调用`readdir()`之前将`errno`设置为零，如果返回NULL，则检查`errno`的值。

## ERRORS

### EBADF 

Invalid directory stream descriptor dirp.

无效的目录流描述符`dirp`。


## ATTRIBUTES

For an explanation of the terms used in this section, see attributes(7).

关于本节所用术语的解释，见属性（7）。

       ┌─────────────────────┬───────────────┬──────────────────────────┐
       │Interface            │ Attribute     │ Value                    │
       ├─────────────────────┼───────────────┼──────────────────────────┤
       │readdir()            │ Thread safety │ MT-Unsafe race:dirstream │
       └─────────────────────┴───────────────┴──────────────────────────┘

In the current POSIX.1 specification (POSIX.1-2008), readdir() is not required to be thread-safe.  However, in modern implementations (including the glibc implementation), concurrent calls to readdir() that specify different directory streams are thread-safe.  In cases where multiple threads must read from the same directory stream, using readdir() with external synchronization is still preferable to the use of the deprecated readdir_r(3) function.  It is expected that a future version of POSIX.1 will require that readdir() be thread-safe when concurrently employed on different directory streams.

在当前的POSIX.1规范（POSIX.1-2008）中，不要求`readdir()`是线程安全的。 然而，在现代实现中（包括glibc实现），对指定不同目录流的`readdir()`的并发调用是线程安全的。 在多个线程必须从同一目录流中读取数据的情况下，使用具有外部同步的`readdir()`仍然比使用已废弃的`readdir_r(3)`函数更可取。 预计未来的POSIX.1版本将要求`readdir()`在不同目录流上并发使用时是线程安全的。

## CONFORMING TO

POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.

## NOTES

A directory stream is opened using opendir(3).

一个目录流是用opendir(3)打开的。

The order in which filenames are read by successive calls to readdir() depends on the filesystem implementation; it is unlikely that the names will be sorted in any fashion.

通过连续调用readdir()读取文件名的顺序取决于文件系统的实现；文件名不可能以任何方式被排序。

Only the fields d_name and (as an XSI extension) d_ino are specified in POSIX.1.  Other than Linux, the d_type field is available mainly only on BSD systems.  The remaining fields are available on many, but not all systems.  Under glibc, programs can check for the availability of the fields not defined in POSIX.1 by testing whether the macros  `_DIRENT_HAVE_D_NAMLEN`, `_DIRENT_HAVE_D_RECLEN`, `_DIRENT_HAVE_D_OFF`, or `_DIRENT_HAVE_D_TYPE` are defined.

POSIX.1中只指定了d_name和（作为XSI的扩展）d_ino字段。 除了Linux之外，d_type字段主要只在BSD系统上可用。 其余的字段在许多系统上可用，但不是所有系统。 在glibc下，程序可以通过测试宏`_DIRENT_HAVE_D_NAMLEN`、`_DIRENT_HAVE_D_RECLEN`、`_DIRENT_HAVE_D_OFF`或`_DIRENT_HAVE_D_TYPE`是否被定义来检查POSIX.1中未定义字段的可用性。

### The d_name field
The dirent structure definition shown above is taken from the glibc headers, and shows the `d_name` field with a fixed size.

上面显示的dirent结构定义取自glibc头文件，显示了`d_name`字段的固定大小。

`Warning`: applications should avoid any dependence on the size of the `d_name` field.  POSIX defines it as `char d_name[]`, a character array of unspecified size, with at most `NAME_MAX` characters preceding the terminating null byte ('\0').

警告：应用程序应避免对`d_name`字段的大小产生任何依赖。 POSIX将其定义为`char d_name[]`，一个未指定大小的字符数组，在结束的空字节（'\0'）之前最多只有`NAME_MAX`字符。

POSIX.1 explicitly notes that this field should not be used as an lvalue.  The standard also notes that the use of sizeof(d_name) is incorrect; use strlen(d_name) instead.  (On some systems, this field is defined as char d_name[1]!)  By implication, the use sizeof(struct dirent) to capture the size of the record including the size of d_name is also incorrect.

POSIX.1明确指出，这个字段不应该作为lvalue使用。 该标准还指出，使用sizeof(d_name)是不正确的；使用strlen(d_name)代替。 (在某些系统中，这个字段被定义为char d_name[1]！)由此可见，使用sizeof(struct dirent)来获取包括d_name大小在内的记录的大小也是不正确的。

Note that while the call

请注意，虽然调用

​           fpathconf(fd, _PC_NAME_MAX)

returns the value 255 for most filesystems, on some filesystems (e.g., CIFS, Windows SMB servers), the null-terminated filename that is (correctly) returned in d_name can actually exceed this size.  In such cases, the d_reclen field will contain a value that exceeds the size of the glibc dirent structure shown above.

返回的值是255，但在某些文件系统中（例如CIFS、Windows SMB服务器），在d_name中（正确）返回的空尾文件名实际上可能超过这个大小。 在这种情况下，d_reclen字段将包含一个超过上述glibc dirent结构大小的值。

