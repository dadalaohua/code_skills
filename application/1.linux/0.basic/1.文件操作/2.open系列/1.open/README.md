# open

https://www.man7.org/linux/man-pages/man2/open.2.html

## NAME

```
open, openat, creat - open and possibly create a file
```

## SYNOPSIS

```c
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int creat(const char *pathname, mode_t mode);

int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);

/* Documented separately, in openat2(2): */
int openat2(int dirfd, const char *pathname, const struct open_how *how, size_t size);

Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

openat():
    Since glibc 2.10:
        _POSIX_C_SOURCE >= 200809L
    Before glibc 2.10:
        _ATFILE_SOURCE
```

## DESCRIPTION

The open() system call opens the file specified by pathname.  If the specified file does not exist, it may optionally (if O_CREAT is specified in *flags*) be created by open().

open() 系统调用打开由路径名指定的文件。 如果指定的文件不存在，则可以选择（如果在*flags*中指定 O_CREAT）由 open() 创建。

The return value of open() is a file descriptor, a small, nonnegative integer that is an index to an entry in the process's table of open file descriptors.  The file descriptor is used in subsequent system calls (read(2), write(2), lseek(2), fcntl(2), etc.) to refer to the open file.  The file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently open for the process.

open() 的返回值是一个文件描述符，一个小的非负整数，它是进程的打开文件描述符表中条目的索引。 文件描述符用于后续系统调用（read(2)、write(2)、lseek(2)、fcntl(2) 等）来引用打开的文件。 成功调用返回的文件描述符将是当前未为进程打开的编号最小的文件描述符。

By default, the new file descriptor is set to remain open across an execve(2) (i.e., the FD_CLOEXEC file descriptor flag described in fcntl(2) is initially disabled); the O_CLOEXEC flag, described below, can be used to change this default.  The file offset is set to the beginning of the file (see lseek(2)).

默认情况下，新文件描述符设置为在 execve(2) 中保持打开状态（即 fcntl(2) 中描述的 FD_CLOEXEC 文件描述符标志最初被禁用）； 如下所述的 O_CLOEXEC 标志可用于更改此默认值。 文件偏移量设置为文件的开头（请参阅 lseek(2)）。

A call to open() creates a new open file description, an entry in the system-wide table of open files.  The open file description records the file offset and the file status flags (see below).  A file descriptor is a reference to an open file description; this reference is unaffected if pathname is subsequently removed or modified to refer to a different file.  For further details on open file descriptions, see NOTES.

对 open() 的调用会创建一个新的打开文件描述，即系统范围的打开文件表中的一个条目。 打开的文件描述记录了文件偏移量和文件状态标志（见下文）。 文件描述符是对打开文件描述的引用； 如果随后删除或修改路径名以引用不同的文件，则此引用不受影响。 有关打开文件描述的更多详细信息，请参阅注释。

The argument flags must include one of the following *access modes*: O_RDONLY, O_WRONLY, or O_RDWR.  These request opening the file read-only, write-only, or read/write, respectively.

参数标志必须包括以下访问模式之一：O_RDONLY、O_WRONLY 或 O_RDWR。 这些请求分别以只读、只写或读/写方式打开文件。

In addition, zero or more file creation flags and file status flags can be bitwise-or'd in flags.  The file creation flags are O_CLOEXEC, O_CREAT, O_DIRECTORY, O_EXCL, O_NOCTTY, O_NOFOLLOW,  O_TMPFILE, and O_TRUNC.  The file status flags are all of the remaining flags listed below.  The distinction between these two  groups of flags is that the file creation flags affect the semantics of the open operation itself, while the file status  flags affect the semantics of subsequent I/O operations.  The file status flags can be retrieved and (in some cases) modified; see fcntl(2) for details.

此外，零个或多个文件创建标志和文件状态标志可以在标志中按位或运算。 文件创建标志是 O_CLOEXEC、O_CREAT、O_DIRECTORY、O_EXCL、O_NOCTTY、O_NOFOLLOW、O_TMPFILE 和 O_TRUNC。 文件状态标志是下面列出的所有剩余标志。 这两组标志的区别在于文件创建标志影响打开操作本身的语义，而文件状态标志影响后续I/O操作的语义。 可以检索和（在某些情况下）修改文件状态标志； 有关详细信息，请参见 fcntl(2)。

The full list of file creation flags and file status flags is as
       follows:

文件创建标志和文件状态标志的完整列表如下
        如下：

 ### O_APPEND

> The file is opened in append mode.  Before each write(2), the file offset is positioned at the end of the file, as if with lseek(2).  The modification of the file offset and the write operation are performed as a single atomic step.
>
> 该文件以附加模式打开。 在每次 write(2) 之前，文件偏移量位于文件末尾，就像使用 lseek(2) 一样。 文件偏移量的修改和写入操作作为单个原子步骤执行。

> O_APPEND may lead to corrupted files on NFS filesystems if more than one process appends data to a file at once. This is because NFS does not support appending to a file, so the client kernel has to simulate it, which can't be done without a race condition.
>
> 如果多个进程同时将数据附加到文件，O_APPEND 可能会导致 NFS 文件系统上的文件损坏。 这是因为 NFS 不支持附加到文件，所以客户端内核必须模拟它，这在没有竞争条件的情况下无法完成。

### O_ASYNC

> Enable signal-driven I/O: generate a signal (SIGIO by default, but this can be changed via fcntl(2)) when input or output becomes possible on this file descriptor.  This feature is available only for terminals, pseudoterminals, sockets, and (since Linux 2.6) pipes and FIFOs.  See fcntl(2) for further details.  See also BUGS, below.
>
> 启用信号驱动 I/O：当此文件描述符上的输入或输出成为可能时，生成一个信号（默认为 SIGIO，但这可以通过 fcntl(2) 更改）。 此功能仅适用于终端、伪终端、套接字以及（自 Linux 2.6 起）管道和 FIFO。 有关详细信息，请参阅 fcntl(2)。 另请参阅下面的错误。

O_CLOEXEC (since Linux 2.6.23)

> Enable the close-on-exec flag for the new file descriptor. Specifying this flag permits a program to avoid additional fcntl(2) F_SETFD operations to set the FD_CLOEXEC flag.
>
> 为新文件描述符启用 close-on-exec 标志。 指定此标志允许程序避免额外的 fcntl(2) F_SETFD 操作来设置 FD_CLOEXEC 标志。

> Note that the use of this flag is essential in some multithreaded programs, because using a separate fcntl(2) F_SETFD operation to set the FD_CLOEXEC flag does not suffice to avoid race conditions where one thread opens a file descriptor and attempts to set its close-on-exec flag using fcntl(2) at the same time as another thread does a fork(2) plus execve(2).  Depending on the order of execution, the race may lead to the file descriptor returned by open() being unintentionally leaked to the program executed by the child process created by fork(2). (This kind of race is in principle possible for any system call that creates a file descriptor whose close-on-exec flag should be set, and various other Linux system calls provide an equivalent of the O_CLOEXEC flag to deal with this problem.)
>
> 请注意，在某些多线程程序中使用此标志是必不可少的，因为使用单独的 fcntl(2) F_SETFD 操作来设置 FD_CLOEXEC 标志并不足以避免一个线程打开文件描述符并尝试设置其 `close -on-exec` 标志在使用 fcntl(2) 的同时另一个线程执行 fork(2) 和 execve(2)。 根据执行顺序，争用可能会导致 open() 返回的文件描述符无意中泄露给由 fork(2) 创建的子进程执行的程序。 （原则上，任何创建文件描述符的系统调用都可能发生这种竞争，该文件描述符应设置 close-on-exec 标志，并且各种其他 Linux 系统调用提供了等效的 O_CLOEXEC 标志来处理此问题。）

