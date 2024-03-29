                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

## A simple tar implementation 一个简单的 tar 实现

https://github.com/calccrypto/tar

测试例程使用

查看说明

./test_code help

创建tar文件

./test_code c test.tar testfile1.md testfile2.md

追加文件到tar文件中

./test_code a test.tar testfile3.md

删除tar中的文件

./test_code r test.tar testfile3.md

打印tar文件列表

./test_code t test.tar

解包tar文件

./test_code x test.tar

将tar文件与工作目录进行比较

./test_code d test.tar

更新有更新修改时间的条目

./test_code u test.tar testfile1.md

加上v，提供更多信息，例如

./test_code tv test.tar

./test_code xv test.tar

***

This is only a simple implementation of the tar file format. It can tar files and extract them. That is about it. Although there are some other utility functions written, they are a very small subset that are provided by GNU Tar. Everything was written based on Wikipedia and the observed results of GNU Tar.

这只是 tar 文件格式的简单实现。它可以 tar 文件并提取它们。就是这样。尽管还编写了一些其他实用函数，但它们只是 GNU Tar 提供的一个非常小的子集。一切都是根据 Wikipedia 和 GNU Tar 的观察结果编写的。

This only works on Linux (or Linux-like environment, such as cygwin) due to the sheer number of POSIX header files being used. The minimum C standard needed is C99.

由于使用了大量的 POSIX 头文件，这只适用于 Linux（或类似 Linux 的环境，如 cygwin）。所需的最低 C 标准是 C99。

The purpose of this is to be a tar library that can be used inside other programs, so that programs don't have to call or perform the tarring outside of the program (such as with system, exec, or through a script)

这样做的目的是成为一个可以在其他程序内部使用的 tar 库，这样程序就不必在程序外部调用或执行 tarring（例如使用 system、exec 或通过脚本）

To build:

```
make      - creates libtar.a
make exec - makes the commandline interface 'exec'
make test - tests the commandline interface
```

Usage:

The library consists of some core functions for basic funtionality, some utility functions that expand on functionality, and some internal functions that should not be called from outside the function.

该库包含一些用于基本功能的核心函数、一些扩展功能的实用函数以及一些不应从函数外部调用的内部函数。

| Core Functions | Description                                                  |
| -------------- | ------------------------------------------------------------ |
| tar_read       | Read from a tar file. Expects address to a null pointer. 从 tar 文件中读取。预期地址为空指针。 |
| tar_write      | Write to a tar file. If a non-empty archive is also provided, the new files will be appended to the older data. 写入 tar 文件。如果还提供了非空存档，则新文件将附加到旧数据中。 |
| tar_free       | Frees up memory used by existing archive instances. 释放现有存档实例使用的内存。 |

------

| Utility Functions | Description                                                  |
| ----------------- | ------------------------------------------------------------ |
| tar_ls            | Prints the contents of an archive. Verbosity level changes what is printed. 打印存档的内容。详细程度会改变打印的内容。 |
| tar_extract       | Extracts the contents of an archive. A filter list can be provided to only extract certain files. 提取档案的内容。可以提供过滤器列表以仅提取某些文件。 |
| tar_update        | Scans through the current working directory and appends any files that are updates of archive entries. 扫描当前工作目录并附加任何作为存档条目更新的文件。 |
| tar_remove        | Given a list of entries, removes those entries from the archive. 给定条目列表，从存档中删除这些条目。 |
| tar_diff          | Checks for differences between entries in the archive and the current working directory. 检查存档中的条目与当前工作目录之间的差异。 |

Many of these functions are just wrappers around internal functions. All functions that involve changing the data in a `struct tar_t *` will take in the address of the archive (`struct tar_t **`).

其中许多函数只是内部函数的包装。所有涉及更改 `struct tar_t *` 中数据的函数都将采用存档的地址（`struct tar_t **`）。

If any function that modifies archive variables errors, it is most likely that the data held in the archive variable is no longer valid.

如果修改存档变量的任何函数出错，则很可能存档变量中保存的数据不再有效。

The commandline interface only has a handful of options, each of which runs one or more of the public functions. Type `help` into the commandline interface to see its usage.

命令行界面只有几个选项，每个选项都运行一个或多个公共功能。在命令行界面中输入帮助以查看其用法。