# write

https://www.man7.org/linux/man-pages/man2/write.2.html

## NAME

```
write - write to a file descriptor
```

## SYNOPSIS

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

## DESCRIPTION

write() writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd.

write() 将缓冲区中从 buf 开始的最多 count 个字节写入文件描述符 fd 所引用的文件。

The number of bytes written may be less than count if, for example, there is insufficient space on the underlying physical medium, or the RLIMIT_FSIZE resource limit is encountered (see setrlimit(2)), or the call was interrupted by a signal handler after having written less than count bytes.  (See also pipe(7).)

写入的字节数可能少于 count，例如，底层物理介质上的空间不足，或者遇到 RLIMIT_FSIZE 资源限制（参见 setrlimit(2)），或者调用被信号处理程序中断后写入少于 count 个字节。 （另请参见管道 (7)。）

For a seekable file (i.e., one to which lseek(2) may be applied, for example, a regular file) writing takes place at the file offset, and the file offset is incremented by the number of bytes actually written.  If the file was open(2)ed with O_APPEND, the file offset is first set to the end of the file before writing. The adjustment of the file offset and the write operation are performed as an atomic step.

对于可查找文件（即可以应用 lseek(2) 的文件，例如常规文件），写入发生在文件偏移量处，并且文件偏移量增加实际写入的字节数。如果使用 O_APPEND 打开（2）文件，则文件偏移量在写入之前首先设置为文件末尾。文件偏移量的调整和写入操作作为原子步骤执行。

POSIX requires that a read(2) that can be proved to occur after a write() has returned will return the new data.  Note that not all filesystems are POSIX conforming.

POSIX 要求可以证明在 write() 返回后发生的 read(2) 将返回新数据。请注意，并非所有文件系统都符合 POSIX。

According to POSIX.1, if count is greater than SSIZE_MAX, the result is implementation-defined; see NOTES for the upper limit on Linux.   

根据 POSIX.1，如果 count 大于 SSIZE_MAX，则结果是实现定义的；有关 Linux 的上限，请参见注释。

## RETURN VALUE

On success, the number of bytes written is returned.  On error,  -1 is returned, and errno is set to indicate the error.

成功时，返回写入的字节数。出错时返回 -1，并设置 errno 以指示错误。

Note that a successful write() may transfer fewer than count  bytes.  Such partial writes can occur for various reasons; for example, because there was insufficient space on the disk device to write all of the requested bytes, or because a blocked write() to a socket, pipe, or similar was interrupted by a signal handler after it had transferred some, but before it had transferred all of the requested bytes.  In the event of a partial write, the caller can make another write() call to transfer the remaining bytes.  The subsequent call will either transfer further bytes or may result in an error (e.g., if the disk is now full).

请注意，成功的 write() 可能传输少于 count 个字节。这种部分写入可能由于各种原因而发生；例如，因为磁盘设备上没有足够的空间来写入所有请求的字节，或者因为阻塞的 write() 到套接字、管道或类似的东西在传输一些字节之后被信号处理程序中断，但在它之前已传输所有请求的字节。在部分写入的情况下，调用者可以进行另一个 write() 调用以传输剩余的字节。随后的调用将传输更多字节或可能导致错误（例如，如果磁盘现在已满）。

If count is zero and fd refers to a regular file, then write() may return a failure status if one of the errors below is detected.  If no errors are detected, or error detection is not  performed, 0 is returned without causing any other effect.  If count is zero and fd refers to a file other than a regular file, the results are not specified.  

如果 count 为零并且 fd 引用常规文件，则如果检测到以下错误之一，则 write() 可能会返回失败状态。如果没有检测到错误，或者没有执行错误检测，则返回 0 而不会造成任何其他影响。如果 count 为零并且 fd 引用的文件不是常规文件，则不指定结果。

## ERRORS

### EAGAIN

The file descriptor fd refers to a file other than a socket and has been marked nonblocking (O_NONBLOCK), and the write would block.  See open(2) for further details on the O_NONBLOCK flag.

