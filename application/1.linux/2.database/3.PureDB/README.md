# PureDB 2

https://github.com/jedisct1/PureDB

## Blurb

PureDB is a portable and tiny set of libraries for creating and reading constant databases.

PureDB 是一组可移植的小型库，用于创建和读取常量数据库。

It manages data files that contains text or binary key/data pairs of arbitrary sizes. Lookups are very fast (normally only one disk access to match a hash value), overhead is low (a database is 1028 bytes plus only 16 extra bytes per record), multiple concurrent read access are supported, and databases can be up to 4 Gb long, and they are portable accross architectures.

它管理包含任意大小的文本或二进制密钥/数据对的数据文件。查找速度非常快（通常只有一个磁盘访问来匹配哈希值），开销低（一个数据库是 1028 字节加上每条记录只有 16 个额外字节），支持多个并发读取访问，数据库最长可达 4 Gb，而且它们可以跨架构移植。

This is a standalone distribution of Pure-FTPd's built-in database.

这是 Pure-FTPd 内置数据库的独立发行版。

## Compilation

Compiling PureDB is a simple matter of:

编译 PureDB 很简单：

```
./configure
make install
```

Static libraries, shared libraries and links are installed in `/usr/local/lib/libpuredb_read*` and `/usr/local/lib/libpuredb_write*`.

静态库、共享库和链接安装在 `/usr/local/lib/libpuredb_read*` 和 `/usr/local/lib/libpuredb_write*` 中。

Header files are installed as `/usr/local/include/puredb_read.h` and `/usr/local/include/puredb_write.h`.

头文件安装为 `/usr/local/include/puredb_read.h` 和 `/usr/local/include/puredb_write.h`。

The library that creates databases is different from the library that reads them, because these different tasks are usually handled by separate applications. However, you can safely link both libraries together.

创建数据库的库与读取它们的库不同，因为这些不同的任务通常由不同的应用程序处理。但是，你可以安全地将这两个库链接在一起。

## Usage

To compile a program with puredb, you have to include the following headers:

要使用 puredb 编译程序，你必须包含以下头文件：

```
#include <puredb_read.h>
```

and/or

```
#include <puredb_write.h>
```

If your application only reads PureDB databases, just include the first header. If it only writes databases, just include the second one. It it does both, include both.

如果你的应用程序只读取 PureDB 数据库，则只需包含第一个标头。如果它只写数据库，只包括第二个。它两者兼而有之，包括两者。

The same thing goes for linker options: you have to link against `libpuredb_read` and/or `libpuredb_write`:

链接器选项也是如此：你必须链接 `libpuredb_read` 和/或 `libpuredb_write`：

```
cc -o myapp1 myapp1.c -lpuredb_read
cc -o myapp2 myapp2.c -lpuredb_write
cc -o myapp3 myapp3.c -lpuredb_read -lpuredb_write
```

## API for creating databases 用于创建数据库的 API

Creating a new database is usually a 4-step operation:

创建新数据库通常需要 4 步操作：

1. Create the database files and initialize the internal structures with `puredbw_open()`.创建数据库文件并使用 puredbw_open() 初始化内部结构。
2. Feed key/data pairs with `puredbw_add()` or `puredbw_add_s()`.使用 puredbw_add() 或 puredbw_add_s() 提供键/数据对。
3. Complete and close the database files with `puredbw_close()`.使用 puredbw_close() 完成并关闭数据库文件。
4. Free the internal structures with `puredbw_free()`.使用 puredbw_free() 释放内部结构。

Here are the functions:

以下是功能：

```
int puredbw_open(PureDBW * const dbw,
                 const char * const file_index,
                 const char * const file_data,
                 const char * const file_final);
```

This function takes a point to an already allocated `PureDBW` structure, and three file names. file_index and file_data are temporary files, needed to create the database. They will be automatically deleted, and the final database will atomically be stored in `file_final`.

这个函数指向一个已经分配的 `PureDBW` 结构和三个文件名。 file_index 和 file_data 是创建数据库所需的临时文件。它们将被自动删除，最终数据库将自动存储在 `file_final` 中。

Return value: `0` if everything is ok, a negative value if something went wrong.

返回值：如果一切正常，则返回 0，如果出现问题，则返回负值。

```
int puredbw_add(PureDBW * const dbw,
                const char * const key, const size_t key_len,
                const char * const content, const size_t content_len);
```

