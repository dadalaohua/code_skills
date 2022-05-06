# read

https://www.man7.org/linux/man-pages/man2/read.2.html

## NAME

```
read - read from a file descriptor
```

## SYNOPSIS

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

## DESCRIPTION

read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.

read() 尝试将文件描述符 fd 中的 count 个字节读入缓冲区，从 buf 开始。

On files that support seeking, the read operation commences at the file offset, and the file offset is incremented by the number of bytes read.  If the file offset is at or past the end of file, no bytes are read, and read() returns zero.

在支持查找的文件上，读取操作从文件偏移量开始，文件偏移量增加读取的字节数。 如果文件偏移位于或超过文件末尾，则不读取任何字节，并且 read() 返回零。

If count is zero, read() may detect the errors described below. In the absence of any errors, or if read() does not check for errors, a read() with a count of 0 returns zero and has no other effects.

如果 count 为零，read() 可能会检测到下面描述的错误。 在没有任何错误的情况下，或者如果 read() 不检查错误，则计数为 0 的 read() 返回零并且没有其他效果。

According to POSIX.1, if count is greater than SSIZE_MAX, the result is implementation-defined; see NOTES for the upper limit on Linux.

根据 POSIX.1，如果 count 大于 SSIZE_MAX，则结果是实现定义的； 有关 Linux 的上限，请参见注释。

## RETURN VALUE

On success, the number of bytes read is returned (zero indicates end of file), and the file position is advanced by this number. It is not an error if this number is smaller than the number of bytes requested; this may happen for example because fewer bytes are actually available right now (maybe because we were close to end-of-file, or because we are reading from a pipe, or from a terminal), or because read() was interrupted by a signal.  See also NOTES.

成功时，返回读取的字节数（零表示文件结束），文件位置提前该数字。 如果此数字小于请求的字节数，则不是错误； 这可能会发生，例如因为现在实际可用的字节数较少（可能是因为我们接近文件结尾，或者因为我们正在从管道或终端读取），或者因为 read() 被中断 信号。 另见注释。

On error, -1 is returned, and errno is set to indicate the error. In this case, it is left unspecified whether the file position (if any) changes.

成功时，返回读取的字节数（零表示文件结束），文件位置提前该数字。 如果此数字小于请求的字节数，则不是错误； 这可能会发生，例如因为现在实际可用的字节数较少（可能是因为我们接近文件结尾，或者因为我们正在从管道或终端读取），或者因为 read() 被中断 信号。 另见注释。

 

## ERRORS

### EAGAIN

The file descriptor fd refers to a file other than a socket and has been marked nonblocking (O_NONBLOCK), and the read would block.  See open(2) for further details on the O_NONBLOCK flag.

文件描述符 fd 指的是不是套接字的文件，并且已被标记为非阻塞（O_NONBLOCK），读取将阻塞。 有关 O_NONBLOCK 标志的更多详细信息，请参见 open(2)。

### EAGAIN or EWOULDBLOCK
The file descriptor fd refers to a socket and has been marked nonblocking (O_NONBLOCK), and the read would block. POSIX.1-2001 allows either error to be returned for this case, and does not require these constants to have the same value, so a portable application should check for both possibilities.

文件描述符 fd 引用了一个套接字并被标记为非阻塞（O_NONBLOCK），读取将阻塞。 POSIX.1-2001 允许在这种情况下返回任一错误，并且不要求这些常量具有相同的值，因此可移植应用程序应检查这两种可能性。

### EBADF

fd is not a valid file descriptor or is not open for reading.

fd 不是有效的文件描述符或未打开以供读取。

### EFAULT

buf is outside your accessible address space.

buf 在你可访问的地址空间之外。

### EINTR

The call was interrupted by a signal before any data was read; see signal(7).

在读取任何数据之前调用被信号中断； 见信号（7）。

### EINVAL

fd is attached to an object which is unsuitable for reading; or the file was opened with the O_DIRECT flag, and either the address specified in buf, the value specified in count, or the file offset is not suitably aligned.

fd连接到一个不适合读取的对象；或者文件是用O_DIRECT标志打开的，并且buf中指定的地址，count中指定的值，或者文件偏移量没有适当的对齐。

### EINVAL

fd was created via a call to timerfd_create(2) and the wrong size buffer was given to read(); see timerfd_create(2) for further information.

