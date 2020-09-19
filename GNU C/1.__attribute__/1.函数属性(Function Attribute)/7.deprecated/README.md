# `__attribute__((section("deprecated")))` 函数属性
# GNU

The `deprecated` attribute results in a warning if the function is used anywhere in the source file.  This is useful when identifying functions that are expected to be removed in a future version of a program.  The warning also includes the location of the declaration of the deprecated function, to enable users to easily find further information about why the function is deprecated, or what they should do instead.  Note that the warnings only occurs for uses:      

```c
          int old_fn () __attribute__ ((deprecated));
          int old_fn ();
          int (*fn_ptr)() = old_fn;
     
```

​     

results in a warning on line 3 but not line 2.      

The `deprecated` attribute can also be used for variables and types (see [Variable Attributes](https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Variable-Attributes.html#Variable-Attributes), see [Type Attributes](https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Type-Attributes.html#Type-Attributes).)      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM
This function attribute indicates that a function exists but the compiler must generate a warning if the deprecated function     is used.

### Note

This function attribute is a GNU compiler extension that the ARM® compiler          supports.

In GNU mode, this attribute takes an optional string parameter to appear          in the message, `__attribute__((deprecated("message")))`

## Example

```c
int Function_Attributes_deprecated_0(int b) __attribute__((deprecated));
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124974790.htm

1、此函数属性指示存在某个函数，但如果使用了 deprecated 函数，则编译器必须生成警告。
2、这个函数属性是ARM®编译器支持的GNU编译器扩展。
3、在GNU模式下，这个属性接受一个可选的字符串参数来显示在消息中，即:

```c
__attribute__((deprecated("message")))
```
4、例程
```c
int Function_Attributes_deprecated_0(int b) __attribute__((deprecated));
```

`__attribute__((section("deprecated")))`
用于表示该函数已弃用