# utf8.h

https://github.com/sheredom/utf8.h

A simple one header solution to supporting utf8 strings in C and C++.

## Usage

Just `#include "utf8.h"` in your code!

The current supported platforms are Linux, macOS and Windows.

The current supported compilers are gcc, clang, MSVC's cl.exe, and clang-cl.exe.

## Design

The utf8.h API matches the string.h API as much as possible by design. There are a few major differences though.

utf8.h uses char8_t* in C++ 20 instead of char*

Anywhere in the string.h or strings.h documentation where it refers to 'bytes' I have changed that to utf8 codepoints. For instance, utf8len will return the number of utf8 codepoints in a utf8 string - which does not necessarily equate to the number of bytes.

## API function docs

```
int utf8casecmp(const void *src1, const void *src2);
```

Return less than 0, 0, greater than 0 if `src1 < src2`, `src1 == src2`, `src1 > src2` respectively, case insensitive.

如果 src1 < src2, src1 == src2, src1 > src2 则分别返回小于 0、0、大于 0，不区分大小写。

```
void *utf8cat(void *dst, const void *src);
```

Append the utf8 string `src` onto the utf8 string `dst`.

将 utf8 字符串 src 附加到 utf8 字符串 dst 上。

```
void *utf8chr(const void *src, utf8_int32_t chr);
```

Find the first match of the utf8 codepoint `chr` in the utf8 string `src`.

在 utf8 字符串 src 中找到 utf8 代码点 chr 的第一个匹配项。

```
int utf8cmp(const void *src1, const void *src2);
```

Return less than 0, 0, greater than 0 if `src1 < src2`,
`src1 == src2`, `src1 > src2` respectively.

如果 src1 < src2, src1 == src2, src1 > src2 分别返回小于 0, 0, 大于 0 。

```
void *utf8cpy(void *dst, const void *src);
```

Copy the utf8 string `src` onto the memory allocated in `dst`.

将 utf8 字符串 src 复制到 dst 中分配的内存中。

```
size_t utf8cspn(const void *src, const void *reject);
```

Number of utf8 codepoints in the utf8 string `src` that consists entirely
of utf8 codepoints not from the utf8 string `reject`.

utf8 字符串 src 开头有多少个字符都不含字符串 reject 中的字符。

```
void *utf8dup(const void *src);
```

Duplicate the utf8 string `src` by getting its size, `malloc`ing a new buffer
copying over the data, and returning that. Or 0 if `malloc` failed.

通过获取它的大小来复制 utf8 字符串 src，分配一个新的缓冲区 复制数据，然后返回。如果 malloc 失败，则为 0。

```
size_t utf8len(const void *str);
```

Number of utf8 codepoints in the utf8 string `str`,
**excluding** the null terminating byte.

utf8 字符串 str 中的 utf8 字符长度， 不包括空终止字节。

```
size_t utf8nlen(const void *str, size_t n);
```

Similar to `utf8len`, except that only at most `n` bytes of `src` are looked.

与 utf8len 类似，只是最多只查找 n 字节的 src。

```
int utf8ncasecmp(const void *src1, const void *src2, size_t n);
```

Return less than 0, 0, greater than 0 if `src1 < src2`, `src1 == src2`,
`src1 > src2` respectively, case insensitive. Checking at most `n`
bytes of each utf8 string.

如果 src1 < src2, src1 == src2, src1 > src2 分别返回小于 0, 0, 大于 0 ，不区分大小写。最多检查每个 utf8 字符串的 n 个字节数。

```
void *utf8ncat(void *dst, const void *src, size_t n);
```

Append the utf8 string `src` onto the utf8 string `dst`,
writing at most `n+1` bytes. Can produce an invalid utf8
string if `n` falls partway through a utf8 codepoint.

将 utf8 字符串 src 附加到 utf8 字符串 dst 上， 最多写入 n+1 个字节。 

如果 n 在 utf8 代码点中途则会产生无效的 utf8字符串。

```
int utf8ncmp(const void *src1, const void *src2, size_t n);
```

Return less than 0, 0, greater than 0 if `src1 < src2`,
`src1 == src2`, `src1 > src2` respectively. Checking at most `n`
bytes of each utf8 string.

如果 src1 < src2, src1 == src2, src1 > src2 分别返回小于 0, 0, 大于 0 。最多检查每个 utf8 字符串的 n 个字节数。

```
void *utf8ncpy(void *dst, const void *src, size_t n);
```

Copy the utf8 string `src` onto the memory allocated in `dst`.
Copies at most `n` bytes. If `n` falls partway through a utf8 codepoint, or if `dst` doesn't have enough room for a null terminator, the final string will be cut short to preserve utf8 validity.

将 utf8 字符串 src 复制到 dst 中分配的内存中。 最多复制 n 个字节。如果 n 落在 utf8 代码点的中途，或者如果 dst 没有足够的空间容纳空终止符，则最终字符串将被缩短以保持 utf8 有效性。