### O_CREAT

> If pathname does not exist, create it as a regular file.
>
> 如果*pathname* 不存在，将其创建为常规文件。

> The owner (user ID) of the new file is set to the effective user ID of the process.
>
> 新文件的所有者（用户 ID）设置为进程的有效用户 ID。

> The group ownership (group ID) of the new file is set either to the effective group ID of the process (System V semantics) or to the group ID of the parent directory (BSD semantics).  On Linux, the behavior depends on whether the set-group-ID mode bit is set on the parent directory: if that bit is set, then BSD semantics apply; otherwise, System V semantics apply.  For some filesystems, the behavior also depends on the bsdgroups and sysvgroups mount options described in mount(8).
>
> 新文件的组所有权（组 ID）设置为进程的有效组 ID（System V 语义）或父目录的组 ID（BSD 语义）。 在 Linux 上，行为取决于是否在父目录上设置了 set-group-ID 模式位：如果设置了该位，则应用 BSD 语义； 否则，System V 语义适用。 对于某些文件系统，行为还取决于 mount(8) 中描述的 *bsdgroups* 和 *sysvgroups* 挂载选项。

>The *mode* argument specifies the file mode bits to be applied when a new file is created.  If neither O_CREAT nor O_TMPFILE is specified in flags, then mode is ignored (and can thus be specified as 0, or simply omitted).  The mode argument must be supplied if O_CREAT or O_TMPFILE is specified in flags; if it is not supplied, some arbitrary bytes from the stack will be applied as the file mode.
>
>*mode* 参数指定创建新文件时要应用的文件模式位。 如果在标志中既没有指定 O_CREAT 也没有指定 O_TMPFILE，则模式被忽略（因此可以指定为 0，或简单地省略）。 如果在标志中指定了 O_CREAT 或 O_TMPFILE，则必须提供模式参数； 如果未提供，则堆栈中的一些任意字节将用作文件模式。

> The effective mode is modified by the process's umask in the usual way: in the absence of a default ACL, the mode of the created file is (mode & ~umask).
>
> 有效模式由进程的 umask 以通常的方式修改：在没有默认 ACL 的情况下，创建文件的模式为 (mode & ~umask)。

>Note that mode applies only to future accesses of the newly created file; the open() call that creates a read-only file may well return a read/write file descriptor.
>
>请注意，模式仅适用于将来访问新创建的文件； 创建只读文件的 open() 调用很可能会返回读/写文件描述符。

>The following symbolic constants are provided for mode:
>
>为模式提供了以下符号常量：

>S_IRWXU  00700 user (file owner) has read, write, and execute permission
>
>​                              用户（文件所有者）具有读、写和执行权限

> S_IRUSR  00400 user has read permission
>
> ​                             用户具有读权限

> S_IWUSR  00200 user has write permission
>
> ​                              用户具有写权限

>S_IXUSR  00100 user has execute permission
>
>​                             用户具有执行权限

>S_IRWXG  00070 group has read, write, and execute permission
>
>​                              组具有读、写和执行权限

> S_IRGRP  00040 group has read permission
>
> ​                             组具有读权限

> S_IWGRP  00020 group has write permission
>
> ​                             组具有写权限

> S_IXGRP  00010 group has execute permission
>
> ​                             组具有执行权限

> S_IRWXO  00007 others have read, write, and execute permission
>
> ​                             其他人具有读、写和执行权限

>S_IROTH  00004 others have read permission
>
>​                             其他人具有读权限

> S_IWOTH  00002 others have write permission
>
> ​                             其他人具有写权限

> S_IXOTH  00001 others have execute permission
>
> ​                             其他人具有执行权限

> According to POSIX, the effect when other bits are set in mode is unspecified.  On Linux, the following bits are also honored in mode:
>
> 根据 POSIX，未指定在 *mode* 中设置其他位时的效果。 在 Linux 上，以下位在模式下也受到尊重：

> S_ISUID  0004000 set-user-ID bit
>
> ​                               设置用户 ID 位

> S_ISGID  0002000 set-group-ID bit (see inode(7)).
>
> ​                                set-group-ID 位（参见 inode(7)）

> S_ISVTX  0001000 sticky bit (see inode(7)).
>
> ​                                粘性位（参见 inode(7)）。

### O_DIRECT (since Linux 2.4.10)

> Try to minimize cache effects of the I/O to and from this file.  In general this will degrade performance, but it is useful in special situations, such as when applications do their own caching.  File I/O is done directly to/from user-space buffers.  The O_DIRECT flag on its own makes an effort to transfer data synchronously, but does not give the guarantees of the O_SYNC flag that data and necessary metadata are transferred.  To guarantee synchronous I/O, O_SYNC must be used in addition to O_DIRECT.  See NOTES  below for further discussion.
>
> 尽量减少进出该文件的 I/O 的缓存影响。 一般来说，这会降低性能，但在特殊情况下很有用，例如当应用程序进行自己的缓存时。 文件 I/O 直接与用户空间缓冲区进行。 O_DIRECT 标志自己努力同步传输数据，但不提供 O_SYNC 标志的保证，即传输数据和必要的元数据。 为了保证同步 I/O，除了 O_DIRECT 之外，还必须使用 O_SYNC。 有关进一步讨论，请参见下面的注释。

>A semantically similar (but deprecated) interface for block devices is described in raw(8).
>
>raw(8) 中描述了块设备的语义相似（但已弃用）的接口。

### O_DIRECTORY

> If pathname is not a directory, cause the open to fail. This flag was added in kernel version 2.1.126, to avoid denial-of-service problems if opendir(3) is called on a FIFO or tape device.
>
> 如果 *pathname* 不是一个目录，导致打开失败。这个标志是在内核2.1.126版本中加入的，以避免在FIFO或磁带设备上调用opendir(3)时出现拒绝服务问题。

### O_DSYNC

> Write operations on the file will complete according to the requirements of synchronized I/O data integrity completion.
>
> 对文件的写操作将根据同步I/O数据完整性的要求完成。

>By the time write(2) (and similar) return, the output data has been transferred to the underlying hardware, along with any file metadata that would be required to retrieve that data (i.e., as though each write(2) was followed by a call to fdatasync(2)).  *See NOTES below.*
>
>当 write(2) （和类似的）返回时，输出数据已经传输到底层硬件，以及检索该数据所需的任何文件元数据（即，就好像每个 write(2) 后面都有 调用 fdatasync(2))。 请参阅下面的注释。

### O_EXCL 

> Ensure that this call creates the file: if this flag is specified in conjunction with O_CREAT, and pathname already exists, then open() fails with the error EEXIST.
>
> 确保此调用创建文件：如果此标志与 O_CREAT 一起指定，并且 *pathname* 已存在，则 open() 将失败并返回错误 EEXIST。

>When these two flags are specified, symbolic links are not followed: if pathname is a symbolic link, then open()  fails regardless of where the symbolic link points.
>
>当指定这两个标志时，不遵循符号链接：如果路径名是符号链接，则无论符号链接指向何处， open() 都会失败。