文件描述符 fd 指的是不是套接字的文件，并且已被标记为非阻塞（O_NONBLOCK），写入将阻塞。 有关 O_NONBLOCK 标志的更多详细信息，请参见 open(2)。

### EAGAIN or EWOULDBLOCK
The file descriptor fd refers to a socket and has been marked nonblocking (O_NONBLOCK), and the write would block.  POSIX.1-2001 allows either error to be returned for this case, and does not require these constants to have the same value, so a portable application should check for both possibilities.

文件描述符 fd 引用一个套接字并且已被标记为非阻塞 (O_NONBLOCK)，写入将阻塞。 POSIX.1-2001 允许在这种情况下返回任一错误，并且不要求这些常量具有相同的值，因此可移植应用程序应检查这两种可能性。

### EBADF

fd is not a valid file descriptor or is not open for writing.

fd 不是有效的文件描述符或未打开写入。

### EDESTADDRREQ
fd refers to a datagram socket for which a peer address has not been set using connect(2).

fd 指的是尚未使用 connect(2) 为其设置对等地址的数据报套接字。

### EDQUOT

The user's quota of disk blocks on the filesystem containing the file referred to by fd has been exhausted.

包含 fd 引用的文件的文件系统上用户的磁盘块配额已用完。

### EFAULT

buf is outside your accessible address space.

buf 在你可访问的地址空间之外。

### EFBIG

An attempt was made to write a file that exceeds the implementation-defined maximum file size or the process's file size limit, or to write at a position past the maximum allowed offset.

试图写入超过实现定义的最大文件大小或进程的文件大小限制的文件，或写入超过最大允许偏移量的位置。

### EINTR

The call was interrupted by a signal before any data was written; see signal(7).

在写入任何数据之前调用被信号中断； 见信号（7）。

### EINVAL

fd is attached to an object which is unsuitable for writing; or the file was opened with the O_DIRECT flag, and either the address specified in buf, the value specified in count, or the file offset is not suitably aligned.

fd 连接到一个不适合写入的对象上； 或者文件是使用 O_DIRECT 标志打开的，并且 buf 中指定的地址、count 中指定的值或文件偏移量未适当对齐。

### EIO 

A low-level I/O error occurred while modifying the inode. This error may relate to the write-back of data written by an earlier write(), which may have been issued to a different file descriptor on the same file.  Since Linux 4.13, errors from write-back come with a promise that they may be reported by subsequent.  write() requests, and will be reported by a subsequent fsync(2) (whether or not they were also reported by write()).  An alternate cause of EIO on networked filesystems is when an advisory lock had been taken out on the file descriptor and this lock has been lost.  See the Lost locks section of fcntl(2) for further details.

修改 inode 时发生低级 I/O 错误。 此错误可能与较早的 write() 写入的数据的回写有关，该数据可能已发送到同一文件上的不同文件描述符。 从 Linux 4.13 开始，回写错误伴随着后续可能会报告它们的承诺。 write() 请求，并将由随后的 fsync(2) 报告（无论它们是否也由 write() 报告）。 网络文件系统上 EIO 的另一个原因是文件描述符上的咨询锁已被取出并且该锁已丢失。 有关详细信息，请参阅 fcntl(2) 的丢失锁部分。

### ENOSPC

The device containing the file referred to by fd has no room for the data.

包含 fd 引用的文件的设备没有数据空间。

### EPERM

The operation was prevented by a file seal; see fcntl(2).

该操作被一个文件密封所阻止；见fcntl(2)。

### EPIPE

fd is connected to a pipe or socket whose reading end is closed.  When this happens the writing process will also receive a SIGPIPE signal.  (Thus, the write return value is seen only if the program catches, blocks or ignores this signal.)

fd 连接到读取端关闭的管道或套接字。 当这种情况发生时，写入过程也会收到一个 SIGPIPE 信号。 （因此，只有当程序捕获、阻塞或忽略此信号时，才会看到写入返回值。）



