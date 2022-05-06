# close

https://www.man7.org/linux/man-pages/man2/close.2.html

## NAME

```
close - close a file descriptor
```

## SYNOPSIS

```c
#include <unistd.h>

int close(int fd);
```

## DESCRIPTION

close() closes a file descriptor, so that it no longer refers to any file and may be reused.  Any record locks (see fcntl(2)) held on the file it was associated with, and owned by the process, are removed (regardless of the file descriptor that was used to obtain the lock).

close() 关闭文件描述符，使其不再引用任何文件并且可以重用。 任何记录锁（请参阅 fcntl(2)）保存在与它关联的文件上，并由进程拥有，都将被删除（无论用于获取锁的文件描述符是什么）。

If fd is the last file descriptor referring to the underlying open file description (see open(2)), the resources associated with the open file description are freed; if the file descriptor was the last reference to a file which has been removed using unlink(2), the file is deleted.

如果 fd 是引用底层打开文件描述的最后一个文件描述符（参见 open(2)），则释放与打开文件描述相关的资源； 如果文件描述符是对已使用 unlink(2) 删除的文件的最后引用，则删除该文件。

## RETURN VALUE

close() returns zero on success.  On error, -1 is returned, and errno is set to indicate the error.

 close() 成功时返回零。 出错时返回 -1，并设置 errno 以指示错误。

## ERRORS

### EBADF

fd isn't a valid open file descriptor.

fd 不是有效的打开文件描述符。

### EINTR

The close() call was interrupted by a signal; see signal(7).

close() 调用被信号中断； 见信号（7）。

### EIO

An I/O error occurred.

发生 I/O 错误。

### ENOSPC, EDQUOT
On NFS, these errors are not normally reported against the first write which exceeds the available storage space, but instead against a subsequent write(2), fsync(2), or close().

在 NFS 上，这些错误通常不会针对超出可用存储空间的第一次写入报告，而是针对后续的 write(2)、fsync(2) 或 close()。



See NOTES for a discussion of why close() should not be retried after an error.

关于为什么 close() 不应在错误后重试的讨论，请参见注释。

## CONFORMING TO

POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.    

## NOTES

A successful close does not guarantee that the data has been successfully saved to disk, as the kernel uses the buffer cache to defer writes.  Typically, filesystems do not flush buffers when a file is closed.  If you need to be sure that the data is physically stored on the underlying disk, use fsync(2).  (It will depend on the disk hardware at this point.)

成功关闭并不能保证数据已成功保存到磁盘，因为内核使用缓冲区缓存来延迟写入。 通常，文件系统在文件关闭时不会刷新缓冲区。 如果您需要确保数据物理存储在底层磁盘上，请使用 fsync(2)。 （此时这将取决于磁盘硬件。）

The close-on-exec file descriptor flag can be used to ensure that a file descriptor is automatically closed upon a successful execve(2); see fcntl(2) for details.

close-on-exec 文件描述符标志可用于确保在成功执行 execve(2) 时自动关闭文件描述符； 有关详细信息，请参见 fcntl(2)。

### Multithreaded processes and close() 多线程进程和 close()

It is probably unwise to close file descriptors while they may be in use by system calls in other threads in the same process. Since a file descriptor may be reused, there are some obscure race conditions that may cause unintended side effects.

当同一进程中的其他线程中的系统调用可能正在使用文件描述符时，关闭文件描述符可能是不明智的。由于可以重用文件描述符，因此存在一些可能导致意外副作用的模糊竞争条件。

Furthermore, consider the following scenario where two threads are performing operations on the same file descriptor:

此外，考虑以下两个线程对同一个文件描述符执行操作的场景：

1. One thread is blocked in an I/O system call on the file descriptor.  For example, it is trying to write(2) to a pipe that is already full, or trying to read(2) from a stream socket which currently has no available data.

      一个线程在文件描述符的 I/O 系统调用中被阻塞。例如，它正在尝试向已满的管道write(2) ，或者尝试从当前没有可用数据的流套接字中read(2) 

2. Another thread closes the file descriptor.

      另一个线程关闭文件描述符。

The behavior in this situation varies across systems.  On some systems, when the file descriptor is closed, the blocking system call returns immediately with an error.

这种情况下的行为因系统而异。在某些系统上，当文件描述符关闭时，阻塞系统调用会立即返回错误。

On Linux (and possibly some other systems), the behavior is different: the blocking I/O system call holds a reference to the underlying open file description, and this reference keeps the description open until the I/O system call completes.  (See open(2) for a discussion of open file descriptions.)  Thus, the blocking system call in the first thread may successfully complete after the close() in the second thread.