>In general, the behavior of O_EXCL is undefined if it is used without O_CREAT.  There is one exception: on Linux 2.6 and later, O_EXCL can be used without O_CREAT if pathname refers to a block device.  If the block device is in use by the system (e.g., mounted), open() fails with the error EBUSY.
>
>通常，如果在没有 O_CREAT 的情况下使用 O_EXCL 的行为，则它的行为是未定义的。 有一个例外：在 Linux 2.6 及更高版本上，如果路径名引用块设备，则可以在没有 O_CREAT 的情况下使用 O_EXCL。 如果系统正在使用块设备（例如，已挂载），则 open() 将失败并返回错误 EBUSY。

>On NFS, O_EXCL is supported only when using NFSv3 or later on kernel 2.6 or later.  In NFS environments where O_EXCL  support is not provided, programs that rely on it for  performing locking tasks will contain a race condition.  Portable programs that want to perform atomic file locking  using a lockfile, and need to avoid reliance on NFS support for O_EXCL, can create a unique file on the same filesystem (e.g., incorporating hostname and PID), and use link(2) to make a link to the lockfile.  If link(2) returns 0, the lock is successful.  Otherwise, use stat(2) on the unique file to check if its link count has increased to 2, in which case the lock is also successful.
>
>在 NFS 上，仅当在内核 2.6 或更高版本上使用 NFSv3 或更高版本时才支持 O_EXCL。 在不提供 O_EXCL 支持的 NFS 环境中，依赖它执行锁定任务的程序将包含竞争条件。 想要使用 lockfile 执行原子文件锁定并且需要避免依赖 NFS 对 O_EXCL 支持的便携式程序，可以在同一文件系统上创建唯一文件（例如，合并主机名和 PID），并使用 link(2) 使 锁定文件的链接。 如果link(2) 返回0，则锁定成功。 否则，对唯一文件使用 stat(2) 来检查其链接数是否增加到 2，在这种情况下，锁定也是成功的。

### O_LARGEFILE

> (LFS) Allow files whose sizes cannot be represented in an off_t (but can be represented in an off64_t) to be opened. The _LARGEFILE64_SOURCE macro must be defined (before including any header files) in order to obtain this definition.  Setting the _FILE_OFFSET_BITS feature test macro to 64 (rather than using O_LARGEFILE) is the preferred method of accessing large files on 32-bit systems (see feature_test_macros(7)).
>
> (LFS) 允许打开大小不能用 off_t 表示（但可以用 *off64_t* 表示）的文件。 必须定义 _LARGEFILE64_SOURCE 宏（在包含任何头文件之前）才能获得此定义。 将 _FILE_OFFSET_BITS 功能测试宏设置为 64（而不是使用 O_LARGEFILE）是在 32 位系统上访问大文件的首选方法（请参阅 feature_test_macros(7)）。

### O_NOATIME (since Linux 2.6.8)

> Do not update the file last access time (*st_atime* in the inode) when the file is read(2).
>
> 读取文件时不要更新文件的上次访问时间（inode 中的 *st_atime*）(2)。

> This flag can be employed only if one of the following conditions is true:
>
> 仅当以下条件之一为真时，才能使用此标志：

>*  The effective UID of the process matches the owner UID of the file.
>*  进程的有效 UID 与文件的所有者 UID 匹配。

> *  The calling process has the CAP_FOWNER capability in its user namespace and the owner UID of the file has a mapping in the namespace.
> *  调用进程在其用户命名空间中具有 CAP_FOWNER 能力，并且文件的所有者 UID 在命名空间中具有映射。

> This flag is intended for use by indexing or backup programs, where its use can significantly reduce the amount of disk activity.  This flag may not be effective on all filesystems.  One example is NFS, where the server maintains the access time.
>
> 此标志旨在供索引或备份程序使用，在这些程序中使用它可以显着减少磁盘活动量。 此标志可能并非对所有文件系统都有效。 一个例子是 NFS，服务器维护访问时间。

### O_NOCTTY

> If *pathname* refers to a terminal device—see tty(4)—it will not become the process's controlling terminal even if the process does not have one.
>
> 如果*pathname*指的是终端设备——参见 tty(4)——即使进程没有终端设备，它也不会成为进程的控制终端。

### O_NOFOLLOW

>  If the trailing component (i.e., basename) of pathname is a symbolic link, then the open fails, with the error ELOOP.  Symbolic links in earlier components of the pathname will still be followed.  (Note that the ELOOP error that can occur in this case is indistinguishable from the case where an open fails because there are too many symbolic links found while resolving components in the prefix part of the pathname.)
>
> 如果*pathname*的尾随组件（即基本名称）是符号链接，则打开失败，并出现错误 ELOOP。 仍将遵循路径名早期组件中的符号链接。 （请注意，在这种情况下可能发生的 ELOOP 错误与打开失败的情况无法区分，因为在解析路径名前缀部分中的组件时发现了太多符号链接。）

> This flag is a FreeBSD extension, which was added to Linux in version 2.1.126, and has subsequently been standardized in POSIX.1-2008.
>
> 此标志是 FreeBSD 扩展，在 2.1.126 版本中添加到 Linux，随后在 POSIX.1-2008 中被标准化。

> See also O_PATH below.
>
> 另请参见下面的 O_PATH。

### O_NONBLOCK or O_NDELAY

> When possible, the file is opened in nonblocking mode. Neither the open() nor any subsequent I/O operations on the file descriptor which is returned will cause the calling process to wait.
>
> 如果可能，文件以非阻塞模式打开。 open() 和返回的文件描述符上的任何后续 I/O 操作都不会导致调用进程等待。

> Note that the setting of this flag has no effect on the operation of poll(2), select(2), epoll(7), and similar, since those interfaces merely inform the caller about whether a file descriptor is "ready", meaning that an I/O operation performed on the file descriptor with the O_NONBLOCK flag clear would not block.
>
> 请注意，此标志的设置对 poll(2)、select(2)、epoll(7) 等的操作没有影响，因为这些接口只是通知调用者文件描述符是否“准备好”，这意味着 对带有 O_NONBLOCK 标志清除的文件描述符执行的 I/O 操作不会阻塞。

> Note that this flag has no effect for regular files and block devices; that is, I/O operations will (briefly) block when device activity is required, regardless of whether O_NONBLOCK is set.  Since O_NONBLOCK semantics might eventually be implemented, applications should not depend upon blocking behavior when specifying this flag for regular files and block devices.
>
> 请注意，此标志对常规文件和块设备无效； 也就是说，无论是否设置了 O_NONBLOCK，当需要设备活动时，I/O 操作都会（短暂地）阻塞。 由于最终可能会实现 O_NONBLOCK 语义，因此在为常规文件和块设备指定此标志时，应用程序不应依赖于阻塞行为。

> For the handling of FIFOs (named pipes), see also fifo(7). For a discussion of the effect of O_NONBLOCK in conjunction with mandatory file locks and with file leases, see fcntl(2).
>
> 有关 FIFO（命名管道）的处理，另请参见 fifo(7)。 有关 O_NONBLOCK 与强制文件锁定和文件租约结合的影响的讨论，请参阅 fcntl(2)。

### O_PATH (since Linux 2.6.39)

> Obtain a file descriptor that can be used for two purposes: to indicate a location in the filesystem tree and to perform operations that act purely at the file descriptor level.  The file itself is not opened, and other file operations (e.g., read(2), write(2), fchmod(2), fchown(2), fgetxattr(2), ioctl(2), mmap(2)) fail with the error EBADF.
>
> 获取可用于两个目的的文件描述符：指示文件系统树中的位置以及执行纯粹在文件描述符级别执行的操作。 文件本身未打开，其他文件操作（例如，read(2)、write(2)、fchmod(2)、fchown(2)、fgetxattr(2)、ioctl(2)、mmap(2)）失败 带有错误 EBADF。