This function stores a new key/data pair in the database. key is a pointer to the key, that is `key_len` long. Same thing for `content` and `content_len`. These buffers can handle binary data, and can have any size up to 4 Gb.

此函数在数据库中存储一个新的键/数据对。 key 是指向键的指针，即 `key_len` 长。 `content` 和 `content_len` 也是一样。这些缓冲区可以处理二进制数据，大小可达4 Gb。

Return value: `0` if everything is ok, a negative value if something went wrong.

返回值：如果一切正常，则返回 0，如果出现问题，则返回负值。

```
int puredbw_add_s(PureDBW * const dbw,
                  const char * const key, const char * const content);
```

This function is a shortcut to `puredbw_add()`, designed to store `\0`-terminated strings. It's equivalent to call `puredbw_add()` with `strlen(key)` and `strlen(content)` as parameters 3 and 5.

这个函数是 `pureddbw_add()` 的一个快捷方式，用于存储以`\0`结尾的字符串。它等价于使用参数 3 和 5 为 `strlen(key)` 和 `strlen(content)` 调用 `pureddbw_add()`。

Return value: `0` if everything is ok, a negative value if something went wrong.

返回值：如果一切正常，则返回 0，如果出现问题，则返回负值。

```
int puredbw_close(PureDBW * const dbw);
```

This function performs a quick sort of the hashed values, writes them to the disk, merges index and data files, rename the result to the final file name and delete the old files. You must call this after having inserted all values in the database.

此函数对散列值进行快速排序，将它们写入磁盘，合并索引和数据文件，将结果重命名为最终文件名并删除旧文件。你必须在数据库中插入所有值后调用它。

Return value: `0` if everything is ok, a negative value if something went wrong.

返回值：如果一切正常，则返回 0，如果出现问题，则返回负值。

```
void puredbw_free(PureDBW * const dbw);
```

This function frees all memory chunks allocated by `puredbw_open()`, `puredbw_add()` and `puredbw_add_s()`. You must call this either after a `puredbw_close()`, or after something went wrong if you decide to abort.

此函数释放由 `puredbw_open()`、`puredbw_add()` 和 `puredbw_add_s()`分配的所有内存块。你必须在 `puredbw_close()` 之后调用它，或者如果您决定中止，则在出现问题之后调用它。

Here's an example, that creates a new database, and inserts three key/data pairs into it.

这是一个示例，它创建一个新数据库，并在其中插入三个键/数据对。

```
#include <stdio.h>
#include <stdlib.h>
#include <puredb_write.h>

int main(void)
{
    PureDBW dbw;

    if (puredbw_open(&dbw, "puredb.index", "puredb.data", "puredb.pdb") != 0) {
        perror("Can't create the database");
    } else if (puredbw_add_s(&dbw, "key", "content") != 0 ||
               puredbw_add_s(&dbw, "key2", "content2") != 0 ||
               puredbw_add_s(&dbw, "key42", "content42") != 0) {
        perror("Error while inserting key/data pairs");
    }
    if (puredbw_close(&dbw) != 0) {
        perror("Error while closing the database");
    }
    puredbw_free(&dbw);

    return 0;
}
```

## API for reading databases 用于读取数据库的 API

Reading the content of a database is usually a 5-step operation:

读取数据库的内容通常需要 5 步操作：

1. Open the database files and initialize the internal structures with `puredb_open()`.打开数据库文件并使用 puredb_open() 初始化内部结构。
2. Perform a lookup for a key with `puredb_find()` or `puredb_find_s()`.使用 puredb_find() 或 puredb_find_s() 执行键查找。
3. If the key is found, read the associated data with `puredb_read()`.如果找到密钥，则使用 puredb_read() 读取相关数据。

[process the data]

[处理数据]

4. Free the data with `puredb_read_free()`.使用 puredb_read_free() 释放数据。

[repeat steps 2, 3 and 4 to read more key/data pairs]

[重复步骤 2、3 和 4 以读取更多密钥/数据对]

5. Close the database and free the internal structures with `puredb_close()`.使用 puredb_close() 关闭数据库并释放内部结构。

Here are the functions:

以下是功能：

```
int puredb_open(PureDB * const db, const char *dbfile);
```

This function opens an existing database, stored in a file named `dbfile`, and initializes a preallocated `PureDB` structure.

