# __builtin_va_arg_pack() 和 __builtin_va_arg_pack_len() 的使用

## 个人理解

builtin_va_arg_pack() 表示不定参数中所有的匿名参数，

builtin_va_arg_pack_len() 表示不定参数中所有的匿名参数的数量。

```c
__extern_always_inline int myprintf (const char *format, ...)
{
    int len = __builtin_va_arg_pack_len();
    printf ("len %d\n", len);
    printf (format, __builtin_va_arg_pack());
    return 0;
}
```

这两个内置函数(built-in function)需要放在头文件中，并且是内联函数(inline function)

## 资料

 **__builtin_va_arg_pack** *()*

这个内置函数表示内联函数的所有匿名参数。它只能用在总是内联的内联函数中，从不作为单独的函数编译，例如那些使用`__attribute__ ((__always_inline__))`或`__attribute__ ((__gnu_inline__))`extern 内联函数。它必须只作为最后一个参数传递给其他一些具有可变参数的函数。当不希望使用预处理器宏时，这对于为可变参数的函数编写小型封装内联是非常有用的

```c
extern int myprintf (FILE *f, const char *format, ...);
extern inline __attribute__ ((__gnu_inline__)) int
myprintf (FILE *f, const char *format, ...)
{
  int r = fprintf (f, "myprintf: ");
  if (r < 0)
    return r;
  int s = fprintf (f, format, __builtin_va_arg_pack ());
  if (s < 0)
    return s;
  return r + s;
}
```



*size_t* **__builtin_va_arg_pack_len** *()*

这个内置函数返回内联函数的匿名参数的数量。它只能用在总是内联的内联函数中，从不作为单独的函数编译，例如那些使用 `__attribute__ ((__always_inline__))` 或 `__attribute__ ((__gnu_inline__))` extern 内联函数。例如下面为优化的代码做了开放参数的链接或运行时检查。

```c
#ifdef __OPTIMIZE__
extern inline __attribute__((__gnu_inline__)) int
myopen (const char *path, int oflag, ...)
{
  if (__builtin_va_arg_pack_len () > 1)
    warn_open_too_many_arguments ();

  if (__builtin_constant_p (oflag))
    {
      if ((oflag & O_CREAT) != 0 && __builtin_va_arg_pack_len () < 1)
        {
          warn_open_missing_mode ();
          return __open_2 (path, oflag);
        }
      return open (path, oflag, __builtin_va_arg_pack ());
    }

  if (__builtin_va_arg_pack_len () < 1)
    return __open_2 (path, oflag);

  return open (path, oflag, __builtin_va_arg_pack ());
}
#endif
```

https://blog.csdn.net/u012028275/article/details/119046316

https://gcc.gnu.org/onlinedocs/gcc/Constructing-Calls.html#Constructing-Calls



## 参考

参考glibc中io/bits/fcntl2.h

```c
__fortify_function int
open (const char *__path, int __oflag, ...)
{
  if (__va_arg_pack_len () > 1)
    __open_too_many_args ();

  if (__builtin_constant_p (__oflag))
    {
      if (__OPEN_NEEDS_MODE (__oflag) && __va_arg_pack_len () < 1)
	{
	  __open_missing_mode ();
	  return __open_2 (__path, __oflag);
	}
      return __open_alias (__path, __oflag, __va_arg_pack ());
    }

  if (__va_arg_pack_len () < 1)
    return __open_2 (__path, __oflag);

  return __open_alias (__path, __oflag, __va_arg_pack ());
}
```

其中

```c
#ifdef __extern_always_inline
# define __fortify_function __extern_always_inline __attribute_artificial__
#endif
```