>The following operations can be performed on the resulting file descriptor:
>
>可以对生成的文件描述符执行以下操作：

> * close(2).
>
> * fchdir(2),  if the file descriptor refers to a directory (since Linux 3.5). 如果文件描述符指向一个目录（从 Linux 3.5 开始）。
>
> * fstat(2) (since Linux 3.6).
>
> * fstatfs(2) (since Linux 3.12).
>
> * Duplicating the file descriptor (dup(2), fcntl(2) F_DUPFD, etc.). 复制文件描述符（dup(2)、fcntl(2) F_DUPFD 等）。
>
> * Getting and setting file descriptor flags (fcntl(2) F_GETFD and F_SETFD). 获取和设置文件描述符标志（fcntl(2) F_GETFD 和 F_SETFD）。
>
> * Retrieving open file status flags using the fcntl(2) F_GETFL operation: the returned flags will include the bit O_PATH. 使用 fcntl(2) F_GETFL 操作检索打开文件状态标志：返回的标志将包括位 O_PATH。
>
> * Passing the file descriptor as the dirfd argument of openat() and the other "*at()" system calls.  This includes linkat(2) with AT_EMPTY_PATH (or via procfs using AT_SYMLINK_FOLLOW) even if the file is not a directory.
>
>   将文件描述符作为 openat() 和其他“*at()”系统调用的 dirfd 参数传递。 这包括带有 AT_EMPTY_PATH 的 linkat(2)（或通过使用 AT_SYMLINK_FOLLOW 的 procfs），即使文件不是目录。
>
> * Passing the file descriptor to another process via a UNIX domain socket (see SCM_RIGHTS in unix(7)).
>
>   通过 UNIX 域套接字将文件描述符传递给另一个进程（请参阅 unix(7) 中的 SCM_RIGHTS）。

>When O_PATH is specified in flags, flag bits other than O_CLOEXEC, O_DIRECTORY, and O_NOFOLLOW are ignored.
>
>在标志中指定 O_PATH 时，忽略 O_CLOEXEC、O_DIRECTORY 和 O_NOFOLLOW 以外的标志位。

> Opening a file or directory with the O_PATH flag requires no permissions on the object itself (but does require execute permission on the directories in the path prefix).Depending on the subsequent operation, a check for suitable file permissions may be performed (e.g.,  fchdir(2) requires execute permission on the directory referred to by its file descriptor argument).  By contrast, obtaining a reference to a filesystem object by opening it with the O_RDONLY flag requires that the caller have read permission on the object, even when the subsequent operation (e.g., fchdir(2), fstat(2)) does not require read permission on the object.
>
> 使用 O_PATH 标志打开文件或目录不需要对象本身的权限（但确实需要对路径前缀中的目录的执行权限）。根据后续操作，可能会执行合适的文件权限检查（例如，fchdir (2) 需要对其文件描述符参数引用的目录具有执行权限）。 相比之下，通过使用 O_RDONLY 标志打开文件系统对象来获取对文件系统对象的引用需要调用者对该对象具有读取权限，即使后续操作（例如 fchdir(2)、fstat(2)）不需要读取也是如此 对象的权限。

> If *pathname* is a symbolic link and the O_NOFOLLOW flag is also specified, then the call returns a file descriptor referring to the symbolic link.  This file descriptor can be used as the dirfd argument in calls to fchownat(2), fstatat(2), linkat(2), and readlinkat(2) with an empty pathname to have the calls operate on the symbolic link.
>
> 如果 *pathname* 是符号链接并且还指定了 O_NOFOLLOW 标志，则调用返回引用符号链接的文件描述符。 此文件描述符可用作调用 fchownat(2)、fstatat(2)、linkat(2) 和 readlinkat(2) 时的 dirfd 参数，路径名为空，以使调用对符号链接进行操作。

> If *pathname* refers to an automount point that has not yet been triggered, so no other filesystem is mounted on it, then the call returns a file descriptor referring to the automount directory without triggering a mount. fstatfs(2) can then be used to determine if it is, in fact, an untriggered automount point (.f_type == AUTOFS_SUPER_MAGIC).
>
> 如果 *pathname* 引用尚未触发的自动挂载点，因此没有其他文件系统挂载在其上，则调用返回引用自动挂载目录的文件描述符而不触发挂载。 然后可以使用 fstatfs(2) 来确定它是否实际上是未触发的自动挂载点 (.f_type == AUTOFS_SUPER_MAGIC)。

> One use of O_PATH for regular files is to provide the equivalent of POSIX.1's O_EXEC functionality.  This permits us to open a file for which we have execute permission but not read permission, and then execute that file, with steps something like the following:
>
> 对常规文件使用 O_PATH 的一种用途是提供与 POSIX.1 的 O_EXEC 功能等效的功能。 这允许我们打开一个我们有执行权限但没有读取权限的文件，然后执行该文件，步骤如下：

```c
char buf[PATH_MAX];
fd = open("some_prog", O_PATH);
snprintf(buf, PATH_MAX, "/proc/self/fd/%d", fd);
execl(buf, "some_prog", (char *) NULL);
```

>An O_PATH file descriptor can also be passed as the argument of fexecve(3).
>
>O_PATH 文件描述符也可以作为 fexecve(3) 的参数传递。

### O_SYNC 

> Write operations on the file will complete according to  the requirements of synchronized I/O file integrity completion (by contrast with the synchronized I/O data integrity completion provided by O_DSYNC.)
>
> 对文件的写操作将按照同步I/O文件完整性完成的要求完成（与O_DSYNC提供的同步I/O数据完整性完成对比）。

> By the time write(2) (or similar) returns, the output data and associated file metadata have been transferred to the underlying hardware (i.e., as though each write(2) was followed by a call to fsync(2)).  See NOTES below.
>
> 到 write(2)（或类似的）返回时，输出数据和相关文件元数据已传输到底层硬件（即，就好像每次 write(2) 之后都调用了 fsync(2)）。 请参阅下面的注释。

### O_TMPFILE (since Linux 3.11)

> Create an unnamed temporary regular file.  The pathname argument specifies a directory; an unnamed inode will be created in that directory's filesystem.  Anything written to the resulting file will be lost when the last file descriptor is closed, unless the file is given a name.
>
> 创建一个未命名的临时常规文件。 pathname 参数指定一个目录； 将在该目录的文件系统中创建一个未命名的 inode。 当最后一个文件描述符关闭时，写入结果文件的任何内容都将丢失，除非为文件指定名称。

> O_TMPFILE must be specified with one of O_RDWR or O_WRONLY and, optionally, O_EXCL.  If O_EXCL is not specified, then linkat(2) can be used to link the temporary file into the filesystem, making it permanent, using code like the following:
>
> O_TMPFILE 必须使用 O_RDWR 或 O_WRONLY 之一指定，也可以使用 O_EXCL。 如果未指定 O_EXCL，则可以使用 linkat(2) 将临时文件链接到文件系统，使其永久化，使用如下代码：

```c
char path[PATH_MAX];
fd = open("/path/to/dir", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);

/* File I/O on 'fd'... */

linkat(fd, "", AT_FDCWD, "/path/for/file", AT_EMPTY_PATH);

/* If the caller doesn't have the CAP_DAC_READ_SEARCH capability (needed to use AT_EMPTY_PATH with linkat(2)), and there is a proc(5) filesystem mounted, then the linkat(2) call above can be replaced with:

snprintf(path, PATH_MAX,  "/proc/self/fd/%d", fd);
linkat(AT_FDCWD, path, AT_FDCWD, "/path/for/file", AT_SYMLINK_FOLLOW);
*/
```

