# stb_sprintf.h

https://github.com/nothings/stb

fast sprintf, snprintf for C/C++



Single file sprintf replacement.

单文件 sprintf 替换。

Originally written by Jeff Roberts at RAD Game Tools - 2015/10/20.
Hereby placed in public domain.

最初由杰夫·罗伯茨 (Jeff Roberts) 在 RAD Game Tools 撰写 - 2015/10/20。
特此置于公共领域。

This is a full sprintf replacement that supports everything that the C runtime sprintfs support, including float/double, 64-bit integers, hex floats, field parameters (%*.*d stuff), length reads backs, etc.

这是一个完整的 sprintf 替换，支持 C 运行时 sprintfs 支持的所有内容，包括浮点/双精度、64 位整数、十六进制浮点数、字段参数（%*.*d 内容）、长度回读等。

Why would you need this if sprintf already exists?  Well, first off, it's *much* faster (see below). It's also much smaller than the CRT versions code-space-wise. We've also added some simple improvements that are super handy (commas in thousands, callbacks at buffer full, for example). Finally, the format strings for MSVC and GCC differ for 64-bit integers (among other small things), so this lets you use the same format strings in cross platform code.

如果 sprintf 已经存在，你为什么需要这个？ 嗯，首先，它*快得多*（见下文）。 在代码空间方面，它也比 CRT 版本小得多。 我们还添加了一些非常方便的简单改进（例如，以千为单位的逗号，缓冲区已满时的回调）。 最后，MSVC 和 GCC 的格式字符串对于 64 位整数（以及其他小东西）有所不同，因此这允许您在跨平台代码中使用相同的格式字符串。

It uses the standard single file trick of being both the header file and the source itself. If you just include it normally, you just get the header file function definitions. To get the code, you include it from a C or C++ file and define STB_SPRINTF_IMPLEMENTATION first.

它使用标准的单文件技巧，既是头文件又是源文件本身。 如果你只是正常包含它，你只会得到头文件函数定义。 要获取代码，您需要从 C 或 C++ 文件中包含它并首先定义 STB_SPRINTF_IMPLEMENTATION。

It only uses va_args macros from the C runtime to do it's work. It does cast doubles to S64s and shifts and divides U64s, which does drag in CRT code on most platforms.

它只使用 C 运行时中的 va_args 宏来完成它的工作。 它确实将 doubles 转换为 S64s 并移动和划分 U64s，这在大多数平台上都会拖入 CRT 代码。

It compiles to roughly 8K with float support, and 4K without.
As a comparison, when using MSVC static libs, calling sprintf drags in 16K.

它编译为大约 8K 支持浮点数，不支持则编译为 4K。
作为比较，当使用 MSVC 静态库时，调用 sprintf 会拖入 16K。