在 Linux（可能还有其他一些系统）上，行为是不同的：阻塞 I/O 系统调用持有对底层打开文件描述的引用，并且该引用保持描述打开直到 I/O 系统调用完成。 （有关打开文件描述的讨论，请参见 open(2)。）因此，第一个线程中的阻塞系统调用可能在第二个线程中的 close() 之后成功完成。

### Dealing with error returns from close() 处理来自 close() 的错误返回

A careful programmer will check the return value of close(), since it is quite possible that errors on a previous write(2) operation are reported only on the final close() that releases the open file description.  Failing to check the return value when closing a file may lead to silent loss of data.  This can especially be observed with NFS and with disk quota.

细心的程序员会检查 close() 的返回值，因为很有可能之前 write(2) 操作中的错误仅在释放打开文件描述的最终 close() 上报告。关闭文件时未能检查返回值可能会导致数据无声丢失。这在 NFS 和磁盘配额中尤其明显。

Note, however, that a failure return should be used only for diagnostic purposes (i.e., a warning to the application that there may still be I/O pending or there may have been failed I/O) or remedial purposes (e.g., writing the file once more or creating a backup).

但是请注意，故障返回应仅用于诊断目的（即，警告应用程序可能仍有 I/O 未决或可能存在 I/O 失败）或补救目的（例如，编写再次归档或创建备份）。

Retrying the close() after a failure return is the wrong thing to do, since this may cause a reused file descriptor from another thread to be closed.  This can occur because the Linux kernel always releases the file descriptor early in the close operation, freeing it for reuse; the steps that may return an error, such as flushing data to the filesystem or device, occur only later in the close operation.

在失败返回后重试 close() 是错误的做法，因为这可能会导致来自另一个线程的重用文件描述符被关闭。这可能是因为 Linux 内核总是在关闭操作的早期释放文件描述符，释放它以供重用；可能返回错误的步骤，例如将数据刷新到文件系统或设备，仅在关闭操作的后期发生。

Many other implementations similarly always close the file descriptor (except in the case of EBADF, meaning that the file descriptor was invalid) even if they subsequently report an error on return from close().  POSIX.1 is currently silent on this point, but there are plans to mandate this behavior in the next major release of the standard.

许多其他实现同样总是关闭文件描述符（EBADF 的情况除外，这意味着文件描述符无效），即使它们随后在从 close() 返回时报告错误。 POSIX.1 目前对此保持沉默，但计划在该标准的下一个主要版本中强制执行此行为。

A careful programmer who wants to know about I/O errors may precede close() with a call to fsync(2).

想要了解 I/O 错误的细心程序员可能会在 close() 之前调用 fsync(2)。

The EINTR error is a somewhat special case.  Regarding the EINTR error, POSIX.1-2008 says:

EINTR 错误是一种特殊情况。关于 EINTR 错误，POSIX.1-2008 说：

> If close() is interrupted by a signal that is to be caught, it shall return -1 with errno set to EINTR and the state of fildes is unspecified.
>
> 如果 close() 被要捕获的信号中断，它应返回 -1，并将 errno 设置为 EINTR，并且未指定 fildes 的状态。

This permits the behavior that occurs on Linux and many other implementations, where, as with other errors that may be reported by close(), the file descriptor is guaranteed to be closed. However, it also permits another possibility: that the implementation returns an EINTR error and keeps the file descriptor open.  (According to its documentation, HP-UX's close() does this.)  The caller must then once more use close() to close the file descriptor, to avoid file descriptor leaks. This divergence in implementation behaviors provides a difficult hurdle for portable applications, since on many implementations, close() must not be called again after an EINTR error, and on at least one, close() must be called again.  There are plans to address this conundrum for the next major release of the POSIX.1 standard.

这允许在 Linux 和许多其他实现上发生的行为，其中与 close() 可能报告的其他错误一样，文件描述符保证被关闭。但是，它也允许另一种可能性：实现返回 EINTR 错误并保持文件描述符打开。 （根据其文档，HP-UX 的 close() 执行此操作。）然后调用者必须再次使用 close() 关闭文件描述符，以避免文件描述符泄漏。这种实现行为的差异为可移植应用程序提供了一个困难的障碍，因为在许多实现中，在 EINTR 错误之后不得再次调用 close()，并且至少在一个错误中，必须再次调用 close()。有计划在 POSIX.1 标准的下一个主要版本中解决这个难题。