>In this case, the open() mode argument determines the file permission mode, as with O_CREAT.
>
>在这种情况下，open() 模式参数确定文件权限模式，与 O_CREAT 一样。

> Specifying O_EXCL in conjunction with O_TMPFILE prevents a temporary file from being linked into the filesystem in the above manner.  (Note that the meaning of O_EXCL in this case is different from the meaning of O_EXCL otherwise.)
>
> 将 O_EXCL 与 O_TMPFILE 一起指定可防止临时文件以上述方式链接到文件系统。 （请注意，这种情况下 O_EXCL 的含义与其他情况下 O_EXCL 的含义不同。）

>There are two main use cases for O_TMPFILE:
>
>O_TMPFILE 有两个主要用例：
>
> *  Improved tmpfile(3) functionality: race-free creation of temporary files that 
>              
>              (1) are automatically deleted when closed; 
>              
>              (2) can never be reached via any pathname;
>              
>              (3) are not subject to symlink attacks; and 
>              
>              (4) do not require the caller to devise unique names.
>              
>              改进的 tmpfile(3) 功能：无竞争地创建临时文件，
>              
>              (1) 关闭时自动删除；
>              
>              (2) 永远无法通过任何路径名到达；
>              
>              (3) 不受符号链接攻击；
>              
>              (4) 不要求调用者设计唯一的名称。
>
>* Creating a file that is initially invisible, which is then populated with data and adjusted to have appropriate filesystem attributes (fchown(2), fchmod(2), fsetxattr(2), etc.)  before being atomically linked into the filesystem in a fully formed state(using linkat(2) as described above).
>
>     创建一个最初不可见的文件，然后填充数据并调整为具有适当的文件系统属性（fchown(2)、fchmod(2)、fsetxattr(2) 等），然后以原子方式链接到文件系统中 形成状态（如上所述使用 linkat(2)）。

>O_TMPFILE requires support by the underlying filesystem; only a subset of Linux filesystems provide that support. In the initial implementation, support was provided in the ext2, ext3, ext4, UDF, Minix, and tmpfs filesystems. Support for other filesystems has subsequently been added as follows: XFS (Linux 3.15); Btrfs (Linux 3.16); F2FS (Linux 3.16); and ubifs (Linux 4.9)
>
>O_TMPFILE 需要底层文件系统的支持； 只有一部分 Linux 文件系统提供这种支持。 在最初的实现中，在 ext2、ext3、ext4、UDF、Minix 和 tmpfs 文件系统中提供了支持。 随后添加了对其他文件系统的支持，如下所示：XFS (Linux 3.15)； Btrfs (Linux 3.16); F2FS（Linux 3.16）； 和 ubifs (Linux 4.9)

### O_TRUNC

>If the file already exists and is a regular file and the access mode allows writing (i.e., is O_RDWR or O_WRONLY) it will be truncated to length 0.  If the file is a FIFO or terminal device file, the O_TRUNC flag is ignored. Otherwise, the effect of O_TRUNC is unspecified.
>
>如果文件已经存在并且是常规文件并且访问模式允许写入（即，是 O_RDWR 或 O_WRONLY），它将被截断为长度 0。如果文件是 FIFO 或终端设备文件，则忽略 O_TRUNC 标志。 否则，未指定 O_TRUNC 的效果。

## creat()
​       A call to creat() is equivalent to calling open() with flags equal to O_CREAT|O_WRONLY|O_TRUNC.

对 creat() 的调用等效于调用带有等于 O_CREAT|O_WRONLY|O_TRUNC 的标志的 open()。

## openat()
​       The openat() system call operates in exactly the same way as open(), except for the differences described here.

openat() 系统调用的操作方式与 open() 完全相同，除了此处描述的不同之处。

The dirfd argument is used in conjunction with the pathname argument as follows:

dirfd 参数与 pathname 参数一起使用，如下所示：

 * If the pathname given in pathname is absolute, then dirfd is ignored.

      如果 pathname 中给出的路径名是绝对的，则忽略 dirfd。

* If the pathname given in pathname is relative and dirfd is the special value AT_FDCWD, then pathname is interpreted relative to the current working directory of the calling process (like open()).

     如果在 pathname 中给出的路径名是相对的并且 dirfd 是特殊值 AT_FDCWD，那么 pathname 被解释为相对于调用进程的当前工作目录（如 open()）。

* If the pathname given in pathname is relative, then it is interpreted relative to the directory referred to by the file descriptor dirfd (rather than relative to the current working directory of the calling process, as is done by open() for a relative pathname).  In this case, dirfd must be a directory that was opened for reading (O_RDONLY) or using the O_PATH flag.

     如果在 pathname 中给出的路径名是相对的，那么它被解释为相对于文件描述符 dirfd 引用的目录（而不是相对于调用进程的当前工作目录，就像 open() 对相对路径名所做的那样） . 在这种情况下，dirfd 必须是为读取 (O_RDONLY) 或使用 O_PATH 标志而打开的目录。

If the pathname given in pathname is relative, and dirfd is not a valid file descriptor, an error (EBADF) results.  (Specifying an invalid file descriptor number in dirfd can be used as a means to ensure that pathname is absolute.)

如果 pathname 中给出的路径名是相对的，并且 dirfd 不是有效的文件描述符，则会产生错误 (EBADF)。 （在 dirfd 中指定一个无效的文件描述符编号可以用来确保路径名是绝对的。）

## openat2(2)
​       The openat2(2) system call is an extension of openat(), and provides a superset of the features of openat().  It is documented separately, in openat2(2).

openat2(2) 系统调用是 openat() 的扩展，并提供了 openat() 功能的超集。 它在 openat2(2) 中单独记录。

## RETURN VALUE

On success, open(), openat(), and creat() return the new file descriptor (a nonnegative integer).  On error, -1 is returned and errno is set to indicate the error.

成功时，open()、openat() 和 creat() 返回新的文件描述符（非负整数）。 出错时，返回 -1 并设置 errno 以指示错误。

## ERRORS

open(), openat(), and creat() can fail with the following errors:

open()、openat() 和 creat() 可能会失败并出现以下错误：

### EACCES 

The requested access to the file is not allowed, or search permission is denied for one of the directories in the path prefix of pathname, or the file did not exist yet and write access to the parent directory is not allowed.  (See also path_resolution(7).)

不允许请求访问该文件，或拒绝对 pathname 的路径前缀中的目录之一的搜索权限，或该文件尚不存在且不允许对父目录进行写访问。 （另见 path_resolution(7)。）

### EACCES 

Where O_CREAT is specified, the protected_fifos or protected_regular sysctl is enabled, the file already exists and is a FIFO or regular file, the owner of the  file is neither the current user nor the owner of the containing directory, and the containing directory is both world- or group-writable and sticky.  For details, see the  descriptions of /proc/sys/fs/protected_fifos and /proc/sys/fs/protected_regular in proc(5).

指定 O_CREAT 的地方，启用 protected_fifos 或 protected_regular sysctl，文件已经存在并且是 FIFO 或常规文件，文件的所有者既不是当前用户也不是包含目录的所有者，包含目录是两个世界 - 或组可写和粘性。 详见proc(5)中/proc/sys/fs/protected_fifos和/proc/sys/fs/protected_regular的描述。

### EBADF  

(openat()) pathname is relative but dirfd is neither AT_FDCWD nor a valid file descriptor.

