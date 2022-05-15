## LodePNG

https://github.com/lvandeve/lodepng

PNG encoder and decoder in C and C++, without dependencies

C 和 C++ 的 PNG 编码器和解码器，无依赖关系

Home page: http://lodev.org/lodepng/

### Documentation

Detailed documentation is included in a large comment in the second half of the header file `lodepng.h`.

详细文档包含在头文件 `lodepng.h` 后半部分的大注释中。

Source code examples using LodePNG can be found in the examples directory.

可以在示例目录中找到使用 LodePNG 的源代码示例。

An FAQ can be found on http://lodev.org/lodepng/

### Building

Only two files are needed to encode and decode PNGs:

编码和解码 PNG 只需要两个文件：

- `lodepng.cpp` (or renamed to `lodepng.c`)
- `lodepng.h`

All other files are just source code examples, tests, misc utilities, etc..., which are normally not needed in projects using this.

所有其他文件只是源代码示例、测试、杂项实用程序等...，在使用它的项目中通常不需要这些文件。

You can include the files directly in your project's source tree and its makefile, IDE project file, or other build system. No library is necessary.

你可以将文件直接包含在项目的源代码树及其 makefile、IDE 项目文件或其他构建系统中。不需要库。

In addition to C++, LodePNG also supports ANSI C (C89), with all the same functionality: C++ only adds extra convenience API.

除了 C++，LodePNG 还支持 ANSI C (C89)，具有所有相同的功能：C++ 只是增加了额外的便利 API。

For C, rename `lodepng.cpp` to `lodepng.c`.

对于 C，将 `lodepng.cpp` 重命名为 `lodepng.c`。

Consider using git submodules to include LodePNG in your project.

考虑使用 git 子模块在项目中包含 LodePNG。

### Compiling in C++

If you have a hypothetical `your_program.cpp` that #includes and uses `lodepng.h`, you can build as follows:

如果你有一个假设的 `your_program.cpp`，其中 #includes 并使用 `lodepng.h`，你可以按如下方式构建：

```
g++ your_program.cpp lodepng.cpp -Wall -Wextra -pedantic -ansi -O3
```

or:

```
clang++ your_program.cpp lodepng.cpp -Wall -Wextra -pedantic -ansi -O3
```

This shows compiler flags it was designed for, but normally one would use the compiler or build system of their project instead of those commands, and other C++ compilers are supported.

这显示了它设计的编译器标志，但通常人们会使用他们项目的编译器或构建系统而不是那些命令，并且支持其他 C++ 编译器。

### Compiling in C

Rename `lodepng.cpp` to `lodepng.c` for this.

为此，将 `lodepng.cpp` 重命名为 `lodepng.c` 。

If you have a hypothetical your_program.c that #includes and uses lodepng.h, you can build as follows:

如果你有一个假设的 your_program.c，其中 #includes 并使用 lodepng.h，你可以按如下方式构建：

```
gcc your_program.c lodepng.c -ansi -pedantic -Wall -Wextra -O3
```

or

```
clang your_program.c lodepng.c -ansi -pedantic -Wall -Wextra -O3
```

This shows compiler flags it was designed for, but normally one would use the compiler or build system of their project instead of those commands, and other C compilers are supported.

这显示了它设计的编译器标志，但通常人们会使用他们项目的编译器或构建系统而不是那些命令，并且支持其他 C 编译器。

### Makefile

There is a Makefile, but this is not intended for using LodePNG itself since the way to use that one is to include its source files in your program. The Makefile only builds development and testing utilities. It can be used as follows:

有一个 Makefile，但这并不是为了使用 LodePNG 本身，因为使用它的方法是将其源文件包含在你的程序中。Makefile 仅构建开发和测试实用程序。它可以按如下方式使用：

```
make -j
```
