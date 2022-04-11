# tpl User Guide

**Troy D. Hanson**
`<tdh@tkhanson.net>`
version 1.5, February 2010

To download tpl, follow this link back to the [GitHub project page](https://github.com/troydhanson/tpl).

要下载 tpl，请点击此链接返回 GitHub 项目页面。

## Overview 概述

### Serialization in C

Tpl is a library for serializing C data. The data is stored in its natural binary form. The API is small and tries to stay "out of the way". Tpl can serialize many C data types, including structures.

Tpl 是一个用于序列化 C 数据的库。数据以自然的二进制形式存储。 API 很少，并试图保持“不碍事”。 Tpl 可以序列化许多 C 数据类型，包括结构体。

### Uses for tpl

Tpl makes a convenient file format. For example, suppose a program needs to store a list of user names and ids. This can be expressed using the format string `A(si)`. If the program needs two such lists (say, one for regular users and one for administrators) this could be expressed as `A(si)A(si)`. It is easy to read and write this kind of structured data using tpl.

Tpl 制作了一种方便的文件格式。例如，假设一个程序需要存储用户名和 id 的列表。这可以使用格式字符串 `A(si)` 来表示。如果程序需要两个这样的列表（例如，一个用于普通用户，一个用于管理员），则可以表示为 `A(si)A(si)`。使用 tpl 很容易读写这种结构化数据。

Tpl can also be used as an IPC message format. It handles byte order issues and deframing individual messages off of a stream automatically.

Tpl 也可以用作 IPC 消息格式。它处理字节顺序问题，并自动从流中解构单个消息。

### Expressing type 表达类型

The "data type" of a tpl is explicitly stated as a format string. There is never any ambiguity about the type of data stored in a tpl. Some examples:

tpl 的“数据类型”显式地声明为一个格式字符串。在tpl中存储的数据类型从来不会有任何歧义。一些例子:

- `A(is)` is a variable-length array of integer-string pairs
- `A(is)` 是一个由整型字符串对组成的变长数组
- `A(is)A(is)` are two such arrays, completely independent of one another
- `A(is)A(is)` 是两个这样的数组，彼此完全独立
- `S(ci)` is a structure containing a char and integer
- `S(ci)` 是一个包含字符和整数的结构
- `S(ci)#` is a fixed-length array of the latter structure
- `S(ci)#` 是后一种结构的定长数组
- `A(A(i))` is a nested array, that is, an array of integer arrays
- `A(A(i))` 是嵌套数组，即整数数组的数组

### The tpl image

A tpl image is the serialized form of a tpl, stored in a memory buffer or file, or written to a file descriptor.

tpl 镜像是 tpl 的序列化形式，存储在内存缓冲区或文件中，或写入文件描述符。

#### What’s in a tpl image? tpl 镜像中有什么？

There is no need to understand the internal structure of the tpl image. But for the curious, the image is a strictly defined binary buffer having two sections, a header and the data. The header encodes the length of the image, its format string, endian order and other flags. The data section contains the packed data.

不需要了解tpl镜像的内部结构。但对于好奇的人来说，镜像是一个严格定义的二进制缓冲区，有两个部分，头文件和数据。标头编码对镜像的长度、格式字符串、字节序和其他标志进行编码。数据部分包含打包数据。

#### No framing needed 不需要框架

A property of the tpl image is that consecutive images can be written to a stream without requiring any delimiter between them. The reader making use of `tpl_gather` (or `tpl_load` in `TPL_FD` mode) will obtain exactly one tpl image at a time. Therefore tpl images can be used as an IPC message format without any higher-level framing protocol.

tpl 镜像的一个属性是可以将连续镜像写入流，而无需在它们之间使用任何分隔符。使用 `tpl_gather`（或 `TPL_FD` 模式下的 `tpl_load`）的读取器一次只能获得一个 tpl 镜像。因此 tpl 镜像可以用作 IPC 消息格式，而无需任何更高级别的帧协议。

#### Data portability 数据可移植性

A tpl image generated on one kind of CPU will generally be portable to other CPU types when tpl is used properly. This may be a surprise considering that tpl is a binary format. But tpl has been carefully designed to make this work. Each [format character](http://troydhanson.github.io/tpl/userguide.html#types) has an associated explicitly-sized type. For integer and floating point types, whose "endian" or byte-order convention varies from one CPU to another, tpl automatically and transparently corrects the endian order (if needed) during the unpacking process. Floating point numbers present their own [special difficulties](http://troydhanson.github.io/tpl/userguide.html#trouble_with_double). *No guarantees are made with regard to floating point portability.* That said, because many modern CPU’s use IEEE 754 floating point representation, data is likely to be portable among them.

### XML and Perl

*Note: The `tplxml` utility and the Perl module are currently unsupported in tpl 1.5.*

注意：tplxml 实用程序和 Perl 模块目前在 tpl 1.5 中不受支持。

#### XML

While a tpl image is a binary entity, you can view any tpl image in XML format using the included `tplxml` utility, located in the `lang/perl` directory.

虽然 tpl 镜像是二进制实体，但你可以使用包含在 `lang/perl`目录中的 `tplxml` 实用程序查看任何 XML 格式的 tpl 镜像。

```
tplxml file.tpl > file.xml
tplxml file.xml > file.tpl
```

The utility is bidirectional, as shown. The file extension is not important; `tplxml` inspects its input to see if it’s tpl or XML. You can also pipe data into it instead of giving it a filename. The `tplxml` utility is slow. Its purpose is two-fold: debugging (manual inspection of the data in a tpl), and interoperability with XML-based programs. The resulting XML is often ten times the size of the original binary tpl image.

如图所示，该实用程序是双向的。文件扩展名并不重要； `tplxml` 检查其输入以查看它是 tpl 还是 XML。你还可以将数据通过管道传输到其中，而不是给它一个文件名。tplxml 实用程序很慢。它的目的有两个：调试（手动检查 tpl 中的数据），以及与基于 XML 的程序的互操作性。生成的 XML 通常是原始二进制 tpl 镜像大小的十倍。

#### Perl

There is a Perl module in `lang/perl/Tpl.pm`. The [Perl API](http://troydhanson.github.io/tpl/perl.html) is convenient for writing Perl scripts that interoperate with C programs, and need to pass structured data back and forth. It is written in pure Perl.

在 `lang/perl/Tpl.pm` 中有一个 Perl 模块。 Perl API 便于编写与 C 程序互操作的 Perl 脚本，并且需要来回传递结构化数据。它是用纯 Perl 编写的。

### Platforms 平台

The tpl software was developed for POSIX systems and has been tested on 32- and 64-bit platforms including:

tpl 软件是为 POSIX 系统开发的，并已在 32 位和 64 位平台上进行了测试，包括：

- Linux
- Solaris
- Mac OS X
- OpenBSD
- Windows using Visual Studio 2008 or 2010, or Cygwin or MinGW

### BSD licensed

This software is made available under the [revised BSD license](http://troydhanson.github.io/tpl/license.html). It is free and open source.

该软件在修订后的 BSD 许可下提供。它是免费和开源的。

### Download 下载

You can clone tpl, or get a zipfile, from the [GitHub project page](https://github.com/troydhanson/tpl).

你可以从 GitHub 项目页面克隆 tpl 或获取 zip 文件。

### Contributing 参与

If you add a new feature or fix something in tpl or in the extras, please make a pull request on Github. For anything other than a trivial change, include a unit test and documentation if you possibly can. (And don’t be discouraged if it takes weeks or even months for me to merge it. Sorry, my life is busy!) Thanks!

### News

The author has a blog for [software updates](http://troydhanson.wordpress.com/) ![(RSS)](http://troydhanson.github.io/tpl/rss.png) . You can also follow @troydhanson on Twitter for updates.

#### Other software

Other open-source software by the author is listed at [http://troydhanson.github.io](http://troydhanson.github.io/)

## Build and install

Tpl has no dependencies on libraries other than the system C library. You can simply copy the tpl source into your project, so you have no dependencies. Alternatively, you can build tpl as a library and link it to your program.

### As source

The simplest way to use tpl is to copy the source files `tpl.h` and `tpl.c` (from the `src/` directory) right into your project, and build them with the rest of your source files. No special compiler flags are required.

### As a library

Alternatively, to build tpl as a library, from the top-level directory, run:

```
./configure
make
make install
```

(Note that, if `configure` is missing, generate it by running `bootstrap`.)

This installs a static library `libtpl.a` and a shared library (e.g., `libtpl.so`), if your system supports them, in standard places. The installation directory can be customized using `./configure --prefix=/some/directory`. Run `configure --help` for further options.

#### Test suite

You can compile and run the built-in test suite by running:

```
cd tests/
make
```

### On Windows

#### Compile-in

Tpl can be used directly (instead of as a DLL) by compiling the tpl sources right into your program. To do this, add `tpl.c`, `tpl.h`, `win/mman.h` and `win/mmap.c` to your program’s source and header files and add the preprocessor definition `TPL_NOLIB`.

#### DLL

If you like, you can build the DLL yourself using VS2008 or VS2010 (the free Express Edition is sufficient) and perhaps newer versions, though this has not been tested by the author. (As of 2013 we need to restore the solution file to make this easy, that’s currently missing).

#### MinGW/Cygwin

You can build it in the traditional Unix method under Cygwin/MinGW using the "configure; make; make install" approach. If the "configure" script is not present in the repository you cloned, generate it by running "bootstrap".

## API concepts API 概念

To use tpl, you need to know the order in which to call the API functions, and the background concepts of format string, arrays and index numbers.

要使用tpl，需要知道调用API函数的顺序，以及格式字符串、数组和索引号的背景概念。

### Order of functions 函数顺序

Creating a tpl is always the first step, and freeing it is the last step. In between, you either pack and dump the tpl (if you’re serializing data) or you load a tpl image and unpack it (if you’re deserializing data).

创建 tpl 始终是第一步，释放它是最后一步。在这两者之间，你可以打包并转储 tpl（如果你正在序列化数据），或者你加载一个 tpl 镜像并解压它（如果你正在反序列化数据）。

| Step | If you’re serializing…<br>如果你正在序列化... | If you’re deserializing…<br>如果你要反序列化... |
| ---- | --------------------------------------------- | ----------------------------------------------- |
| 1.   | `tpl_map()`                                   | `tpl_map()`                                     |
| 2.   | `tpl_pack()`                                  | `tpl_load()`                                    |
| 3.   | `tpl_dump()`                                  | `tpl_unpack()`                                  |
| 4.   | `tpl_free()`                                  | `tpl_free()`                                    |

### Format string 格式化字符串

When a tpl is created using `tpl_map()`, its data type is expressed as a format string. Each character in the format string has an associated argument of a specific type. For example, this is how a format string and its arguments are passed in to `tpl_map`:

当使用 `tpl_map()` 创建 tpl 时，其数据类型表示为格式字符串。格式字符串中的每个字符都有一个特定类型的关联参数。例如，这是将格式字符串及其参数传递给 `tpl_map` 的方式：

```c
tpl_node *tn;
char c;
int i[10];
tn = tpl_map("ci#", &c, i, 10);  /* ci# is our format string */
```

| Type | Description                                                  | Required argument type<br>所需的参数类型 |
| ---- | ------------------------------------------------------------ | ---------------------------------------- |
| `j`  | 16-bit signed int                                            | int16_t* or equivalent                   |
| `v`  | 16-bit unsigned int                                          | uint16_t* or equivalent                  |
| `i`  | 32-bit signed int                                            | int32_t* or equivalent                   |
| `u`  | 32-bit unsigned int                                          | uint32_t* or equivalent                  |
| `I`  | 64-bit signed int                                            | int64_t* or equivalent                   |
| `U`  | 64-bit unsigned int                                          | uint64_t* or equivalent                  |
| `c`  | character (byte)                                             | char*                                    |
| `s`  | string                                                       | char**                                   |
| `f`  | 64-bit double precision float<br>64位双精度浮点数            | double* (varies by platform)             |
| `#`  | array length; modifies preceding `iujvIUcsf` or `S(...)`<br>数组长度；修改前面的 `iujvIUcsf` 或 `S(...)` | int                                      |
| `B`  | binary buffer (arbitrary-length)<br>二进制缓冲区(任意长度)   | tpl_bin*                                 |
| `S`  | structure (…)<br/>结构体                                     | struct *                                 |
| `$`  | nested structure (…)<br>嵌套结构体                           | none                                     |
| `A`  | array (…)                                                    | none                                     |

#### Explicit sizes

The sizes of data types such as `long` and `double` vary by platform. This must be kept in mind because most tpl format characters require a pointer argument to a specific-sized type, listed above. You can use explicit-sized types such as `int32_t` (defined in `inttypes.h`) in your program if you find this helpful.

数据类型(如`long`和`double`)的大小因平台而异。必须记住这一点，因为大多数tpl格式字符都需要一个指针参数，指向上面列出的特定大小的类型。如果你觉得这很有帮助，可以在程序中使用显式大小的类型，如`int32_t` (在`inttypes.h`中定义)。

##### The trouble with double  double的麻烦

Unfortunately there are no standard explicit-sized floating-point types-- no `float64_t`, for example. If you plan to serialize `double` on your platform using tpl’s `f` format character, first be sure that your `double` is 64 bits. Second, if you plan to deserialize it on a different kind of CPU, be sure that both CPU’s use the same floating-point representation such as IEEE 754.

不幸的是，没有标准的显式大小的浮点类型——例如，没有 float64_t。如果你打算在你的平台上使用 tpl 的 f 格式字符序列化 double，首先要确保你的 double 是 64 位的。其次，如果您打算在不同类型的 CPU 上反序列化它，请确保两个 CPU 使用相同的浮点表示，例如 IEEE 754。

### Arrays 数组

Arrays come in two kinds: **fixed-length** and **variable-length** arrays. Intuitively, they can be thought of like conventional C arrays and linked lists. In general, use fixed-length arrays if possible, and variable-length arrays if necessary. The variable-length arrays support more complex data types, and give or receive the elements to your program one by one.

数组有两种类型:定长数组和变长数组。直观上，它们可以被看作是传统的C数组和链表。通常，尽可能使用固定长度的数组，必要时使用可变长度的数组。变长数组支持更复杂的数据类型，并且将元素一个一个地提供或接收到你的程序。

#### Fixed-length vs. Variable-length arrays

- Notation

  Fixed-length arrays are denoted like `i#` (a simple type followed by one or more `#` signs), but variable-length arrays are denoted like `A(i)`.

  固定长度数组表示为 `i#`（一种简单类型，后跟一个或多个 `#` 符号），但可变长度数组表示为 `A(i)`。

- Element handling

  All the elements of a fixed-length array are packed or unpacked at once. But the elements of a variable-length array are packed or unpacked one by one.

  固定长度数组的所有元素一次打包或解包。但是变长数组的元素会被逐一打包或解包。

- Array length

  The number of elements in a fixed-length array is specified before use-- before any data is packed. But variable-length arrays do not have a fixed element count. They can have any number of elements packed into them. When unpacking a variable-length array, they are unpacked one by one until they are exhausted.

  固定长度数组中的元素数量在使用之前指定 -- 在打包任何数据之前。但是可变长度数组没有固定的元素计数。它们可以包含任意数量的元素。对变长数组进行解包时，会逐一解包，直到用完为止。

- Element types

  Elements of fixed-length arrays can be the integer, byte, double, string types or structures. (This excludes format characters `BA`). Fixed-length arrays can also be multi-dimensional like `i##`. Variable-length arrays can have simple or complex elements-- for example, an array of ints `A(i)`, an array of int/double pairs `A(if)`, or even nested arrays like `A(A(if))`.

  固定长度数组的元素可以是整数、字节、双精度、字符串类型或结构体。 （这不包括格式字符 `BA`）。定长数组也可以是多维的，例如 i##。可变长度数组可以有简单或复杂的元素 -- 例如，int 数组 `A(i)`、int/double 对数组 `A(if)`，甚至像 `A(A(if))` 这样的嵌套数组。

Before explaining all the concepts, it’s illustrative to see how both kinds of arrays are used. Let’s pack the integers 0 through 9 both ways.

在解释所有概念之前，先看看这两种数组是如何使用的。让我们以两种方式打包整数 0 到 9。

**Packing 0-9 as a fixed-length array 将 0-9 打包为定长数组**

```c
#include "tpl.h"
int main() {
    tpl_node *tn;
    int x[] = {0,1,2,3,4,5,6,7,8,9};

    tn = tpl_map("i#", x, 10);
    tpl_pack(tn,0);                         /* pack all 10 elements at once */
    tpl_dump(tn, TPL_FILE, "/tmp/fixed.tpl");
    tpl_free(tn);
}
```

Note that the length of the fixed-length array (10) was passed as an argument to `tpl_map()`. The corresponding unpacking [example](http://troydhanson.github.io/tpl/userguide.html#fixed_unpack) is listed further below. Now let’s see how we would pack 0-9 as a variable-length array:

请注意，固定长度数组 (10) 的长度作为参数传递给 `tpl_map()`。下面进一步列出了相应的解包示例。现在让我们看看如何将 0-9 打包为变长数组：

**Packing 0-9 as a variable-length array 将 0-9 打包为变长数组**

```c
#include "tpl.h"
int main() {
    tpl_node *tn;
    int x;

    tn = tpl_map("A(i)", &x);
    for(x = 0; x < 10; x++) tpl_pack(tn,1);  /* pack one element at a time */
    tpl_dump(tn, TPL_FILE, "/tmp/variable.tpl");
    tpl_free(tn);
}
```

Notice how we called `tpl_pack` in a loop, once for each element 0-9. Again, there is a corresponding unpacking [example](http://troydhanson.github.io/tpl/userguide.html#var_unpack) shown later in the guide. You might also notice that this time, we passed 1 as the final argument to tpl_pack. This is an index number designating which variable-length array we’re packing. In this case, there is only one.

请注意我们如何在循环中调用 `tpl_pack`，每个元素 0-9 调用一次。同样，在本指南后面还有一个相应的解包示例。你可能还注意到，这一次，我们将 1 作为最后一个参数传递给 `tpl_pack`。这是一个索引号，指定我们要打包哪个变长数组。在这种情况下，只有一个。

#### Index numbers 索引号

Index numbers identify a particular variable-length array in the format string. Each `A(...)` in a format string has its own index number. The index numbers are assigned left-to-right starting from 1. Examples:

索引号标识格式字符串中的特定可变长度数组。格式字符串中的每个 `A(...)` 都有自己的索引号。索引号从 1 开始从左到右分配。示例：

```c
A(i)        /* index number 1 */
A(i)A(i)    /* index numbers 1 and 2 */
A(A(i))     /* index numbers 1 and 2 (order is independent of nesting) */
```

##### Special index number 0 特殊索引号0

The special index number 0 designates all the format characters that are not inside an `A(...)`. Examples of what index 0 does (and does not) designate:

特殊索引号 0 表示所有不在` A(...)` 内的格式字符。索引 0 表示（和不表示）的示例：

```c
S(ius)      /* index 0 designates the whole thing */
iA(c)u      /* index 0 designates the i and the u */
c#A(i)S(ci) /* index 0 designates the c# and the S(ci) */
```

An index number is passed to `tpl_pack` and `tpl_unpack` to specify which variable-length array (or non-array, in the case of index number 0) to act upon.

将索引号传递给 `tpl_pack` 和 `tpl_unpack` 以指定要对哪个可变长度数组（或非数组，在索引号 0 的情况下）进行操作。

### Integers 整数

The array examples [above](http://troydhanson.github.io/tpl/userguide.html#fixed_pack) demonstrated how integers could be packed. We’ll show some further examples here of unpacking integers and dealing with multi-dimensional arrays. The same program could be used to demonstrate working with byte, 16-bit shorts, 32-bit or 64-bit signed and unsigned integers with only a change to the data type and the format character.

上面的数组示例演示了如何打包整数。我们将在这里展示一些解包整数和处理多维数组的进一步示例。相同的程序可用于演示如何处理byte, 16-bit shorts, 32-bit 或 64-bit signed 和unsigned integers，只需更改数据类型和格式字符。

Unpacking 0-9 from a fixed-length array 从定长数组中解包0-9

```c
#include "tpl.h"
int main() {
    tpl_node *tn;
    int x[10];

    tn = tpl_map("i#", x, 10);
    tpl_load(tn, TPL_FILE, "/tmp/fixed.tpl");
    tpl_unpack(tn,0);  /* unpack all 10 elements at once */
    tpl_free(tn);
    /* now do something with x[0]...x[9].. (not shown) */
}
```

For completeness, let’s also see how to unpack a variable-length integer array.

为了完整起见，让我们也看看如何解包一个可变长度的整数数组。

Unpacking 0-9 from a variable-length array 从变长数组中解包0-9

```c
#include "tpl.h"
int main() {
    tpl_node *tn;
    int x;

    tn = tpl_map("A(i)", &x);
    tpl_load(tn, TPL_FILE, "/tmp/variable.tpl");
    while (tpl_unpack(tn,1) > 0) printf("%d\n",x); /* unpack one by one */
    tpl_free(tn);
}
```

#### Multi-dimensional arrays 多维数组

A multi-dimensional matrix of integers can be packed and unpacked the same way as any fixed-length array.

整数的多维数组可以像任何固定长度数组一样进行打包和解包。

```c
int xy[XDIM][YDIM];
...
tn = tpl_map("i##", xy, XDIM, YDIM);
tpl_pack(tn, 0);
```

This single call to `tpl_pack` packs the entire matrix.

对 `tpl_pack` 的单次调用会打包整个矩阵。

### Strings 字符串

Tpl can serialize C strings. A different format is used for `char*` vs. `char[ ]` as described below. Let’s look at `char*` first:

Tpl 可以序列化 C 字符串。 `char*` 与 `char[ ]` 使用不同的格式，如下所述。我们先来看 `char*`：

Packing a string

```c
    #include "tpl.h"

    int main() {
        tpl_node *tn;
        char *s = "hello, world!";
        tn = tpl_map("s", &s);
        tpl_pack(tn,0);  /* copies "hello, world!" into the tpl */
        tpl_dump(tn,TPL_FILE,"string.tpl");
        tpl_free(tn);
    }
```

The `char*` must point to a null-terminated string or be a `NULL` pointer.

`char*` 必须指向以 null 结尾的字符串或者是一个 `NULL` 指针。

When deserializing (unpacking) a C string, space for it will be allocated automatically, but you are responsible for freeing it (unless it is `NULL`):

当反序列化（解包）一个 C 字符串时，它的空间将被自动分配，但你需要负责释放它（除非它是 NULL）：

Unpacking a string

```c
    #include "tpl.h"

    int main() {
        tpl_node *tn;
        char *s;
        tn = tpl_map("s", &s);
        tpl_load(tn,TPL_FILE,"string.tpl");
        tpl_unpack(tn,0);   /* allocates space, points s to "hello, world!" */
        printf("unpacked %s\n", s);
        free(s);            /* our responsibility to free s */
        tpl_free(tn);
    }
```

#### char* vs char[ ]

The `s` format character is only for use with `char*` types. In the example above, `s` is a `char*`. If it had been a `char s[14]`, we would use the format characters `c#` to pack or unpack it, as a fixed-length character array. (This unpacks the characters "in-place", instead of into a dynamically allocated buffer). Also, a fixed-length buffer described by `c#` need not be null-terminated.

`s` 格式字符仅用于 `char*` 类型。在上面的示例中，`s` 是一个 `char*`。如果它是一个 `char s[14]`，我们将使用格式字符 `c#` 来打包或解包它，作为一个固定长度的字符数组。（这会将字符“就地”解包，而不是将其解压缩到动态分配的缓冲区中）。此外，`c#` 描述的固定长度缓冲区不需要以空字符null结尾。

#### Arrays of strings

You can use fixed- or variable-length arrays of strings in tpl. An example of packing a fixed-length two-dimensional array of strings is shown here.

你可以在 tpl 中使用固定长度或可变长度的字符串数组。此处显示了打包固定长度的二维字符串数组的示例。

```c
char *labels[2][3] = { {"one", "two", "three"},
                       {"eins", "zwei", "drei" } };
tpl_node *tn;
tn = tpl_map("s##", labels, 2, 3);
tpl_pack(tn,0);
tpl_dump(tn,TPL_FILE,filename);
tpl_free(tn);
```

Later, when unpacking these strings, the programmer must remember to free them one by one, after they are no longer needed.

稍后，在解压这些字符串时，程序员必须记住在不再需要它们之后，将它们一一释放。

```c
char *olabels[2][3];
int i,j;
tn = tpl_map("s##", olabels, 2, 3);
tpl_load(tn,TPL_FILE,filename);
tpl_unpack(tn,0);
tpl_free(tn);
for(i=0;i<2;i++) {
  for(j=0;j<3;j++) {
    printf("%s\n", olabels[i][j]);
    free(olabels[i][j]);
  }
}
```

### Binary buffers 二进制缓冲区

Packing an arbitrary-length binary buffer (tpl format character `B`) makes use of the `tpl_bin` structure. You must declare this structure and populate it with the address and length of the binary buffer to be packed.

打包任意长度的二进制缓冲区（tpl 格式字符 `B`）使用 `tpl_bin` 结构。你必须声明此结构并使用要打包的二进制缓冲区的地址和长度填充它。

Packing a binary buffer 打包二进制缓冲区

```c
    #include "tpl.h"
    #include <sys/time.h>

    int main() {
        tpl_node *tn;
        tpl_bin tb;

        /* we'll use a timeval as our guinea pig */
        struct timeval tv;
        gettimeofday(&tv,NULL);

        tn = tpl_map( "B", &tb );
        tb.sz = sizeof(struct timeval);  /* size of buffer to pack */
        tb.addr = &tv;                   /* address of buffer to pack */
        tpl_pack( tn, 0 );
        tpl_dump(tn, TPL_FILE, "bin.tpl");
        tpl_free(tn);
    }
```

When you unpack a binary buffer, tpl will automatically allocate it, and will populate your `tpl_bin` structure with its address and length. You are responsible for eventually freeing the buffer.

当你解包一个二进制缓冲区时，tpl 会自动分配它，并用它的地址和长度填充你的 `tpl_bin` 结构。你负责最终释放缓冲区。

Unpacking a binary buffer 解包二进制缓冲区

```c
    #include "tpl.h"

    int main() {
        tpl_node *tn;
        tpl_bin tb;

        tn = tpl_map( "B", &tb );
        tpl_load( tn, TPL_FILE, "bin.tpl" );
        tpl_unpack( tn, 0 );
        tpl_free(tn);

        printf("binary buffer of length %d at address %p\n", tb.sz, tb.addr);
        free(tb.addr);  /* our responsibility to free it */
    }
```

### Structures 结构体

You can use tpl to pack and unpack structures, and arrays of structures.

你可以使用 tpl 来打包和解包结构体以及结构体数组。

```c
struct ci {
    char c;
    int i;
};
struct ci s = {'a', 1};
tn = tpl_map("S(ci)", &s);  /* pass structure address */
tpl_pack(tn, 0);
tpl_dump(tn, TPL_FILE, "struct.tpl");
tpl_free(tn);
```

As shown, omit the individual arguments for the format characters inside the parenthesis. The exception is for fixed-length arrays; when `S(...)` contains a `#` character, its length argument is required: `tpl_map("S(f#i)", &s, 10);`

如图所示，省略括号内格式字符的各个参数。固定长度数组除外。当 S(...) 包含 `#` 字符时，其长度参数是必需的：`tpl_map("S(f#i)", &s, 10);`

When using the `S(...)` format, the only characters allowed inside the parentheses are `iujvcsfIU#$()`.

当使用 S(...) 格式时，括号内唯一允许的字符是 `iujvcsfIU#$()`。

#### Structure arrays 结构体数组

Arrays of structures are the same as simple arrays. Fixed- or variable- length arrays are supported.

结构体数组与简单数组相同。支持固定或可变长度数组。

```c
struct ci sa[100], one;
tn = tpl_map("S(ci)#", sa, 100);  /* fixed-length array of 100 structures */
tn = tpl_map("A(S(ci))", &one);   /* variable-length array (one at a time) */
```

The differences between fixed- and variable-length arrays are explained in the [Arrays](http://troydhanson.github.io/tpl/userguide.html#arrays) section.

固定长度数组和可变长度数组之间的区别在数组一节中进行了解释。

#### Nested structures 嵌套结构体

When dealing with nested structures, the outermost structure uses the `S` format character, and the inner nested structures use the `$` format. Only the *outermost* structure’s address is given to `tpl_map`.

在处理嵌套结构体时，最外层的结构使用 `S` 格式字符，最内层的嵌套结构使用 `$` 格式。只有最外层结构的地址被提供给 `tpl_map`。

```c
struct inner_t {
  char a;
}
struct outer_t {
  char b;
  struct inner_t i;
}
tpl_node *tn;
struct outer_t outer = {'b', {'a'}};
tn = tpl_map("S(c$(c))", &outer);
```

Structures can nest to any level. Currently tpl does not support fixed-length array suffixes on inner structures. However the outermost structure can have a length suffix even if it contains some nested structures.

结构体可以嵌套到任何级别。目前 tpl 不支持内部结构体的固定长度数组后缀。然而，最外面的结构体可以有一个长度后缀，即使它包含一些嵌套结构。

### Linked lists 链表

While tpl has no specific data type for a linked list, the technique for packing them is illustrated here. First describe your list element as a format string and then surround it with `A(...)` to describe it as variable-length array. Then, using a temporary variable, iterate over each list element, copying it to the temporary variable and packing it.

虽然 tpl 没有针对链表的特定数据类型，但此处说明了打包它们的技术。首先将你的列表元素描述为格式字符串，然后用 `A(...)` 将其包围以将其描述为可变长度数组。然后，使用临时变量，遍历每个列表元素，将其复制到临时变量并打包。

```c
struct element {
  char c;
  int i;
  struct element *next;
}
struct element *list, *i, tmp;
tpl_node *tn;
/* add some elements to list.. (not shown) */
tn = tpl_map("A(S(ci))", &tmp);
for(i = list; i != NULL; i=i->next) {
  tmp = *i;
  tpl_pack(tn, 1);
}
tpl_dump(tn,TPL_FILE,"list.tpl");
tpl_free(tn);
```

Unpacking is similar. The `for` loop is just replaced with:

拆包类似。 for 循环只是替换为：

```c
while( tpl_unpack(tn,1) > 0) {
  struct element *newelt = malloc(sizeof(struct element));
  *newelt = tmp;
  add_to_list(list, newelt);
}
```

As you can see, tpl does not reinstate the whole list at once-- just one element at a time. You need to link the elements manually. A future release of tpl may support *pointer swizzling* to make this easier.

如你所见，tpl 不会立即恢复整个列表 -- 一次只恢复一个元素。你需要手动链接这些元素。 tpl 的未来版本可能会支持指针混合以使这更容易。

## API

### tpl_map

The only way to create a tpl is to call `tpl_map()`. The first argument is the [format string](http://troydhanson.github.io/tpl/userguide.html#format). This is followed by a list of arguments as required by the particular characters in the format string. E.g,

创建 tpl 的唯一方法是调用 `tpl_map()`。第一个参数是格式字符串。后面是格式字符串中特定字符所需的参数列表。例如，

```c
tpl_node *tn;
int i;
tn = tpl_map( "A(i)", &i );
```

The function creates a mapping between the items in the format string and the C program variables whose addresses are given. Later, the C variables will be read or written as the tpl is packed or unpacked.

该函数在格式字符串中的项和给定地址的 C 程序变量之间创建映射。稍后，将在打包或解包 tpl 时读取或写入 C 变量。

This function returns a `tpl_node*` on success, or `NULL` on failure.

如果函数成功，则返回一个`tpl_node*` ，如果失败，则返回`NULL`。

### tpl_pack

The function `tpl_pack()` packs data into a tpl. The arguments to `tpl_pack()` are a `tpl_node*` and an [index number](http://troydhanson.github.io/tpl/userguide.html#index).

函数 `tpl_pack()` 将数据打包到一个 tpl 中。` tpl_pack()` 的参数是一个 `tpl_node*` 和一个索引号。

```c
tn = tpl_map("A(i)A(c)", &i, &c);
for(i=0; i<10; i++) tpl_pack(tn, 1);    /* pack 0-9 into index 1 */
for(c='a'; c<='z'; c++) tpl_pack(tn, 2); /* pack a-z into index 2 */
```

Data is copied when packed 打包时复制数据

Every call to `tpl_pack()` immediately *copies* the data being packed. Thus the program is free to immediately overwrite or re-use the packed variables.

每次调用 tpl_pack() 都会立即复制正在打包的数据。因此，程序可以自由地立即覆盖或重新使用打包变量。

#### Index number 0

It is necessary to pack index number 0 only if the format string contains characters that are not inside an `A(...)`, such as the `i` in the format string `iA(c)`.

只有当格式字符串包含不在 `A(...)` 内的字符时，才需要打包索引号 0，例如格式字符串 `iA(c)` 中的 `i`。

#### Variable-length arrays 变长数组

##### Adding elements to an array 向数组中添加元素

To add elements to a variable-length array, call `tpl_pack()` repeatedly. Each call adds another element to the array.

要将元素添加到可变长度数组，请重复调用` tpl_pack()`。每次调用都会将另一个元素添加到数组中。

##### Zero-length arrays are ok 长度为零的数组也可以

It’s perfectly acceptable to pack nothing into a variable-length array, resulting in a zero-length array.

不将任何内容打包到可变长度数组中是完全可以接受的，这会导致数组长度为零。

##### Packing nested arrays 打包嵌套的数组

In a format string containing a nested, variable-length array, such as `A(A(s))`, the inner, child array should be packed prior to the parent array.

在包含嵌套可变长度数组的格式字符串中，例如 `A(A(s))`，内部子数组应该在父数组之前打包。

When you pack a parent array, a "snapshot" of the current child array is placed into the parent’s new element. Packing a parent array also empties the child array. This way, you can pack new data into the child, then pack the parent again. This creates distinct parent elements which each contain distinct child arrays.

当你打包一个父数组时，当前子数组的“快照”被放置到父数组的新元素中。打包父数组也会清空子数组。这样，你可以将新数据打包到子项中，然后再次打包父项。这会创建不同的父元素，每个元素都包含不同的子数组。

| Tip  | When dealing with nested arrays like `A(A(i))`, *pack* them from the "inside out" (child first), but *unpack* them from the "outside in" (parent first). |
| ---- | ------------------------------------------------------------ |
|      | 在处理像 `A(A(i))` 这样的嵌套数组时，从“由内而外”(子优先)打包它们，但从“由外而内”（父优先）解包。 |

The example below creates a tpl having the format string `A(A(c))`.

下面的示例创建了一个具有格式字符串`A(A(c))` 的 tpl。

Packing nested arrays 打包嵌套的数组

```c
#include "tpl.h"

int main() {
    char c;
    tpl_node *tn;

    tn = tpl_map("A(A(c))", &c);

    for(c='a'; c<'c'; c++) tpl_pack(tn,2);  /* pack child (twice) */
    tpl_pack(tn, 1);                        /* pack parent */

    for(c='1'; c<'4'; c++) tpl_pack(tn,2);  /* pack child (three times) */
    tpl_pack(tn, 1);                        /* pack parent */

    tpl_dump(tn, TPL_FILE, "test40.tpl");
    tpl_free(tn);
}
```

This creates a nested array in which the parent has two elements: the first element is the two-element nested array *a*, *b*; and the second element is the three-element nested array *1*, *2*, *3*. The [nested unpacking example](http://troydhanson.github.io/tpl/userguide.html#nested_unpack) shows how this tpl is unpacked.

这将创建一个嵌套数组，其中父元素有两个元素：第一个元素是包含两个元素嵌套数组 a、b；第二个元素是包含三个元素嵌套数组 1、2、3。嵌套解包示例显示了如何解包这个 tpl。

### tpl_dump

After packing a tpl, `tpl_dump()` is used to write the tpl image to a file, memory buffer or file descriptor. The corresponding modes are shown below. A final mode is for querying the output size without actually performing the dump.

打包 tpl 后，`tpl_dump()` 用于将 tpl 镜像写入文件、内存缓冲区或文件描述符。对应的模式如下所示。最后一种模式是在不实际执行转储的情况下查询输出大小。

| Write to…       | Usage                                                    |
| --------------- | -------------------------------------------------------- |
| file            | `tpl_dump(tn, TPL_FILE, "file.tpl" );`                   |
| file descriptor | `tpl_dump(tn, TPL_FD, 2);`                               |
| memory          | `tpl_dump(tn, TPL_MEM, &addr, &len );`                   |
| caller’s memory | `tpl_dump(tn, TPL_MEM|TPL_PREALLOCD, buf, sizeof(buf));` |
| just get size   | `tpl_dump(tn, TPL_GETSIZE, &sz);`                        |

The first argument is the `tpl_node*` and the second is one of these constants:

第一个参数是 `tpl_node*`，第二个是这些常量之一：

- `TPL_FILE`

  Writes the tpl to a file whose name is given in the following argument. The file is created with permissions 664 (`rw-rw-r--`) unless further restricted by the process `umask`.

  将 tpl 写入文件，该文件的名称在之后的参数中给出。该文件是使用权限 664 (rw-rw-r--) 创建的，除非受到进程 umask 的进一步限制。

- `TPL_FD`

  Writes the tpl to the file descriptor given in the following argument. The descriptor can be either blocking or non-blocking, but will busy-loop if non-blocking and the contents cannot be written immediately.

  将 tpl 写入之后的参数中给出的文件描述符。描述符可以是阻塞的，也可以是非阻塞的，如果非阻塞且内容不能立即写入，则会出现忙循环。

- `TPL_MEM`

  Writes the tpl to a memory buffer. The following two arguments must be a `void**` and a `size_t*`. The function will allocate a buffer and store its address and length into these locations. The caller is responsible to `free()` the buffer when done using it.

  将 tpl 写入内存缓冲区。之后的两个参数必须是 `void**` 和 `size_t*`。该函数将分配一个缓冲区并将其地址和长度存储到这些位置。调用者负责在使用完缓冲区后`free()`缓冲区。

- `TPL_MEM|TPL_PREALLOCD`

  Writes the tpl to a memory buffer that the caller has already allocated or declared. The following two arguments must be a `void*` and a `size_t` specifying the buffer address and size respectively. (If the buffer is of insufficient size to receive the tpl dump, the function will return -1). This mode can be useful in conjunction with `tpl_load` in `TPL_EXCESS_OK` mode, as shown [here.](http://troydhanson.github.io/tpl/userguide.html#excess_ok)

  将 tpl 写入调用者已分配或声明的内存缓冲区。之后的两个参数必须是 `void*` 和`size_t`，分别指定缓冲区地址和大小。（如果缓冲区的大小不足以接收 tpl 转储，该函数将返回 -1）。在 `TPL_EXCESS_OK` 模式下，此模式可以与 `tpl_load` 结合使用，如这里所示。

- `TPL_GETSIZE`

  This special mode does not actually dump the tpl. Instead it places the size that the dump *would* require into the `size_t` pointed to by the following argument.

  这种特殊模式实际上并不转储 tpl。相反，它将转储所需的大小放入以下参数指向的 `size_t` 中。

The return value is 0 on success, or -1 on error.

返回值为 0 表示成功，或 -1 表示错误。

The `tpl_dump()` function does not free the tpl. Use `tpl_free()` to release the tpl’s resources when done.

tpl_dump() 函数不会释放 tpl。完成后使用 `tpl_free()` 释放 tpl 的资源。

| Tip  | Back-to-back tpl images require no delimiterIf you want to store a series of tpl images, or transmit sequential tpl images over a socket (perhaps as messages to another program), you can simply dump them sequentially without needing to add any delimiter for the individual tpl images. Tpl images are internally delimited, so `tpl_load` will read just one at a time even if multiple images are contiguous. |
| ---- | ------------------------------------------------------------ |
|      | 如果你想存储一系列 tpl 镜像，或通过套接字传输顺序 tpl 镜像（可能作为消息发送到另一个程序），你可以简单地按顺序转储它们，而无需为各个 tpl 镜像添加任何分隔符。Tpl 镜像是内部分隔的，因此 `tpl_load` 一次只会读取一个，即使多个镜像是连续的。 |

### tpl_load

This API function reads a previously-dumped tpl image from a file, memory buffer or file descriptor, and prepares it for subsequent unpacking. The format string specified in the preceding call to `tpl_map()` will be cross-checked for equality with the format string stored in the tpl image.

这个 API 函数从文件、内存缓冲区或文件描述符中读取先前转储的 tpl 镜像，并为后续解包做好准备。在前面对 `tpl_map()` 的调用中指定的格式字符串将被交叉检查，以确定是否与存储在 tpl 镜像中的格式字符串相等。

```c
tn = tpl_map( "A(i)", &i );
tpl_load( tn, TPL_FILE, "demo.tpl" );
```

The first argument to `tpl_load()` is the `tpl_node*`. The second argument is one of the constants:

`tpl_load()` 的第一个参数是 `tpl_node*`。第二个参数是常量之一：

- `TPL_FILE`

  Loads the tpl from the file named in the following argument. It is also possible to bitwise-OR this flag with `TPL_EXCESS_OK` as explained below.

  从之后参数中的文件名加载 tpl。也可以将这个标志与 `TPL_EXCESS_OK` 进行按位或，如下所述。

- `TPL_MEM`

  Loads the tpl from a memory buffer. The following two arguments must be a `void*` and a `size_t`, specifying the buffer address and size, respectively. The caller must not free the memory buffer until after freeing the tpl with `tpl_free()`. (If the caller wishes to hand over responsibility for freeing the memory buffer, so that it’s automatically freed along with the tpl when `tpl_free()` is called, the constant `TPL_UFREE` may be bitwise-OR’d with `TPL_MEM` to achieve this). Furthermore, `TPL_MEM` may be bitwise-OR’d with `TPL_EXCESS_OK`, explained below.

  从内存缓冲区加载 tpl。以下两个参数必须是 `void*` 和 `size_t`，分别指定缓冲区地址和大小。在使用 tpl_free() 释放 tpl 之前，调用者不得释放内存缓冲区。（如果调用者希望移交释放内存缓冲区的责任，这样当 `tpl_free()` 被调用时，它会随着 tpl 被自动释放，则常量 `TPL_UFREE` 可以与 `TPL_MEM` 进行按位或来实现此目的）。此外，`TPL_MEM` 可以与 `TPL_EXCESS_OK` 进行按位或，如下所述。

- `TPL_FD`

  Loads the tpl from the file descriptor given in the following argument. The descriptor is read until one complete tpl image is loaded; no bytes past the end of the tpl image will be read. The descriptor can be either blocking or non-blocking, but will busy-loop if non-blocking and the contents cannot be read immediately.

  从之后参数中给出的文件描述符加载 tpl。读取描述符直到加载一个完整的 tpl 镜像；不会读取超过 tpl 镜像末尾的字节。描述符可以是阻塞的，也可以是非阻塞的，但如果非阻塞且内容不能立即读取，则会出现忙循环。

During loading, the tpl image will be extensively checked for internal validity.

在加载过程中，将广泛检查 tpl 镜像的内部有效性。

This function returns 0 on success or -1 on error.

此函数在成功时返回 0，在错误时返回 -1。

#### `TPL_EXCESS_OK`

When reading a tpl image from a file or memory (but not from a file descriptor) the size of the file or memory buffer must exactly equal that of the tpl image stored therein. In other words, no excess trailing data beyond the tpl image is permitted. The bit flag `TPL_EXCESS_OK` can be OR’d with `TPL_MEM` or `TPL_FILE` to relax this requirement.

从文件或内存（但不是从文件描述符）读取 tpl 镜像时，文件或内存缓冲区的大小必须完全等于存储在其中的 tpl 镜像的大小。换句话说，tpl 镜像之外不允许有多余的尾随数据。位标志 `TPL_EXCESS_OK` 可以与 `TPL_MEM` 或 `TPL_FILE` 进行或运算以放宽这个要求。

A situation where this flag can be useful is in conjunction with `tpl_dump` in the `TPL_MEM|TPL_PREALLOCD` mode. In this example, the program does not concern itself with the actual tpl size as long as `LEN` is sufficiently large.

此标志可能有用的情况是与 `TPL_MEM|TPL_PREALLOCD` 模式中的 `tpl_dump` 结合使用。在这个例子中，只要 `LEN` 足够大，程序就不会关心实际的 tpl 大小。

```c
char buf[LEN];  /* will store and read tpl images here */
...
tpl_dump(tn, TPL_MEM|TPL_PREALLOCD, buf, LEN);
...
tpl_load(tn, TPL_MEM|TPL_EXCESS_OK, buf, LEN);
```

### tpl_unpack

The `tpl_unpack()` function unpacks data from the tpl. When data is unpacked, it is copied to the C program variables originally specified in `tpl_map()`. The first argument to `tpl_unpack` is the `tpl_node*` for the tpl and the second argument is an [index number](http://troydhanson.github.io/tpl/userguide.html#index).

`tpl_unpack()`函数从 tpl 中解包数据。当数据解包时，它被复制到最初在 `tpl_map()` 中指定的 C 程序变量中。`tpl_unpack` 的第一个参数是 tpl 的 `tpl_node*`，第二个参数是索引号。

```c
tn = tpl_map( "A(i)A(c)", &i, &c );
tpl_load( tn, TPL_FILE, "nested.tpl" );
while (tpl_unpack( tn, 1) > 0) printf("i is %d\n", i); /* unpack index 1 */
while (tpl_unpack( tn, 2) > 0) printf("c is %c\n", c); /* unpack index 2 */
```

#### Index number 0

It is necessary to unpack index number 0 only if the format string contains characters that are not inside an `A(...)`, such as the `i` in the format string `iA(c)`.

只有当格式字符串包含不在 `A(...)` 内的字符时，才需要解压索引号 0，例如格式字符串 `iA(c)`中的 `i`。

#### Variable-length arrays

##### Unpacking elements from an array

For variable-length arrays, each call to `tpl_unpack()` unpacks another element. The return value can be used to tell when you’re done: if it’s positive, an element was unpacked; if it’s 0, nothing was unpacked because there are no more elements. A negative return value indicates an error (e.g. invalid index number). In this document, we usually unpack variable-length arrays using a `while` loop:

对于可变长度数组，每次调用 `tpl_unpack()` 都会解包另一个元素。返回值可用于告诉你什么时候完成：如果为正，则说明一个元素已解包；如果为 0，则没有任何内容被解包，因为没有更多元素。负返回值表示错误（例如无效的索引号）。在本文档中，我们通常使用 while 循环解包可变长度数组：

```c
while( tpl_unpack( tn, 1 ) > 0 ) {
    /* got another element */
}
```

##### Array length 数组长度

When unpacking a variable-length array, it may be convenient to know ahead of time how many elements will need to be unpacked. You can use `tpl_Alen()` to get this number.

解包可变长度数组时，提前知道有多少元素需要解包可能比较方便。你可以使用 `tpl_Alen()` 来获取这个数字。

##### Unpacking nested arrays 解包嵌套数组

In a format string containing a nested variable-length array such as `A(A(s))`, unpack the outer, parent array before unpacking the child array.

在包含嵌套可变长度数组（例如 `A(A(s))`）的格式字符串中，在解包子数组之前先解包外部父数组。

When you unpack a parent array, it prepares the child array for unpacking. After unpacking the elements of the child array, the program can repeat the process by unpacking another parent element, then the child elements, and so on. The example below unpacks a tpl having the format string `A(A(c))`.

当你解包父数组时，它会准备子数组以解包。在解包子数组的元素之后，程序可以重复这个过程，先解包另一个父元素，然后解包子元素，依此类推。下面的示例将一个具有格式字符串`A(A(c))`的 tpl 解包。

Unpacking nested arrays

```c
#include "tpl.h"
#include <stdio.h>

int main() {
    char c;
    tpl_node *tn;

    tn = tpl_map("A(A(c))", &c);

    tpl_load(tn, TPL_FILE, "test40.tpl");
    while (tpl_unpack(tn,1) > 0) {
        while (tpl_unpack(tn,2) > 0) printf("%c ",c);
        printf("\n");
    }
    tpl_free(tn);
}
```

The file `test40.tpl` is from the [nested packing example](http://troydhanson.github.io/tpl/userguide.html#nested_pack). When run, this program prints:

文件 `test40.tpl` 来自嵌套打包示例。运行时，该程序打印：

```
a b
1 2 3
```

### tpl_free

The final step for any tpl is to release it using `tpl_free()`. Its only argument is the `tpl_node*` to free.

任何 tpl 的最后一步是使用 `tpl_free()` 释放它。它唯一的参数是要释放的 `tpl_node*`。

```c
tpl_free( tn );
```

This function does not return a value (it is `void`).

这个函数没有返回值(它是`void`)。

### tpl_Alen

This function takes a `tpl_node*` and an index number and returns an `int` specifying the number of elements in the variable-length array.

这个函数接受一个 `tpl_node*`和一个索引号，并返回一个`int`值，指定变长数组的元素个数。

```c
num_elements = tpl_Alen(tn, index);
```

This is mainly useful for programs that unpack data and need to know ahead of time the number of elements that will need to be unpacked. (It returns the current number of elements; it will decrease as elements are unpacked).

这主要用于解包数据并需要提前知道需要解包的元素数量的程序。 （它返回当前元素的数量；它会随着元素的解包而减少）。

### tpl_peek

This function peeks into a file or a memory buffer containing a tpl image and returns a copy of its format string. It can also peek at the lengths of any fixed-length arrays in the format string, or it can also peek into the data stored in the tpl.

这个函数查看包含 tpl 镜像的文件或内存缓冲区，并返回其格式字符串的副本。它还可以查看格式字符串中任何固定长度数组的长度，或者还可以查看存储在tpl中的数据。

#### Format peek

The format string can be obtained like this:

格式字符串可以这样获取：

```c
fmt = tpl_peek(TPL_FILE, "file.tpl");
fmt = tpl_peek(TPL_MEM, addr, sz);
```

On success, a copy of the format string is returned. The caller must eventually free it. On error, such as a non-existent file, or an invalid tpl image, it returns `NULL`.

成功时，返回格式字符串的副本。调用者最终必须释放它。出错时，例如不存在的文件或无效的 tpl 镜像，它返回 `NULL`。

#### Array length peek

The lengths of all fixed-length arrays in the format string can be queried using the `TPL_FXLENS` mode. It provides the number of such fixed-length arrays and their lengths. If the former is non-zero, the caller must free the latter array when finished. The format string itself must also be freed.

格式字符串中所有定长数组的长度都可以使用 `TPL_FXLENS` 模式查询。它提供这种固定长度数组的数量及其长度。如果前者非零，则调用者必须在完成后释放后者数组。格式字符串本身也必须被释放。

```c
uint32_t num_fxlens, *fxlens, j;
fmt = tpl_peek(TPL_FILE|TPL_FXLENS, filename, &num_fxlens, &fxlens);
if (fmt) {
  printf("format %s, num_fxlens %u\n", fmt, num_fxlens);
  for(j=0; j<num_fxlens; j++) printf("fxlens[%u] %u\n", j, fxlens[j]);
  if (num_fxlens > 0) free(fxlens);
  free(fmt);
}
```

The `TPL_FXLENS` mode is mutually exclusive with `TPL_DATAPEEK`.

`TPL_FXLENS` 模式与 `TPL_DATAPEEK` 模式互斥。

#### Data peek

To peek into the data, additional arguments are used. This is a quick alternative to mapping, loading and unpacking the tpl, but peeking is limited to the data in index 0. In other words, no peeking into `A(...)` types. Suppose the tpl image in `file.tpl` has the format string `siA(i)`. Then the index 0 format characters are `si`. This is how to peek at their content:

为了查看数据，使用了额外的参数。这是映射、加载和解包 tpl 的一种快速替代方法，但查看仅限于索引 0 中的数据。换句话说，不要查看`A(...)`类型。假设文件中有 tpl 镜像。tpl具有格式字符串`siA(i)`。那么索引 0 格式字符是`si`。以下是如何查看它们的内容:

```c
char *s;
int i;
fmt = tpl_peek(TPL_FILE | TPL_DATAPEEK, "file.tpl", "si", &s, &i);
```

Now `s`, `i`, and `fmt` have been populated with data. The caller must eventually free `fmt` and `s` because they are allocated strings. Of course, it works with `TPL_MEM` as well as `TPL_FILE`. Notice that `TPL_DATAPEEK` was OR’d with the mode. You can also specify *any leading portion* of the index 0 format if you don’t want to peek at the whole thing:

现在 `s`、`i` 和 `fmt` 已经填充了数据。调用者最终必须释放 `fmt` 和 `s`，因为它们是分配的字符串。当然，它可以与 `TPL_MEM` 和 `TPL_FILE` 一起工作。请注意，`TPL_DATAPEEK` 与模式进行了或运算。如果你不想查看整个内容，还可以指定索引 0 格式的任何前导部分：

```c
fmt = tpl_peek(TPL_FILE | TPL_DATAPEEK, "file.tpl", "s", &s);
```

The `TPL_DATAPEEK` mode is mutually exclusive with `TPL_FXLENS`.

`TPL_DATAPEEK` 模式与 `TPL_FXLENS` 互斥。

##### Structure peek

Lastly you can peek into `S(...)` structures in index 0, but omit the surrounding `S(...)` in the format, and specify an argument to receive each structure member individually. You can specify any leading portion of the structure format. For example if `struct.tpl` has the format string `S(si)`, you can peek at its data in these ways:

最后，你可以查看索引 0 中的 `S(...)` 结构，但在格式中省略周围的 `S(...)`，并指定一个参数以单独接收每个结构成员。你可以指定结构格式的任何前导部分。例如，如果 `struct.tpl` 具有格式字符串 `S(si)`，你可以通过以下方式查看其数据：

```c
fmt = tpl_peek(TPL_FILE | TPL_DATAPEEK, "struct.tpl", "s", &s);
fmt = tpl_peek(TPL_FILE | TPL_DATAPEEK, "struct.tpl", "si", &s, &i);
```

### tpl_jot

This is a quick shortcut for generating a tpl. It can be used instead of the usual "map, pack, dump, and free" lifecycle. With `tpl_jot` all those steps are handled for you. It only works for simple formats-- namely, those without `A(...)` in their format string. Here is how it is used:

这是生成 tpl 的快捷方式。它可以代替通常的“映射、打包、转储和免费”的生命周期。使用`tpl_jot` 可以为你处理所有这些步骤。它只适用于简单的格式 -- 即格式字符串中没有`A(...)` 的格式。下面是它的用法:

```c
char *hello = "hello", *world = "world";
tpl_jot( TPL_FILE, "file.tpl", "ss", &hello, &world);
```

It supports the three standard modes, `TPL_FILE`, `TPL_FD` and `TPL_MEM`. It returns -1 on failure (such as a bad format string or error writing the file) or 0 on success.

它支持三种标准模式，`TPL_FILE`、`TPL_FD` 和 `TPL_MEM`。它在失败时返回 -1（例如错误的格式字符串或写入文件时出错）或在成功时返回 0。

### tpl_hook

Most users will just leave these hooks at their default values. You can change these hook values if you want to modify tpl’s internal memory management and error reporting behavior.

大多数用户只会保留这些钩子的默认值。如果你想修改 tpl 的内部内存管理和错误报告行为，你可以修改这些钩子值。

A global structure called `tpl_hook` encapsulates the hooks. A program can reconfigure any hook by specifying an alternative function whose prototype matches the default. For example:

一个名为 tpl_hook 的全局结构体封装了这些钩子。程序可以通过指定原型与默认值匹配的替代函数来重新配置任何钩子。例如：

```c
#include "tpl.h"
extern tpl_hook_t tpl_hook;
int main() {
    tpl_hook.oops = printf;
    ...
}
```

| Hook                  | Description                                   | Default         |
| --------------------- | --------------------------------------------- | --------------- |
| `tpl_hook.oops`       | log error messages 记录错误信息               | `tpl_oops`      |
| `tpl_hook.malloc`     | allocate memory 分配内存                      | `malloc`        |
| `tpl_hook.realloc`    | reallocate memory 重新分配内存                | `realloc`       |
| `tpl_hook.free`       | free memory 释放内存                          | `free`          |
| `tpl_hook.fatal`      | log fatal message and exit 记录致命消息并退出 | `tpl_fatal`     |
| `tpl_hook.gather_max` | tpl_gather max image size 最大镜像大小        | `0 (unlimited)` |

#### The oops hook

The `oops` has the same prototype as `printf`. The built-in default oops handling function writes the error message to `stderr`.

`oops` 的原型与 `printf` 相同。内置的默认 oops 处理函数将错误消息写入 `stderr`。

#### The fatal hook

The fatal hook is invoked when a tpl function cannot continue because of an out- of-memory condition or some other usage violation or inconsistency. It has this prototype:

当 tpl 函数由于内存不足或某些其他使用违规或不一致而无法继续时，将调用致命钩子。它有这个原型：

```c
void fatal_fcn(char *fmt, ...);
```

The `fatal` hook must not return. It must either exit, *or* if the program needs to handle the failure and keep executing, `setjmp` and `longjmp` can be used. The default behavior is to `exit(-1)`.

`fatal`钩子不能返回。它必须退出，或者如果程序需要处理失败并继续执行，可以使用 `setjmp` 和 `longjmp`。默认行为是`exit(-1)`。

Using longjmp in a fatal error handler

```c
#include <setjmp.h>
#include <stdio.h>
#include <stdarg.h>
#include "tpl.h"

jmp_buf env;
extern tpl_hook_t tpl_hook;

void catch_fatal(char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  longjmp(env,-1);                /* return to setjmp point */
}

int main() {
  int err;
  tpl_node *tn;
  tpl_hook.fatal = catch_fatal;    /* install fatal handler */

  err = setjmp(env); /* on error, control will return here  */
  if (err) {
    printf("caught error!\n");
    return -1;
  }

  tn = tpl_map("@");              /* generate a fatal error */
  printf("program ending, without error\n");
  return 0;
}
```

This example is included in `tests/test123.c`. When run, this program prints:

此示例包含在 `tests/test123.c` 中。当运行时，这个程序打印:

```
unsupported option @
failed to parse @
caught error!
```

### tpl_gather

> Most programs don’t need this
>
> 大多数程序不需要这个
>
> Normally, `tpl_load()` is used to read a tpl image having an expected format string. A more generic operation is to acquire a tpl image whose format string is unknown. E.g., a generic message-receiving function might gather tpl images of varying format and route them to their final destination. This is the purpose of `tpl_gather`. It produces a memory buffer containing one tpl image. If there are multiple contiguous images in the input, it gathers exactly one image at a time.
>
> 通常，`tpl_load()` 用于读取具有预期格式字符串的 tpl 镜像。更通用的操作是获取格式字符串未知的 tpl 镜像。例如，一个通用的消息接收函数可能会收集不同格式的 tpl 镜像并将它们路由到它们的最终目的地。这就是 `tpl_gather` 的目的。它产生一个包含一个 tpl 镜像的内存缓冲区。如果输入中有多个连续的镜像，它一次只收集一个镜像。

The prototype for this function is:

这个函数的原型是：

```
int tpl_gather( int mode, ...);
```

The `mode` argument is one of three constants listed below, which must be followed by the mode-specific required arguments:

`mode`参数是下面列出的三个常量之一，后面必须跟特定于模式的必需参数：

```c
TPL_GATHER_BLOCKING,    int fd, void **img, size_t *sz
TPL_GATHER_NONBLOCKING, int fd, tpl_gather_t **gs, tpl_gather_cb *cb, void *data
TPL_GATHER_MEM,         void *addr, size_t sz, tpl_gather_t **gs, tpl_gather_cb *cb, void *data
```

Note 

> `tpl_hook.gather_max`
>
> All modes honor `tpl_hook.gather_max`, specifying the maximum byte size for a tpl image to be gathered (the default is unlimited, signified by 0). If a source attempts to send a tpl image larger than this maximum, whatever partial image has been read will be discarded, and no further reading will take place; in this case `tpl_gather` will return a negative (error) value to inform the caller that it should stop gathering from this source, and close the originating file descriptor if there is one. (The whole idea is to prevent untrusted sources from sending extremely large tpl images which would consume too much memory.)
>
> 所有模式都遵循 `tpl_hook.gather_max`，指定要收集的 tpl 镜像的最大字节大小（默认为无限制，由 0 表示）。如果一个源尝试发送大于此最大值的 tpl 镜像，则已读取的任何部分图像都将被丢弃，并且不会进行进一步的读取；在这种情况下， `tpl_gather` 将返回一个负（错误）值以通知调用者它应该停止从这个源收集，并关闭原始文件描述符（如果有的话）。（整个想法是防止不受信任的源发送非常大的 tpl 镜像，这会消耗太多内存。）

#### `TPL_GATHER_BLOCKING`

In this mode, `tpl_gather` blocks while reading file descriptor `fd` until one complete tpl image is read. No bytes past the end of the tpl image will be read. The address of the buffer containing the image is returned in `img` and its size is placed in `sz`. The caller is responsible for eventually freeing the buffer. The function returns 1 on success, 0 on end-of-file, or a negative number on error.

在这种模式下，`tpl_gather` 在读取文件描述符 `fd` 时会阻塞，直到读取一个完整的 tpl 镜像。不会读取超过 tpl 镜像末尾的字节。包含镜像的缓冲区的地址在 `img` 中返回，其大小放在 `sz` 中。调用者负责最终释放缓冲区。该函数在成功时返回 1，在文件结束时返回 0，或者在错误时返回负数。

#### `TPL_GATHER_NONBLOCKING`

This mode is for non-blocking, event-driven programs that implement their own file descriptor readability testing using `select()` or the like. In this mode, tpl images are gathered in chunks as data becomes readable. Whenever a full tpl image has been gathered, it invokes a caller-specified callback to do something with the image. The arguments are the file descriptor `fd` which the caller has determined to be readable and which must be in non-blocking mode, a pointer to a file-descriptor-specific handle which the caller has declared (explained below); a callback to invoke when a tpl image has been read; and an opaque pointer that will passed to the callback.

这种模式适用于非阻塞的、事件驱动的程序，这些程序使用 `select()` 或类似方法实现了自己的文件描述符可读性测试。在这种模式下，当数据变得可读时，将 tpl 镜像以块的形式收集。只要收集了完整的 tpl 镜像，它就会调用调用者指定的回调函数来处理镜像。参数是文件描述符 `fd`，调用者认为它是可读的，必须处于非阻塞模式，指向调用者声明的文件描述符特定句柄的指针（解释如下）；读取 tpl 镜像时要调用的回调；和一个传递给回调函数的不透明指针。

For each file descriptor on which `tpl_gather` will be used, the caller must declare a `tpl_gather_t*` and initialize it to `NULL`. Thereafter it will be used internally by `tpl_gather` whenever data is readable on the descriptor.

对于将使用 `tpl_gather` 的每个文件描述符，调用者必须声明一个 `tpl_gather_t*` 并将其初始化为 `NULL`。此后，当描述符上的数据可读时，`tpl_gather` 就会在内部使用它。

The callback will only be invoked whenever `tpl_gather()` has accumulated one complete tpl image. It must have this prototype:

只有当 `tpl_gather()` 累积了一个完整的 tpl 镜像时，才会调用回调。它必须有这个原型：

```c
int (tpl_gather_cb)(void *img, size_t sz, void *data);
```

The callback can do anything with the tpl image but it must not free it. It can be copied if it needs to survive past the callback’s return. The callback should return 0 under normal circumstances, or a negative number to abort; that is, returning a negative number causes `tpl_gather` itself to discard any remaining full or partial tpl images that have been read, and to return a negative number (-4 in particular) to signal its caller to close the file descriptor.

回调可以对 tpl 镜像做任何事情，但不能释放它。如果它需要在回调的返回后继续存在，则可以复制它。回调正常情况下应该返回0，或者返回负数中止；也就是说，返回一个负数会导致 `tpl_gather` 本身丢弃任何剩余的已读取的完整或部分 tpl 镜像，并返回一个负数（特别是 -4）以通知其调用者关闭文件描述符。

The return value of `tpl_gather()` is negative if an error occurred or 0 if a normal EOF was encountered-- both cases require that the caller close the file descriptor (and stop monitoring it for readability, obviously). If the return value is positive, the function succeeded in gathering whatever data was currently readable, which may have been a partial tpl image, or one or more complete images.

如果发生错误，则 `tpl_gather()` 的返回值为负数；如果遇到正常的 EOF，则返回 0 -- 这两种情况都要求调用者关闭文件描述符（显然，为了可读性而停止监视它）。如果返回值为正，则该函数成功收集了当前可读的任何数据，可能是部分 tpl 镜像，或者是一个或多个完整镜像。

##### Typical Usage 典型用法

The program will have established a file descriptor in non-blocking mode and be monitoring it for readability, using `select()`. Whenever it’s readable, the program calls `tpl_gather()`. In skeletal terms:

该程序将在非阻塞模式下建立一个文件描述符，并使用 `select()` 监视它的可读性。只要它可读，程序就会调用 `tpl_gather()`。代码轮廓：

```c
tpl_gather_t *gt=NULL;
int rc;
void fd_is_readable(int fd) {
  rc = tpl_gather( TPL_GATHER_NONBLOCKING, fd, &gt, callback, NULL );
  if (rc <= 0) {
      close(fd);               /* got eof or fatal */
      stop_watching_fd(fd);
  }
}
int callback( void *img, size_t sz, void *data ) {
  printf("got a tpl image\n"); /* do something with img. do not free it. */
  return 0;                    /* normal (no error) */
}
```

#### `TPL_GATHER_MEM`

This mode is identical to `TPL_GATHER_NONBLOCKING` except that it gathers from a memory buffer instead of from a file descriptor. In other words, if some other layer of code-- say, a decryption function (that is decrypting fixed-size blocks) produces tpl fragments one-by-one, this mode can be used to reconstitute the tpl images and invoke the callback for each one. Its parameters are the same as for the `TPL_GATHER_NONBLOCKING` mode except that instead of a file descriptor, it takes a buffer address and size. The return values are also the same as for `TPL_GATHER_NONBLOCKING` noting of course there is no file descriptor to close on a non-positive return value.

这种模式与 `TPL_GATHER_NONBLOCKING` 相同，只是它从内存缓冲区而不是文件描述符中收集。换句话说，如果其他一些代码层 -- 例如，一个解密函数（即解密固定大小的块）一个接一个地产生 tpl 片段，这种模式可以用来重构 tpl 镜像并为每个镜像调用回调。。它的参数与 `TPL_GATHER_NONBLOCKING` 模式的参数相同，只是它使用缓冲区地址和大小来代替文件描述符。返回值也与 `TPL_GATHER_NONBLOCKING` 相同，当然，对于非正返回值，没有文件描述符可以关闭。