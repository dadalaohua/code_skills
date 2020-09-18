# `__attribute__((section("deprecated")))` 函数属性
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