(openat()) 路径名是相对的，但 dirfd 既不是 AT_FDCWD 也不是有效的文件描述符。

### EBUSY  

O_EXCL was specified in flags and pathname refers to a block device that is in use by the system (e.g., it is mounted).

O_EXCL 在标志中指定，路径名指的是系统正在使用的块设备（例如，它已挂载）。

### EDQUOT

Where O_CREAT is specified, the file does not exist, and the user's quota of disk blocks or inodes on the filesystem has been exhausted.

如果指定了 O_CREAT，则文件不存在，并且文件系统上用户的磁盘块或 inode 配额已用完。

### EEXIST

pathname already exists and O_CREAT and O_EXCL were used.

路径名已经存在并且使用了 O_CREAT 和 O_EXCL。

### EFAULT

pathname points outside your accessible address space.

路径名指向你可访问的地址空间之外。

### EFBIG

See EOVERFLOW.

请参阅 EOVERFLOW。

### EINTR

While blocked waiting to complete an open of a slow device (e.g., a FIFO; see fifo(7)), the call was interrupted by a signal handler; see signal(7).

当阻塞等待完成慢速设备的打开时（例如，FIFO；参见 fifo(7)），调用被信号处理程序中断； 见信号（7）。

### EINVAL

The filesystem does not support the O_DIRECT flag.  See NOTES for more information.

文件系统不支持 O_DIRECT 标志。 有关详细信息，请参阅注释。

### EINVAL

Invalid value in flags.

标志中的值无效。

### EINVAL

O_TMPFILE was specified in flags, but neither O_WRONLY nor O_RDWR was specified.

在标志中指定了 O_TMPFILE，但没有指定 O_WRONLY 和 O_RDWR。

### EINVAL

O_CREAT was specified in flags and the final component ("basename") of the new file's pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem).

O_CREAT 在 flags 中指定，并且新文件路径名的最后一个组件（“basename”）无效（例如，它包含底层文件系统不允许的字符）。

### EINVAL 

The final component ("basename") of pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem).

路径名的最后一个组件（“basename”）无效（例如，它包含底层文件系统不允许的字符）。

### EISDIR

pathname refers to a directory and the access requested involved writing (that is, O_WRONLY or O_RDWR is set).

pathname 指的是一个目录，并且请求的访问涉及写入（即设置了 O_WRONLY 或 O_RDWR）。

### EISDIR

pathname refers to an existing directory, O_TMPFILE and one of O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality.

路径名指的是现有目录，O_TMPFILE 和 O_WRONLY 或 O_RDWR 之一在标志中指定，但此内核版本不提供 O_TMPFILE 功能。

### ELOOP

Too many symbolic links were encountered in resolving pathname.

解析路径名时遇到太多符号链接。

### ELOOP

pathname was a symbolic link, and flags specified O_NOFOLLOW but not O_PATH.

pathname 是一个符号链接，并且标志指定了 O_NOFOLLOW 但不是 O_PATH。

### EMFILE

The per-process limit on the number of open file descriptors has been reached (see the description of RLIMIT_NOFILE in getrlimit(2)).

已达到每个进程打开文件描述符数量的限制（参见 getrlimit(2) 中 RLIMIT_NOFILE 的描述）。

### ENAMETOOLONG
pathname was too long.

路径名太长。

### ENFILE

The system-wide limit on the total number of open files has been reached.

已达到打开文件总数的系统范围限制。

### ENODEV

pathname refers to a device special file and no corresponding device exists.  (This is a Linux kernel bug; in this situation ENXIO must be returned.)

pathname 指的是设备专用文件，不存在对应的设备。 （这是一个 Linux 内核错误；在这种情况下必须返回 ENXIO。）

### ENOENT

O_CREAT is not set and the named file does not exist.

O_CREAT 未设置且命名文件不存在。

### ENOENT

A directory component in pathname does not exist or is a dangling symbolic link.

路径名中的目录组件不存在或者是悬空符号链接。

### ENOENT

pathname refers to a nonexistent directory, O_TMPFILE and one of O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality.

路径名指的是不存在的目录，O_TMPFILE 和 O_WRONLY 或 O_RDWR 之一在标志中指定，但此内核版本不提供 O_TMPFILE 功能。

### ENOMEM

The named file is a FIFO, but memory for the FIFO buffer can't be allocated because the per-user hard limit on memory allocation for pipes has been reached and the caller is not privileged; see pipe(7).

命名文件是 FIFO，但无法分配 FIFO 缓冲区的内存，因为已达到每个用户对管道内存分配的硬限制并且调用者没有特权； 见管道（7）。

### ENOMEM

Insufficient kernel memory was available.

可用的内核内存不足。

### ENOSPC

pathname was to be created but the device containing pathname has no room for the new file.

要创建路径名，但包含路径名的设备没有空间容纳新文件。

### ENOTDIR
 A component used as a directory in pathname is not, in fact, a directory, or O_DIRECTORY was specified and pathname was not a directory.

在路径名中用作目录的组件实际上不是目录，或者指定了 O_DIRECTORY 并且路径名不是目录。

### ENOTDIR
(openat()) pathname is a relative pathname and dirfd is a file descriptor referring to a file other than a directory.

(openat()) pathname 是一个相对路径名，而 dirfd 是一个文件描述符，它引用一个目录以外的文件。

### ENXIO

O_NONBLOCK | O_WRONLY is set, the named file is a FIFO, and no process has the FIFO open for reading.

O_NONBLOCK | 设置了 O_WRONLY，命名文件是 FIFO，没有进程打开 FIFO 进行读取。

### ENXIO

The file is a device special file and no corresponding device exists.

该文件是设备专用文件，不存在对应的设备。

### ENXIO

The file is a UNIX domain socket.

该文件是一个 UNIX 域套接字。

### EOPNOTSUPP
The filesystem containing pathname does not support O_TMPFILE.

包含路径名的文件系统不支持 O_TMPFILE。

### EOVERFLOW
pathname refers to a regular file that is too large to be opened.  The usual scenario here is that an application compiled on a 32-bit platform without -D_FILE_OFFSET_BITS=64 tried to open a file whose size exceeds (1<<31)-1 bytes; see also O_LARGEFILE above.  This is the error specified by POSIX.1; in kernels before 2.6.24, Linux gave the error EFBIG for this case.

路径名是指一个太大而无法打开的常规文件。 这里的常见情况是在没有 -D_FILE_OFFSET_BITS=64 的 32 位平台上编译的应用程序试图打开一个大小超过 (1<<31)-1 字节的文件； 另请参见上面的 O_LARGEFILE。 这是 POSIX.1 指定的错误； 在 2.6.24 之前的内核中，Linux 针对这种情况给出了错误 EFBIG。

### EPERM

The O_NOATIME flag was specified, but the effective user ID of the caller did not match the owner of the file and the caller was not privileged.

指定了 O_NOATIME 标志，但调用者的有效用户 ID 与文件的所有者不匹配，并且调用者没有特权。

### EPERM

The operation was prevented by a file seal; see fcntl(2).

该操作被一个文件密封所阻止；见fcntl(2)。

### EROFS

pathname refers to a file on a read-only filesystem and write access was requested.

路径名指的是只读文件系统上的一个文件，并且要求有写入权限。

### ETXTBSY
pathname refers to an executable image which is currently being executed and write access was requested.

路径名指的是一个正在执行的可执行映像，并且被要求进行写入访问。

### ETXTBSY
pathname refers to a file that is currently in use as a swap file, and the O_TRUNC flag was specified.

路径名是指当前用作交换文件的文件，并且指定了 O_TRUNC 标志。