Other errors may occur, depending on the object connected to fd. 

其他错误可能会发生，这取决于与fd连接的对象。

## CONFORMING TO

SVr4, 4.3BSD, POSIX.1-2001.

Under SVr4 a write may be interrupted and return EINTR at any  point, not just before any data is written.  

在 SVr4 下，写入可能会被中断并在任何时候返回 EINTR，而不仅仅是在写入任何数据之前。

## NOTES

The types size_t and ssize_t are, respectively, unsigned and signed integer data types specified by POSIX.1.

类型 size_t 和 ssize_t 分别是 POSIX.1 指定的无符号和有符号整数数据类型。

A successful return from write() does not make any guarantee that data has been committed to disk.  On some filesystems, including NFS, it does not even guarantee that space has successfully been reserved for the data.  In this case, some errors might be delayed until a future write(), fsync(2), or even close(2).  The only way to be sure is to call fsync(2) after you are done writing all your data.

write() 的成功返回并不能保证数据已提交到磁盘。在包括 NFS 在内的某些文件系统上，它甚至不能保证已成功为数据保留空间。在这种情况下，一些错误可能会延迟到未来的 write()、fsync(2) 甚至 close(2)。唯一可以确定的方法是在完成所有数据的写入后调用 fsync(2)。

If a write() is interrupted by a signal handler before any bytes are written, then the call fails with the error EINTR; if it is interrupted after at least one byte has been written, the call succeeds, and returns the number of bytes written.

如果 write() 在写入任何字节之前被信号处理程序中断，则调用失败并返回错误 EINTR；如果在至少写入一个字节后中断，则调用成功，并返回写入的字节数。

On Linux, write() (and similar system calls) will transfer at most 0x7ffff000 (2,147,479,552) bytes, returning the number of bytes actually transferred.  (This is true on both 32-bit and 64-bit systems.)

在 Linux 上，write()（和类似的系统调用）将最多传输 0x7ffff000 (2,147,479,552) 字节，返回实际传输的字节数。 （在 32 位和 64 位系统上都是如此。）

An error return value while performing write() using direct I/O does not mean the entire write has failed.  Partial data may be written and the data at the file offset on which the write() was attempted should be considered inconsistent.

使用直接 I/O 执行 write() 时返回错误值并不意味着整个写入失败。可能会写入部分数据，并且尝试 write() 的文件偏移量处的数据应被视为不一致。

## BUGS

According to POSIX.1-2008/SUSv4 Section XSI 2.9.7 ("Thread Interactions with Regular File Operations"):

根据 POSIX.1-2008/SUSv4 Section XSI 2.9.7（“线程与常规文件操作的交互”）：

> All of the following functions shall be atomic with respect to each other in the effects specified in POSIX.1-2008 when they operate on regular files or symbolic links: ...
>
> 以下所有函数在对常规文件或符号链接进行操作时，在 POSIX.1-2008 中指定的效果中相互之间应是原子的： ...

Among the APIs subsequently listed are write() and writev(2). And among the effects that should be atomic across threads (and processes) are updates of the file offset.  However, on Linux before version 3.14, this was not the case: if two processes that share an open file description (see open(2)) perform a write() (or writev(2)) at the same time, then the I/O operations were not atomic with respect to updating the file offset, with the result that the blocks of data output by the two processes might (incorrectly) overlap.  This problem was fixed in Linux 3.14.

随后列出的 API 包括 write() 和 writev(2)。 跨线程（和进程）应该是原子的影响之一是文件偏移量的更新。 但是，在 3.14 之前的 Linux 上，情况并非如此：如果共享打开文件描述（参见 open(2)）的两个进程同时执行 write()（或 writev(2)），则 I /O 操作在更新文件偏移方面不是原子的，因此两个进程输出的数据块可能（不正确地）重叠。 此问题已在 Linux 3.14 中修复。