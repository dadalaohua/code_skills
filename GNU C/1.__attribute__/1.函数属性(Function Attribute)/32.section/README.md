# `__attribute__((section("name")))` 函数属性
# GNU

Normally, the compiler places the code it generates in the `text` section.  Sometimes, however, you need additional sections, or you need certain particular functions to appear in special sections.  The `section` attribute specifies that a function lives in a particular section.  For example, the declaration:      

```c
          extern void foobar (void) __attribute__ ((section ("bar")));
     
```

puts the function `foobar` in the `bar` section.      

Some file formats do not support arbitrary sections so the `section` attribute is not available on all platforms.  If you need to map the entire contents of a module to a particular section, consider using the facilities of the linker instead.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

The `section` function attribute enables you to place code in different sections of the image.

### Note
This function attribute is a GNU compiler extension that the ARM compiler supports. 

## Examples
In the following example, `Function_Attributes_section_0` is placed into the        RO section `new_section` rather than `.text`.
```c
void Function_Attributes_section_0 (void) 
    __attribute__((section ("new_section")));
void Function_Attributes_section_0 (void)
{
    static int aStatic =0;
    aStatic++;
}
```
In the following example, `section` function attribute overrides the `#pragma arm section` setting.

```c
#pragma arm section code="foo"
  int f2()
  {
      return 1;
  }                                  // into the 'foo' area
  __attribute__((section ("bar"))) int f3()
  {
      return 1;
  }                                  // into the 'bar' area
  int f4()
  {
      return 1;
  }                                  // into the 'foo' area
#pragma arm section
```
https://www.keil.com/support/man/docs/armcc/armcc_chr1359124977848.htm

1、section 函数属性使您能够将代码放置在镜像的不同部分中。
2、这个函数属性是ARM编译器支持的GNU编译器扩展。
3、例程
在下面的示例中，Function_Attributes_section_0 被放置到RO section new_section 中，而不是 .text 中。

```c
void Function_Attributes_section_0 (void) 
    __attribute__((section ("new_section")));
void Function_Attributes_section_0 (void)
{
    static int aStatic =0;
    aStatic++;
}
```
在下面的例子中，section 函数属性覆盖了 #pragma arm section 设置。
```c
#pragma arm section code="foo"
  int f2()
  {
      return 1;
  }                                  // into the 'foo' area
  __attribute__((section ("bar"))) int f3()
  {
      return 1;
  }                                  // into the 'bar' area
  int f4()
  {
      return 1;
  }                                  // into the 'foo' area
#pragma arm section
```



`__attribute__((section(“name”)))` function attribute
`__attribute__((section(“name”)))` 其作用是将作用的函数或数据放入指定名为"section_name"对应的段中

```c
static void __attribute((section("__TEXT,MySection" ))) myFun1(void){
print("");
}
```


可以通过命令查看代码段情况
```shell
objdump -h test_code.o
```

或者

```shell
readelf -S test_code.o 
```