fd 是通过调用 timerfd_create(2) 创建的，并且给 read() 提供了错误大小的缓冲区； 有关详细信息，请参阅 timerfd_create(2)。

### EIO

I/O error.  This will happen for example when the process is in a background process group, tries to read from its controlling terminal, and either it is ignoring or blocking SIGTTIN or its process group is orphaned.  It may also occur when there is a low-level I/O error while reading from a disk or tape.  A further possible cause of EIO on networked filesystems is when an advisory lock had been taken out on the file descriptor and this lock has been lost.  See the Lost locks section of fcntl(2) for further details.

输入/输出错误。 例如，当进程在后台进程组中，尝试从其控制终端读取，并且它忽略或阻止 SIGTTIN 或其进程组是孤立的时，就会发生这种情况。 当从磁盘或磁带读取时出现低级 I/O 错误时，也可能发生这种情况。 网络文件系统上的 EIO 的另一个可能原因是文件描述符上的咨询锁已被取出并且该锁已丢失。 有关详细信息，请参阅 fcntl(2) 的丢失锁部分。

### EISDIR

fd refers to a directory.

fd 指的是一个目录。



Other errors may occur, depending on the object connected to fd. 

其他错误可能会发生，这取决于与fd连接的对象。

## CONFORMING TO

SVr4, 4.3BSD, POSIX.1-2001.    

## NOTES

The types size_t and ssize_t are, respectively, unsigned and signed integer data types specified by POSIX.1.

类型 size_t 和 ssize_t 分别是 POSIX.1 指定的无符号和有符号整数数据类型。

On Linux, read() (and similar system calls) will transfer at most 0x7ffff000 (2,147,479,552) bytes, returning the number of bytes actually transferred.  (This is true on both 32-bit and 64-bit systems.)

在 Linux 上，read()（和类似的系统调用）将最多传输 0x7ffff000 (2,147,479,552) 字节，返回实际传输的字节数。 （在 32 位和 64 位系统上都是如此。）

On NFS filesystems, reading small amounts of data will update the timestamp only the first time, subsequent calls may not do so. This is caused by client side attribute caching, because most if not all NFS clients leave st_atime (last file access time) updates to the server, and client side reads satisfied from the client's cache will not cause st_atime updates on the server as there are no server-side reads.  UNIX semantics can be obtained by disabling client-side attribute caching, but in most situations this will substantially increase server load and decrease performance.

在 NFS 文件系统上，读取少量数据只会在第一次更新时间戳，后续调用可能不会这样做。 这是由客户端属性缓存引起的，因为大多数（如果不是所有）NFS 客户端都会将 st_atime（上次文件访问时间）更新留给服务器，并且客户端从客户端缓存中满足的读取不会导致服务器上的 st_atime 更新，因为没有 服务器端读取。 可以通过禁用客户端属性缓存来获得 UNIX 语义，但在大多数情况下，这将大大增加服务器负载并降低性能。

## BUGS

According to POSIX.1-2008/SUSv4 Section XSI 2.9.7 ("Thread Interactions with Regular File Operations"):

根据 POSIX.1-2008/SUSv4 Section XSI 2.9.7（“线程与常规文件操作的交互”）：

> All of the following functions shall be atomic with respect to each other in the effects specified in POSIX.1-2008 when they operate on regular files or symbolic links: ...
>
> 以下所有函数在对常规文件或符号链接进行操作时，在 POSIX.1-2008 中指定的效果中相互之间应是原子的： ...

Among the APIs subsequently listed are read() and readv(2).  And among the effects that should be atomic across threads (and processes) are updates of the file offset.  However, on Linux before version 3.14, this was not the case: if two processes that share an open file description (see open(2)) perform a read() (or readv(2)) at the same time, then the I/O operations were not atomic with respect updating the file offset, with the result that the reads in the two processes might (incorrectly) overlap in the blocks of data that they obtained.  This problem was fixed in Linux 3.14.

随后列出的 API 包括 read() 和 readv(2)。 跨线程（和进程）应该是原子的影响之一是文件偏移量的更新。 但是，在 3.14 之前的 Linux 上，情况并非如此：如果共享打开文件描述（参见 open(2)）的两个进程同时执行 read()（或 readv(2)），则 I /O 操作在更新文件偏移方面不是原子操作，因此两个进程中的读取可能（错误地）在它们获得的数据块中重叠。 此问题已在 Linux 3.14 中修复。