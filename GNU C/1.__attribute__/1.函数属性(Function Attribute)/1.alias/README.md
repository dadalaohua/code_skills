# `__attribute__((section("alias")))` 函数属性
# GNU

```
alias ("`target`")
```

The `alias` attribute causes the declaration to be emitted as an alias for another symbol, which must be specified.  For instance,      

```c
          void __f () { /* Do something. */; }
          void f () __attribute__ ((weak, alias ("__f")));
     
```

declares `f` to be a weak alias for `__f`.  In C++, the mangled name for the target must be used.  It is an error if `__f` is not defined in the same translation unit.      

Not all target machines support this attribute.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

This function attribute enables you to specify multiple aliases for a function.

Aliases must be defined in the same translation unit as the original function.

### Note

You cannot specify aliases in block scope. The compiler ignores aliasing attributes attached to local function definitions and treats the function definition as a normal local definition.

In the output object file, the compiler replaces alias calls with a call to the original function name, and emits the alias alongside the original name. For example:

```c
static int oldname(int x, int y) {
     return x + y;
}
static int newname(int x, int y) __attribute__((alias("oldname")));
int caller(int x, int y) {
     return oldname(x,y) + newname(x,y);
}
```

This code compiles to:

```
AREA ||.text||, CODE, READONLY, ALIGN=2
newname                  ; Alternate entry point
oldname PROC
     MOV      r2,r0
     ADD      r0,r2,r1
     BX       lr
     ENDP
caller PROC
     PUSH     {r4,r5,lr}
     MOV      r3,r0
     MOV      r4,r1
     MOV      r1,r4
     MOV      r0,r3
     BL       oldname
     MOV      r5,r0
     MOV      r1,r4
     MOV      r0,r3
     BL       oldname
     ADD      r0,r0,r5
     POP      {r4,r5,pc}
     ENDP
```

### Note

This function attribute is a GNU compiler extension that the        ARM compiler supports. 

### Note

Variables names might also be aliased using the        corresponding variable attribute `__attribute__((alias))`.      

### Syntax

```
return-type newname([argument-list])              __attribute__((alias("oldname"))); 
```

Where:

- `oldname`

  is the name of the function to be aliased

- `newname`

  is the new name of the aliased function.

## Example

```c
#include <stdio.h>
void foo(void)
{
    printf("%s\n", __FUNCTION__);
}
void bar(void) __attribute__((alias("foo")));
void gazonk(void)
{
    bar(); // calls foo
}
```
https://www.keil.com/support/man/docs/armcc/armcc_chr1359124973698.htm

1、`__attribute__((alias))`  函数属性使你能够为一个函数指定多个别名。
2、需要注意的是别名必须和原函数具有相同的类型
3、不能在块范围内指定别名。编译器忽略附加到局部函数定义的别名属性，并将函数定义视为普通的局部定义。
4、在输出对象文件中，编译器将别名调用替换为对原始函数名的调用，并在原始名称旁边发出别名。例如:
```c
static int oldname(int x, int y) {
     return x + y;
}
static int newname(int x, int y) __attribute__((alias("oldname")));
int caller(int x, int y) {
     return oldname(x,y) + newname(x,y);
}
```
编译输出文件为
```
AREA ||.text||, CODE, READONLY, ALIGN=2
newname                  ; Alternate entry point
oldname PROC
     MOV      r2,r0
     ADD      r0,r2,r1
     BX       lr
     ENDP
caller PROC
     PUSH     {r4,r5,lr}
     MOV      r3,r0
     MOV      r4,r1
     MOV      r1,r4
     MOV      r0,r3
     BL       oldname
     MOV      r5,r0
     MOV      r1,r4
     MOV      r0,r3
     BL       oldname
     ADD      r0,r0,r5
     POP      {r4,r5,pc}
     ENDP
```
5、这个函数属性是ARM编译器支持的GNU编译器扩展。
6、变量名称也可以使用这个属性扩展
7、语法
```
return-type newname([argument-list]) __attribute__((alias("oldname")));
```
oldname：需要另起别名的函数
newname：新的别名
示例
```c
#include <stdio.h>
void foo(void)
{
    printf("%s\n", __FUNCTION__);
}
void bar(void) __attribute__((alias("foo")));
void gazonk(void)
{
    bar(); // calls foo
}
```