### ETXTBSY
pathname refers to a file that is currently being read by the kernel (e.g., for module/firmware loading), and write access was requested.

路径名是指当前正在被内核读取的文件（例如，用于模块/固件加载），并且请求了写访问权。

### EWOULDBLOCK
The O_NONBLOCK flag was specified, and an incompatible lease was held on the file (see fcntl(2)).  

指定了 O_NONBLOCK 标志，并且文件上持有不兼容的租约（请参阅 fcntl(2)）。

## VERSIONS

openat() was added to Linux in kernel 2.6.16; library support was added to glibc in version 2.4.

在内核 2.6.16 中将 openat() 添加到 Linux； 库支持在 2.4 版中添加到 glibc。

## CONFORMING TO

open(), creat() SVr4, 4.3BSD, POSIX.1-2001, POSIX.1-2008.

openat(): POSIX.1-2008.

openat2(2) is Linux-specific.

The O_DIRECT, O_NOATIME, O_PATH, and O_TMPFILE flags are Linux-specific.  One must define _GNU_SOURCE to obtain their definitions.

O_DIRECT、O_NOATIME、O_PATH 和 O_TMPFILE 标志是特定于 Linux 的。 必须定义 _GNU_SOURCE 才能获得它们的定义。

The O_CLOEXEC, O_DIRECTORY, and O_NOFOLLOW flags are not specified in POSIX.1-2001, but are specified in POSIX.1-2008. Since glibc 2.12, one can obtain their definitions by defining either _POSIX_C_SOURCE with a value greater than or equal to 200809L or _XOPEN_SOURCE with a value greater than or equal to 700.  In glibc 2.11 and earlier, one obtains the definitions by defining _GNU_SOURCE.

O_CLOEXEC、O_DIRECTORY 和 O_NOFOLLOW 标志未在 POSIX.1-2001 中指定，但在 POSIX.1-2008 中指定。 从 glibc 2.12 开始，可以通过定义 _POSIX_C_SOURCE 的值大于或等于 200809L 或 _XOPEN_SOURCE 的值大于或等于 700 来获得它们的定义。在 glibc 2.11 和更早版本中，通过定义 _GNU_SOURCE 来获得定义。

As noted in feature_test_macros(7), feature test macros such as _POSIX_C_SOURCE, _XOPEN_SOURCE, and _GNU_SOURCE must be defined before including any header files.

如 feature_test_macros(7) 中所述，必须在包含任何头文件之前定义功能测试宏，例如 `_POSIX_C_SOURCE`、`_XOPEN_SOURCE` 和 `_GNU_SOURCE`。

## NOTES