```
void *utf8pbrk(const void *str, const void *accept);
```

Locates the first occurrence in the utf8 string `str` of any byte in the
utf8 string `accept`, or 0 if no match was found.

定位 utf8 字符串 `a` 中第一个匹配utf8 字符串 `b`中任何字节的项，如果未找到匹配项，则为 0。

```
void *utf8rchr(const void *src, utf8_int32_t chr);
```

Find the last match of the utf8 codepoint `chr` in the utf8 string `src`.

在 utf8 字符串 src 中查找 utf8 代码点 chr 的最后一个匹配项。

```
size_t utf8size(const void *str);
```

Number of bytes in the utf8 string `str`,
including the null terminating byte.

utf8 字符串 str 中的字节数， 包括空终止字节。

```
size_t utf8size_lazy(const void *str);
```

Similar to `utf8size`, except that the null terminating byte is **excluded**.

与 utf8size 类似，只是不包括空终止字节。

```
size_t utf8nsize_lazy(const void *str, size_t n);
```

Similar to `utf8size`, except that only at most `n` bytes of `src` are looked and the null terminating byte is **excluded**.

类似于utf8size，不同之处在于src中最多只查找n个字节，并且不包含null结束字节。

```
size_t utf8spn(const void *src, const void *accept);
```

Number of utf8 codepoints in the utf8 string `src` that consists entirely
of utf8 codepoints from the utf8 string `accept`.

utf8 字符串 src 开头有多少个字符都含有字符串 accept中的字符。

```
void *utf8str(const void *haystack, const void *needle);
```

The position of the utf8 string `needle` in the utf8 string `haystack`.

utf8 字符串 haystack 中 utf8 字符串needle的位置。

```
void *utf8casestr(const void *haystack, const void *needle);
```

The position of the utf8 string `needle` in the utf8 string `haystack`, case insensitive.

utf8 字符串 haystack 中 utf8 字符串needle的位置，不区分大小写。

```
void *utf8valid(const void *str);
```

Return 0 on success, or the position of the invalid utf8 codepoint on failure.

成功时返回 0，失败时返回无效 utf8 代码点的位置。

```
void *utf8nvalid(const void *str, size_t n);
```

Similar to `utf8valid`, except that only at most `n` bytes of `src` are looked.

与 utf8valid 类似，只是最多只查找 n 字节的 src。

```
int utf8makevalid(void *str, utf8_int32_t replacement);
```

Return 0 on success. Makes the `str` valid by replacing invalid sequences with the 1-byte `replacement` codepoint.

成功返回 0。通过用 1 字节replacement代码点替换无效序列使 str 有效。

```
void *utf8codepoint(const void *str, utf8_int32_t *out_codepoint);
```

Sets out_codepoint to the current utf8 codepoint in `str`, and returns the address of the next utf8 codepoint after the current one in `str`.

将 out_codepoint 设置为 str 中的当前 utf8 代码点，并返回 str 中当前代码点之后的下一个 utf8 代码点的地址。

```
void *utf8rcodepoint(const void *str, utf8_int32_t *out_codepoint);
```

Sets out_codepoint to the current utf8 codepoint in `str`, and returns the address of the previous utf8 codepoint before the current one in `str`.

将 out_codepoint 设置为 str 中的当前 utf8 代码点，并返回 str 中当前代码点之前的上一个 utf8 代码点的地址。

```
size_t utf8codepointsize(utf8_int32_t chr);
```

Returns the size of the given codepoint in bytes.

返回给定代码点的大小（以字节为单位）

```
void *utf8catcodepoint(void *utf8_restrict str, utf8_int32_t chr, size_t n);
```

Write a codepoint to the given string, and return the address to the next place after the written codepoint. Pass how many bytes left in the buffer to n. If there is not enough space for the codepoint, this function returns null.

将代码点写入给定的字符串，并将地址返回到写入代码点之后的下一个位置。将缓冲区中剩余的字节数传递给 n。如果代码点没有足够的空间，则此函数返回 null。

```
int utf8islower(utf8_int32_t chr);
```

Returns 1 if the given character is lowercase, or 0 if it is not.

如果给定字符是小写，则返回 1，否则返回 0。

```
int utf8isupper(utf8_int32_t chr);
```

Returns 1 if the given character is uppercase, or 0 if it is not.

如果给定字符是大写，则返回 1，否则返回 0。

```
void utf8lwr(void *utf8_restrict str);
```

Transform the given string into all lowercase codepoints.

将给定的字符串转换为所有小写代码点。

```
void utf8upr(void *utf8_restrict str);
```

Transform the given string into all uppercase codepoints.

将给定的字符串转换为所有大写代码点。

```
utf8_int32_t utf8lwrcodepoint(utf8_int32_t cp);
```

Make a codepoint lower case if possible.

如果可能，将代码点设为小写。

```
utf8_int32_t utf8uprcodepoint(utf8_int32_t cp);
```

Make a codepoint upper case if possible.

如果可能，将代码点设为大写。
