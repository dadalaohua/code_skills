# lseek

https://www.man7.org/linux/man-pages/man2/lseek.2.html

## NAME

```
lseek - reposition read/write file offset
```

## SYNOPSIS

```c
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

## DESCRIPTION

lseek() repositions the file offset of the open file description associated with the file descriptor fd to the argument offset according to the directive whence as follows:

lseek() 根据指令将与文件描述符 fd 关联的打开文件描述的文件偏移重新定位到参数偏移量，如下所示：

### SEEK_SET
​              The file offset is set to offset bytes.

​			   文件偏移量设置为偏移字节。

### SEEK_CUR
​              The file offset is set to its current location plus offset bytes.

​              文件偏移量设置为其当前位置加上偏移量字节。

### SEEK_END
​              The file offset is set to the size of the file plus offset bytes.

​               文件偏移量设置为文件大小加上偏移量字节。

lseek() allows the file offset to be set beyond the end of the file (but this does not change the size of the file).  If data is later written at this point, subsequent reads of the data in the gap (a "hole") return null bytes ('\0') until data is actually written into the gap.

lseek() 允许将文件偏移量设置为超出文件末尾（但这不会改变文件的大小）。 如果稍后在此时写入数据，则后续读取间隙（“洞”）中的数据将返回空字节（'\0'），直到数据实际写入间隙。

Seeking file data and holes

寻求文件数据和漏洞

Since version 3.1, Linux supports the following additional values for whence:

从 3.1 版开始，Linux 支持以下附加值：

### SEEK_DATA
> Adjust the file offset to the next location in the file greater than or equal to offset containing data.  If offset points to data, then the file offset is set to offset.
>
> 将文件偏移量调整到文件中大于或等于包含数据的偏移量的下一个位置。 如果偏移量指向数据，那么文件偏移量被设置为偏移量。

### SEEK_HOLE
>  Adjust the file offset to the next hole in the file greater than or equal to offset.  If offset points into the middle of a hole, then the file offset is set to offset.  If there is no hole past offset, then the file offset is adjusted to the end of the file (i.e., there is an implicit hole at the end of any file).
>
> 将文件偏移量调整到大于或等于偏移量的文件中的下一个孔。 如果偏移指向孔的中间，则文件偏移设置为偏移。 如果没有超过偏移量的孔，则将文件偏移量调整到文件的末尾（即，在任何文件的末尾都有一个隐含的孔）。

In both of the above cases, lseek() fails if offset points past the end of the file.

在上述两种情况下，如果偏移点超过文件末尾，则 lseek() 将失败。

These operations allow applications to map holes in a sparsely allocated file.  This can be useful for applications such as file backup tools, which can save space when creating backups and preserve holes, if they have a mechanism for discovering holes.

这些操作允许应用程序在稀疏分配的文件中映射孔。这对于文件备份工具等应用程序很有用，如果它们具有发现漏洞的机制，则可以在创建备份和保留漏洞时节省空间。

For the purposes of these operations, a hole is a sequence of zeros that (normally) has not been allocated in the underlying file storage.  However, a filesystem is not obliged to report holes, so these operations are not a guaranteed mechanism for mapping the storage space actually allocated to a file. (Furthermore, a sequence of zeros that actually has been written to the underlying storage may not be reported as a hole.)  In the simplest implementation, a filesystem can support the operations by making SEEK_HOLE always return the offset of the end of the file, and making SEEK_DATA always return offset (i.e., even if the location referred to by offset is a hole, it can be considered to consist of data that is a sequence of zeros).

出于这些操作的目的，空洞是（通常）尚未在底层文件存储中分配的零序列。但是，文件系统没有义务报告漏洞，因此这些操作不是映射实际分配给文件的存储空间的保证机制。 （此外，实际上已写入底层存储的一系列零可能不会被报告为漏洞。）在最简单的实现中，文件系统可以通过使 SEEK_HOLE 始终返回文件末尾的偏移量来支持这些操作，并使 SEEK_DATA 始终返回偏移量（即，即使偏移量所指的位置是一个孔，也可以认为它由零序列的数据组成）。

The _GNU_SOURCE feature test macro must be defined in order to obtain the definitions of SEEK_DATA and SEEK_HOLE from <unistd.h>.

必须定义 _GNU_SOURCE 功能测试宏才能从 <unistd.h> 中获取 SEEK_DATA 和 SEEK_HOLE 的定义。

The SEEK_HOLE and SEEK_DATA operations are supported for the following filesystems:

以下文件系统支持 SEEK_HOLE 和 SEEK_DATA 操作：

* Btrfs (since Linux 3.1)

*  OCFS (since Linux 3.2)
*  ext4 (since Linux 3.8)
*  tmpfs(5) (since Linux 3.8)
*  NFS (since Linux 3.18)
*  FUSE (since Linux 4.5)
*  GFS2 (since Linux 4.15)    

## RETURN VALUE

Upon successful completion, lseek() returns the resulting offset location as measured in bytes from the beginning of the file.  On error, the value (off_t) -1 is returned and errno is set to indicate the error.    

成功完成后，lseek() 返回从文件开头开始以字节为单位测量的结果偏移位置。 出错时，返回值 (off_t) -1 并设置 errno 以指示错误。

## ERRORS

### EBADF

fd is not an open file descriptor.

fd 不是打开的文件描述符。

### EINVAL

whence is not valid.  Or: the resulting file offset would be negative, or beyond the end of a seekable device.

其中无效。 或者：生成的文件偏移量将为负数，或超出可搜索设备的末尾。

### ENXIO

whence is SEEK_DATA or SEEK_HOLE, and offset is beyond the end of the file, or whence is SEEK_DATA and offset is within a hole at the end of the file.

wherece 是 SEEK_DATA 或 SEEK_HOLE，并且 offset 超出文件末尾，或者 wherece 是 SEEK_DATA 并且 offset 在文件末尾的孔内。

### EOVERFLOW
The resulting file offset cannot be represented in an off_t.

生成的文件偏移量不能用 off_t 表示。

### ESPIPE

fd is associated with a pipe, socket, or FIFO.

fd 与管道、套接字或 FIFO 相关联。



## CONFORMING TO

POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.

SEEK_DATA and SEEK_HOLE are nonstandard extensions also present in Solaris, FreeBSD, and DragonFly BSD; they are proposed for inclusion in the next POSIX revision (Issue 8).

SEEK_DATA 和 SEEK_HOLE 是非标准扩展，也出现在 Solaris、FreeBSD 和 DragonFly BSD 中； 建议将它们包含在下一个 POSIX 修订版（第 8 期）中。

## NOTES

See open(2) for a discussion of the relationship between file descriptors, open file descriptions, and files.

有关文件描述符、打开文件描述和文件之间关系的讨论，请参见 open(2)。

If the O_APPEND file status flag is set on the open file description, then a write(2) always moves the file offset to the end of the file, regardless of the use of lseek().

如果在打开的文件描述上设置了 O_APPEND 文件状态标志，那么无论使用 lseek()，write(2) 总是将文件偏移量移动到文件末尾。

The off_t data type is a signed integer data type specified by POSIX.1.

off_t 数据类型是 POSIX.1 指定的有符号整数数据类型。

Some devices are incapable of seeking and POSIX does not specify which devices must support lseek().

某些设备无法搜索，POSIX 没有指定哪些设备必须支持 lseek()。

On Linux, using lseek() on a terminal device fails with the error ESPIPE.

在 Linux 上，在终端设备上使用 lseek() 失败并出现错误 ESPIPE。