```
       Under Linux, the O_NONBLOCK flag is sometimes used in cases where
       one wants to open but does not necessarily have the intention to
       read or write.  For example, this may be used to open a device in
       order to get a file descriptor for use with ioctl(2).

       The (undefined) effect of O_RDONLY | O_TRUNC varies among
       implementations.  On many systems the file is actually truncated.

       Note that open() can open device special files, but creat()
       cannot create them; use mknod(2) instead.

       If the file is newly created, its st_atime, st_ctime, st_mtime
       fields (respectively, time of last access, time of last status
       change, and time of last modification; see stat(2)) are set to
       the current time, and so are the st_ctime and st_mtime fields of
       the parent directory.  Otherwise, if the file is modified because
       of the O_TRUNC flag, its st_ctime and st_mtime fields are set to
       the current time.

       The files in the /proc/[pid]/fd directory show the open file
       descriptors of the process with the PID pid.  The files in the
       /proc/[pid]/fdinfo directory show even more information about
       these file descriptors.  See proc(5) for further details of both
       of these directories.

       The Linux header file <asm/fcntl.h> doesn't define O_ASYNC; the
       (BSD-derived) FASYNC synonym is defined instead.

   Open file descriptions
       The term open file description is the one used by POSIX to refer
       to the entries in the system-wide table of open files.  In other
       contexts, this object is variously also called an "open file
       object", a "file handle", an "open file table entry", or—in
       kernel-developer parlance—a struct file.

       When a file descriptor is duplicated (using dup(2) or similar),
       the duplicate refers to the same open file description as the
       original file descriptor, and the two file descriptors
       consequently share the file offset and file status flags.  Such
       sharing can also occur between processes: a child process created
       via fork(2) inherits duplicates of its parent's file descriptors,
       and those duplicates refer to the same open file descriptions.

       Each open() of a file creates a new open file description; thus,
       there may be multiple open file descriptions corresponding to a
       file inode.

       On Linux, one can use the kcmp(2) KCMP_FILE operation to test
       whether two file descriptors (in the same process or in two
       different processes) refer to the same open file description.

   Synchronized I/O
       The POSIX.1-2008 "synchronized I/O" option specifies different
       variants of synchronized I/O, and specifies the open() flags
       O_SYNC, O_DSYNC, and O_RSYNC for controlling the behavior.
       Regardless of whether an implementation supports this option, it
       must at least support the use of O_SYNC for regular files.

       Linux implements O_SYNC and O_DSYNC, but not O_RSYNC.  Somewhat
       incorrectly, glibc defines O_RSYNC to have the same value as
       O_SYNC.  (O_RSYNC is defined in the Linux header file
       <asm/fcntl.h> on HP PA-RISC, but it is not used.)

       O_SYNC provides synchronized I/O file integrity completion,
       meaning write operations will flush data and all associated
       metadata to the underlying hardware.  O_DSYNC provides
       synchronized I/O data integrity completion, meaning write
       operations will flush data to the underlying hardware, but will
       only flush metadata updates that are required to allow a
       subsequent read operation to complete successfully.  Data
       integrity completion can reduce the number of disk operations
       that are required for applications that don't need the guarantees
       of file integrity completion.

       To understand the difference between the two types of completion,
       consider two pieces of file metadata: the file last modification
       timestamp (st_mtime) and the file length.  All write operations
       will update the last file modification timestamp, but only writes
       that add data to the end of the file will change the file length.
       The last modification timestamp is not needed to ensure that a
       read completes successfully, but the file length is.  Thus,
       O_DSYNC would only guarantee to flush updates to the file length
       metadata (whereas O_SYNC would also always flush the last
       modification timestamp metadata).

       Before Linux 2.6.33, Linux implemented only the O_SYNC flag for
       open().  However, when that flag was specified, most filesystems
       actually provided the equivalent of synchronized I/O data
       integrity completion (i.e., O_SYNC was actually implemented as
       the equivalent of O_DSYNC).

       Since Linux 2.6.33, proper O_SYNC support is provided.  However,
       to ensure backward binary compatibility, O_DSYNC was defined with
       the same value as the historical O_SYNC, and O_SYNC was defined
       as a new (two-bit) flag value that includes the O_DSYNC flag
       value.  This ensures that applications compiled against new
       headers get at least O_DSYNC semantics on pre-2.6.33 kernels.

   C library/kernel differences
       Since version 2.26, the glibc wrapper function for open() employs
       the openat() system call, rather than the kernel's open() system
       call.  For certain architectures, this is also true in glibc
       versions before 2.26.

   NFS
       There are many infelicities in the protocol underlying NFS,
       affecting amongst others O_SYNC and O_NDELAY.

       On NFS filesystems with UID mapping enabled, open() may return a
       file descriptor but, for example, read(2) requests are denied
       with EACCES.  This is because the client performs open() by
       checking the permissions, but UID mapping is performed by the
       server upon read and write requests.

   FIFOs
       Opening the read or write end of a FIFO blocks until the other
       end is also opened (by another process or thread).  See fifo(7)
       for further details.

   File access mode
       Unlike the other values that can be specified in flags, the
       access mode values O_RDONLY, O_WRONLY, and O_RDWR do not specify
       individual bits.  Rather, they define the low order two bits of
       flags, and are defined respectively as 0, 1, and 2.  In other
       words, the combination O_RDONLY | O_WRONLY is a logical error,
       and certainly does not have the same meaning as O_RDWR.

       Linux reserves the special, nonstandard access mode 3 (binary 11)
       in flags to mean: check for read and write permission on the file
       and return a file descriptor that can't be used for reading or
       writing.  This nonstandard access mode is used by some Linux
       drivers to return a file descriptor that is to be used only for
       device-specific ioctl(2) operations.

   Rationale for openat() and other directory file descriptor APIs
       openat() and the other system calls and library functions that
       take a directory file descriptor argument (i.e., execveat(2),
       faccessat(2), fanotify_mark(2), fchmodat(2), fchownat(2),
       fspick(2), fstatat(2), futimesat(2), linkat(2), mkdirat(2),
       mknodat(2), mount_setattr(2), move_mount(2),
       name_to_handle_at(2), open_tree(2), openat2(2), readlinkat(2),
       renameat(2), renameat2(2), statx(2), symlinkat(2), unlinkat(2),
       utimensat(2), mkfifoat(3), and scandirat(3)) address two problems
       with the older interfaces that preceded them.  Here, the
       explanation is in terms of the openat() call, but the rationale
       is analogous for the other interfaces.

       First, openat() allows an application to avoid race conditions
       that could occur when using open() to open files in directories
       other than the current working directory.  These race conditions
       result from the fact that some component of the directory prefix
       given to open() could be changed in parallel with the call to
       open().  Suppose, for example, that we wish to create the file
       dir1/dir2/xxx.dep if the file dir1/dir2/xxx exists.  The problem
       is that between the existence check and the file-creation step,
       dir1 or dir2 (which might be symbolic links) could be modified to
       point to a different location.  Such races can be avoided by
       opening a file descriptor for the target directory, and then
       specifying that file descriptor as the dirfd argument of (say)
       fstatat(2) and openat().  The use of the dirfd file descriptor
       also has other benefits:

       *  the file descriptor is a stable reference to the directory,
          even if the directory is renamed; and

       *  the open file descriptor prevents the underlying filesystem
          from being dismounted, just as when a process has a current
          working directory on a filesystem.

       Second, openat() allows the implementation of a per-thread
       "current working directory", via file descriptor(s) maintained by
       the application.  (This functionality can also be obtained by
       tricks based on the use of /proc/self/fd/dirfd, but less
       efficiently.)

       The dirfd argument for these APIs can be obtained by using open()
       or openat() to open a directory (with either the O_RDONLY or the
       O_PATH flag).  Alternatively, such a file descriptor can be
       obtained by applying dirfd(3) to a directory stream created using
       opendir(3).

       When these APIs are given a dirfd argument of AT_FDCWD or the
       specified pathname is absolute, then they handle their pathname
       argument in the same way as the corresponding conventional APIs.
       However, in this case, several of the APIs have a flags argument
       that provides access to functionality that is not available with
       the corresponding conventional APIs.

   O_DIRECT
       The O_DIRECT flag may impose alignment restrictions on the length
       and address of user-space buffers and the file offset of I/Os.
       In Linux alignment restrictions vary by filesystem and kernel
       version and might be absent entirely.  However there is currently
       no filesystem-independent interface for an application to
       discover these restrictions for a given file or filesystem.  Some
       filesystems provide their own interfaces for doing so, for
       example the XFS_IOC_DIOINFO operation in xfsctl(3).

       Under Linux 2.4, transfer sizes, the alignment of the user
       buffer, and the file offset must all be multiples of the logical
       block size of the filesystem.  Since Linux 2.6.0, alignment to
       the logical block size of the underlying storage (typically 512
       bytes) suffices.  The logical block size can be determined using
       the ioctl(2) BLKSSZGET operation or from the shell using the
       command:

           blockdev --getss

       O_DIRECT I/Os should never be run concurrently with the fork(2)
       system call, if the memory buffer is a private mapping (i.e., any
       mapping created with the mmap(2) MAP_PRIVATE flag; this includes
       memory allocated on the heap and statically allocated buffers).
       Any such I/Os, whether submitted via an asynchronous I/O
       interface or from another thread in the process, should be
       completed before fork(2) is called.  Failure to do so can result
       in data corruption and undefined behavior in parent and child
       processes.  This restriction does not apply when the memory
       buffer for the O_DIRECT I/Os was created using shmat(2) or
       mmap(2) with the MAP_SHARED flag.  Nor does this restriction
       apply when the memory buffer has been advised as MADV_DONTFORK
       with madvise(2), ensuring that it will not be available to the
       child after fork(2).

       The O_DIRECT flag was introduced in SGI IRIX, where it has
       alignment restrictions similar to those of Linux 2.4.  IRIX has
       also a fcntl(2) call to query appropriate alignments, and sizes.
       FreeBSD 4.x introduced a flag of the same name, but without
       alignment restrictions.

       O_DIRECT support was added under Linux in kernel version 2.4.10.
       Older Linux kernels simply ignore this flag.  Some filesystems
       may not implement the flag, in which case open() fails with the
       error EINVAL if it is used.

       Applications should avoid mixing O_DIRECT and normal I/O to the
       same file, and especially to overlapping byte regions in the same
       file.  Even when the filesystem correctly handles the coherency
       issues in this situation, overall I/O throughput is likely to be
       slower than using either mode alone.  Likewise, applications
       should avoid mixing mmap(2) of files with direct I/O to the same
       files.

       The behavior of O_DIRECT with NFS will differ from local
       filesystems.  Older kernels, or kernels configured in certain
       ways, may not support this combination.  The NFS protocol does
       not support passing the flag to the server, so O_DIRECT I/O will
       bypass the page cache only on the client; the server may still
       cache the I/O.  The client asks the server to make the I/O
       synchronous to preserve the synchronous semantics of O_DIRECT.
       Some servers will perform poorly under these circumstances,
       especially if the I/O size is small.  Some servers may also be
       configured to lie to clients about the I/O having reached stable
       storage; this will avoid the performance penalty at some risk to
       data integrity in the event of server power failure.  The Linux
       NFS client places no alignment restrictions on O_DIRECT I/O.

       In summary, O_DIRECT is a potentially powerful tool that should
       be used with caution.  It is recommended that applications treat
       use of O_DIRECT as a performance option which is disabled by
       default.
```

## BUGS

Currently, it is not possible to enable signal-driven I/O by specifying O_ASYNC when calling open(); use fcntl(2) to enable this flag.

目前，在调用 open() 时无法通过指定 O_ASYNC 来启用信号驱动 I/O； 使用 fcntl(2) 启用此标志。

One must check for two different error codes, EISDIR and ENOENT, when trying to determine whether the kernel supports O_TMPFILE functionality.

在尝试确定内核是否支持 O_TMPFILE 功能时，必须检查两种不同的错误代码，EISDIR 和 ENOENT。

When both O_CREAT and O_DIRECTORY are specified in flags and the file specified by pathname does not exist, open() will create a regular file (i.e., O_DIRECTORY is ignored).

当标志中同时指定了 O_CREAT 和 O_DIRECTORY 并且路径名指定的文件不存在时，open() 将创建一个常规文件（即忽略 O_DIRECTORY）。