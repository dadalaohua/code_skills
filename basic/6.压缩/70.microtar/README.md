# microtar

https://github.com/rxi/microtar

A lightweight tar library written in ANSI C

用 ANSI C 编写的轻量级 tar 库

## Basic Usage

The library consists of `microtar.c` and `microtar.h`. These two files can be dropped into an existing project and compiled along with it.

该库由 microtar.c 和 microtar.h 组成。这两个文件可以拖放到现有项目中并与它一起编译。

#### Reading

```
mtar_t tar;
mtar_header_t h;
char *p;

/* Open archive for reading */
mtar_open(&tar, "test.tar", "r");

/* Print all file names and sizes */
while ( (mtar_read_header(&tar, &h)) != MTAR_ENULLRECORD ) {
  printf("%s (%d bytes)\n", h.name, h.size);
  mtar_next(&tar);
}

/* Load and print contents of file "test.txt" */
mtar_find(&tar, "test.txt", &h);
p = calloc(1, h.size + 1);
mtar_read_data(&tar, p, h.size);
printf("%s", p);
free(p);

/* Close archive */
mtar_close(&tar);
```

#### Writing

```
mtar_t tar;
const char *str1 = "Hello world";
const char *str2 = "Goodbye world";

/* Open archive for writing */
mtar_open(&tar, "test.tar", "w");

/* Write strings to files `test1.txt` and `test2.txt` */
mtar_write_file_header(&tar, "test1.txt", strlen(str1));
mtar_write_data(&tar, str1, strlen(str1));
mtar_write_file_header(&tar, "test2.txt", strlen(str2));
mtar_write_data(&tar, str2, strlen(str2));

/* Finalize -- this needs to be the last thing done before closing */
mtar_finalize(&tar);

/* Close archive */
mtar_close(&tar);
```

## Error handling

All functions which return an `int` will return `MTAR_ESUCCESS` if the operation is successful. If an error occurs an error value less-than-zero will be returned; this value can be passed to the function `mtar_strerror()` to get its corresponding error string.

如果操作成功，所有返回 `int` 的函数都将返回 `MTAR_ESUCCESS`。如果发生错误，将返回小于零的错误值；可以将此值传递给函数 `mtar_strerror()` 以获取其对应的错误字符串。

## Wrapping a stream

If you want to read or write from something other than a file, the `mtar_t` struct can be manually initialized with your own callback functions and a `stream` pointer.

如果你想从文件以外的内容读取或写入，可以使用你自己的回调函数和`stream`指针手动初始化 `mtar_t` 结构。

All callback functions are passed a pointer to the `mtar_t` struct as their first argument. They should return `MTAR_ESUCCESS` if the operation succeeds without an error, or an integer below zero if an error occurs.

所有回调函数都传递一个指向 `mtar_t` 结构的指针作为它们的第一个参数。如果操作成功且没有错误，它们应该返回 `MTAR_ESUCCESS`，如果发生错误，它们应该返回小于零的整数。

After the `stream` field has been set, all required callbacks have been set and all unused fields have been zeroset the `mtar_t` struct can be safely used with the microtar functions. `mtar_open` *should not* be called if the `mtar_t` struct was initialized manually.

设置`stream`字段后，已设置所有必需的回调并且已将所有未使用的字段置零，`mtar_t` 结构可以安全地与 microtar 函数一起使用。如果 `mtar_t` 结构是手动初始化的，则不应调用 `mtar_open`。

#### Reading

The following callbacks should be set for reading an archive from a stream:

应设置以下回调以从流中读取存档：

| Name    | Arguments                                | Description                               |
| ------- | ---------------------------------------- | ----------------------------------------- |
| `read`  | `mtar_t *tar, void *data, unsigned size` | Read data from the stream 从流中读取数据  |
| `seek`  | `mtar_t *tar, unsigned pos`              | Set the position indicator 设置位置指示器 |
| `close` | `mtar_t *tar`                            | Close the stream 关闭流                   |

#### Writing

The following callbacks should be set for writing an archive to a stream:

应设置以下回调以将存档写入流：

| Name    | Arguments                                      | Description                           |
| ------- | ---------------------------------------------- | ------------------------------------- |
| `write` | `mtar_t *tar, const void *data, unsigned size` | Write data to the stream 将数据写入流 |
