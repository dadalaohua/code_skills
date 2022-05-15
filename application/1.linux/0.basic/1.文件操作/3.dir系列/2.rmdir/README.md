# rmdir

https://man7.org/linux/man-pages/man2/rmdir.2.html

## NAME

rmdir - delete a directory

rmdir - 删除目录

## SYNOPSIS

```c
#include <unistd.h>

int rmdir(const char *pathname);
```

## DESCRIPTION

rmdir() deletes a directory, which must be empty.

rmdir()删除一个目录，该目录必须为空。

## RETURN VALUE

On success, zero is returned.  On error, -1 is returned, and  errno is set to indicate the error.

成功时，返回零。 出错时返回 -1，并设置 errno 以指示错误。

## ERRORS

### EACCES 

Write access to the directory containing pathname was not allowed, or one of the directories in the path prefix of pathname did not allow search permission.  (See also path_resolution(7).)

不允许对包含路径名的目录进行写访问，或者路径名的路径前缀中的目录之一不允许搜索权限。 （另见 path_resolution(7)。）

### EBUSY

pathname is currently in use by the system or some process that prevents its removal.  On Linux, this means pathname is currently used as a mount point or is the root directory of the calling process.

路径名当前正在被系统或某个阻止其删除的进程使用。 在 Linux 上，这意味着路径名当前用作挂载点或者是调用进程的根目录。

### EFAULT

pathname points outside your accessible address space.

路径名指向您可访问的地址空间之外。

### EINVAL

pathname has .  as last component.

路径名的最后一个组成部分是.

### ELOOP

Too many symbolic links were encountered in resolving pathname.

解析路径名时遇到太多符号链接。

### ENAMETOOLONG
pathname was too long.

路径名太长。

### ENOENT

A directory component in pathname does not exist or is a dangling symbolic link.

路径名中的目录组件不存在或者是悬空符号链接。

### ENOMEM

Insufficient kernel memory was available.

可用的内核内存不足。

### ENOTDIR
pathname, or a component used as a directory in pathname, is not, in fact, a directory.

路径名，或路径名中用作目录的组件，实际上不是目录。

### ENOTEMPTY
pathname contains entries other than . and .. ; or, pathname has ..  as its final component.  POSIX.1 also allows EEXIST for this condition.

pathname包含除.和.以外的条目；或者，pathname的最后组成部分是.。 POSIX.1也允许在此条件下使用EEXIST。

### EPERM

The directory containing pathname has the sticky bit(S_ISVTX) set and the process's effective user ID is neither the user ID of the file to be deleted nor that of the directory containing it, and the process is not privileged (Linux: does not have the CAP_FOWNER  capability).

包含路径名的目录设置了粘性位（S_ISVTX），进程的有效用户ID既不是要删除的文件的用户ID，也不是包含它的目录的用户ID，并且该进程没有特权（Linux：没有 CAP_FOWNER 能力）。

### EPERM

The filesystem containing pathname does not support the removal of directories.

包含路径名的文件系统不支持删除目录。

### EROFS

pathname refers to a directory on a read-only filesystem.

路径名是指只读文件系统上的目录。

## CONFORMING TO

POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.

## BUGS

Infelicities in the protocol underlying NFS can cause the unexpected disappearance of directories which are still being used.

NFS 底层协议中的缺陷可能导致仍在使用的目录意外消失。