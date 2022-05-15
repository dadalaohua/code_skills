# mkdir

https://man7.org/linux/man-pages/man2/mkdir.2.html

## NAME

mkdir, mkdirat - create a directory

mkdir, mkdirat - 创建一个目录

## SYNOPSIS

```
       #include <sys/stat.h>

       int mkdir(const char *pathname, mode_t mode);

       #include <fcntl.h>           /* Definition of AT_* constants */
       #include <sys/stat.h>

       int mkdirat(int dirfd, const char *pathname, mode_t mode);

   Feature Test Macro Requirements for glibc (see
   feature_test_macros(7)):

       mkdirat():
           Since glibc 2.10:
               _POSIX_C_SOURCE >= 200809L
           Before glibc 2.10:
               _ATFILE_SOURCE
```

## DESCRIPTION

### mkdir()

mkdir() attempts to create a directory named pathname.

mkdir() 尝试创建一个名为 pathname 的目录。

The argument mode specifies the mode for the new directory (see [inode(7)](https://man7.org/linux/man-pages/man7/inode.7.html)).  It is modified by the process's umask in the usual way: in the absence of a default ACL, the mode of the created directory is (mode & ~umask & 0777).  Whether other mode bits are honored for the created directory depends on the operating system.  For Linux, see NOTES below.

参数 mode 指定新目录的模式（参见 [inode(7)](https://man7.org/linux/man-pages/man7/inode.7.html)）。 它由进程的umask以通常的方式修改：在没有默认ACL的情况下，创建的目录的模式是(mode & ~umask & 0777)。 创建的目录是否支持其他模式位取决于操作系统。 对于 Linux，请参阅下面的注释。

The newly created directory will be owned by the effective user ID of the process.  If the directory containing the file has the set-group-ID bit set, or if the filesystem is mounted with BSD group semantics (mount -o bsdgroups or, synonymously mount -o grpid), the new directory will inherit the group ownership from its parent; otherwise it will be owned by the effective group ID of the process.

新创建的目录将归进程的有效用户 ID 所有。 如果包含该文件的目录设置了 set-group-ID 位，或者如果文件系统使用 BSD 组语义（mount -o bsdgroups 或同义的 mount -o grpid）挂载，则新目录将从其继承组所有权 父母； 否则它将归进程的有效组 ID 所有。

If the parent directory has the set-group-ID bit set, then so will the newly created directory.

如果父目录设置了 set-group-ID 位，那么新创建的目录也会如此。



### mkdirat()

The mkdirat() system call operates in exactly the same way as mkdir(), except for the differences described here.

mkdirat() 系统调用的运行方式与 mkdir() 完全相同，除了此处描述的不同之处。

If the pathname given in pathname is relative, then it is interpreted relative to the directory referred to by the file descriptor dirfd (rather than relative to the current working directory of the calling process, as is done by mkdir() for a  relative pathname).

如果 pathname 中给出的路径名是相对的，那么它被解释为相对于文件描述符 dirfd 引用的目录（而不是相对于调用进程的当前工作目录，如 mkdir() 对相对路径名所做的那样）.

If pathname is relative and dirfd is the special value AT_FDCWD, then pathname is interpreted relative to the current working directory of the calling process (like mkdir()).

如果路径名是相对的并且 dirfd 是特殊值 AT_FDCWD，则路径名被解释为相对于调用进程的当前工作目录（如 mkdir()）。

If pathname is absolute, then dirfd is ignored.

如果路径名是绝对的，则忽略 dirfd。

See openat(2) for an explanation of the need for mkdirat().

有关需要 mkdirat() 的说明，请参见 openat(2)。

## RETURN VALUE

mkdir() and mkdirat() return zero on success.  On error, -1 is returned and [errno](https://man7.org/linux/man-pages/man3/errno.3.html) is set to indicate the error.

mkdir() 和 mkdirat() 成功时返回零。 出错时，返回 -1 并设置 errno 以指示错误。

## ERRORS

### EACCES 

The parent directory does not allow write permission to the process, or one of the directories in pathname did not allow search permission.  (See also path_resolution(7).)

父目录不允许进程写入权限，或者路径名中的目录之一不允许搜索权限。 （另见 path_resolution(7)。）

### EBADF

(mkdirat()) pathname is relative but dirfd is neither AT_FDCWD nor a valid file descriptor.

(mkdirat()) 路径名是相对的，但 dirfd 既不是 AT_FDCWD 也不是有效的文件描述符。

### EDQUOT

The user's quota of disk blocks or inodes on the filesystem has been exhausted.

文件系统上用户的磁盘块或 inode 配额已用完。

### EEXIST

pathname already exists (not necessarily as a directory). This includes the case where pathname is a symbolic link, dangling or not.

路径名已经存在（不一定是目录）。 这包括路径名是符号链接的情况，无论是否悬空。

### EFAULT

pathname points outside your accessible address space.

路径名指向你可访问的地址空间之外。

### EINVAL

The final component ("basename") of the new directory's pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem).

新目录路径名的最后一个组成部分（“basename”）无效（例如，它包含底层文件系统不允许的字符）。

### ELOOP

Too many symbolic links were encountered in resolving pathname.

解析路径名时遇到太多符号链接。

### EMLINK

The number of links to the parent directory would exceed LINK_MAX.

到父目录的链接数将超过 LINK_MAX。

### ENAMETOOLONG
pathname was too long.

路径名太长。

### ENOENT 

A directory component in pathname does not exist or is a dangling symbolic link.

路径名中的目录组件不存在或者是悬空符号链接。

### ENOMEM

Insufficient kernel memory was available.

可用的内核内存不足。

### ENOSPC

The device containing pathname has no room for the new directory.

包含路径名的设备没有新目录的空间。

### ENOSPC

The new directory cannot be created because the user's disk quota is exhausted.

无法创建新目录，因为用户的磁盘配额已用完。

### ENOTDIR
A component used as a directory in pathname is not, in fact, a directory.

在路径名中用作目录的组件实际上不是目录。

### ENOTDIR
(mkdirat()) pathname is relative and dirfd is a file descriptor referring to a file other than a directory.

(mkdirat()) 路径名是相对的，而 dirfd 是一个文件描述符，它指的是目录以外的文件。

### EPERM

The filesystem containing pathname does not support the creation of directories.

包含路径名的文件系统不支持创建目录。

### EROFS

pathname refers to a file on a read-only filesystem.    

路径名是指只读文件系统上的文件。

## VERSIONS

mkdirat() was added to Linux in kernel 2.6.16; library support was added to glibc in version 2.4.

mkdirat() 在内核 2.6.16 中被添加到 Linux； 库支持在 2.4 版中添加到 glibc。

## CONFORMING TO

mkdir(): SVr4, BSD, POSIX.1-2001, POSIX.1-2008.

mkdirat(): POSIX.1-2008.

## NOTES

Under Linux, apart from the permission bits, the S_ISVTX mode bit is also honored.

在 Linux 下，除了权限位外，还支持 S_ISVTX 模式位。

There are many infelicities in the protocol underlying NFS.  Some of these affect mkdir().

NFS 底层的协议有很多不足之处。 其中一些会影响 mkdir()。

### Glibc notes

On older kernels where mkdirat() is unavailable, the glibc wrapper function falls back to the use of mkdir().  When pathname is a relative pathname, glibc constructs a pathname based on the symbolic link in /proc/self/fd that corresponds to the dirfd argument.

在 mkdirat() 不可用的旧内核上，glibc 包装函数回退到使用 mkdir()。 当 pathname 是相对路径名时，glibc 基于 /proc/self/fd 中与 dirfd 参数对应的符号链接构造一个路径名。