此函数打开一个现有数据库，存储在一个名为 dbfile 的文件中，并初始化一个预分配的 PureDB 结构。

Return value: `0` if everything is ok, a negative value if something went wrong.

返回值：如果一切正常，则返回 0，如果出现问题，则返回负值。

```
int puredb_find(PureDB * const db, const char * const tofind,
                const size_t tofind_len, off_t * const retpos,
                size_t * const retlen);
```

This function looks the database for a key matching `tofind`, whoose length is `tofind_len`. After a successful match, retpos contains the offset to the first byte of the matching data, and retlen is the length of the data.

此函数在数据库中查找与 `tofind` 匹配的键，其长度为 `tofind_len`。匹配成功后，`retpos` 包含匹配数据第一个字节的偏移量，`retlen` 是数据的长度。

Return value: `0` if the key was found. `-1` if the key was not found. `-2` if the database is corrupted. `-3` if a system error occured.

返回值：如果找到密钥，则返回 0。 -1 如果没有找到密钥。 -2 如果数据库损坏。 -3 如果发生系统错误。

```
int puredb_find_s(PureDB * const db, const char * const tofind,
                  off_t * const retpos, size_t * const retlen);
```

This function is a shortcut to `puredb_find()` for text keys, which computes `strlen(tofind)` as a key length.

此函数是用于文本键的 puredb_find() 的快捷方式，它将 strlen(tofind) 计算为键长度。

Return value: `0` if the key was found. `-1` if the key was not found. `-2` if the database is corrupted. `-3` if a system error occured.

返回值：如果找到密钥，则返回 0。 -1 如果没有找到密钥。 -2 如果数据库损坏。 -3 如果发生系统错误。

```
void *puredb_read(PureDB * const db, const off_t offset, const size_t len);
```

This function reads len bytes in the database file, starting at `offset`. A large enough buffer is allocated, filled and returned. It is guaranteed to be terminated by an extra `\0`, so it's safe to process C-strings returned by that function.

此函数从偏移量开始读取数据库文件中的 len 个字节。分配、填充和返回足够大的缓冲区。它保证由一个额外的 \0 终止，因此处理该函数返回的 C 字符串是安全的。

Return value: the address of a buffer with the data, or `NULL` if something went wrong (no memory, corrupted file, no permission, etc) .

返回值：包含数据的缓冲区的地址，如果出现问题（没有内存、损坏的文件、没有权限等），则返回 NULL。

```
void puredb_read_free(void *data);
```

Frees a buffer allocated by `puredb_read()`.

释放由 puredb_read() 分配的缓冲区。

```
int puredb_getfd(PureDB * const db);
```

Returns the file descriptor opened for the database, just in case you want to read the data by yourself. It can be interesting if the data is too large to be stored in memory.

返回为数据库打开的文件描述符，以防你想自己读取数据。如果数据太大而无法存储在内存中，这可能会很有趣。

Return value: a file descriptor. or `-1` if none was allocated (error).

返回值：一个文件描述符。或 -1 如果没有分配（错误）。

```
off_t puredb_getsize(PureDB * const db);
```

This function returns the size of the file handling the database, in bytes.

此函数返回处理数据库的文件的大小，以字节为单位。

Return value: the size of the file.

返回值：文件的大小。

```
int puredb_close(PureDB * const db);
```

This function closes the database and frees all related internal structures. Don't forget to call this even if something went wrong, and you decide to abort.

此函数关闭数据库并释放所有相关的内部结构。即使出现问题，也不要忘记调用它，并且你决定中止。

Here's an example, that reads a previously created database.

这是一个示例，它读取先前创建的数据库。

```
#include <stdio.h>
#include <stdlib.h>
#include <puredb_read.h>

int main(void)
{
    PureDB db;
    off_t retpos;
    size_t retlen;
    char *data;

    if (puredb_open(&db, "puredb.pdb") != 0) {
        perror("Can't open the database");
    } else if (puredb_find_s(&db, "key42", &retpos, &retlen) != 0) {
        fprintf(stderr, "The key wasn't found\n");
    } else if ((data = puredb_read(&db, retpos, retlen)) != NULL) {
        printf("The maching data are: [%s]\n", data);
        puredb_read_free(data);
    }
    if (puredb_close(&db) != 0) {
        perror("The database couldn't be properly closed");
    }
    return 0;
}
```
