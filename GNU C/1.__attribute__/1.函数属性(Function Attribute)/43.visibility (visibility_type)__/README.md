# `__attribute__((visibility ("`visibility_type`"))` 函数属性

# GNU
```
visibility ("`visibility_type`")
```

The `visibility` attribute on ELF targets causes the declaration to be emitted with default, hidden, protected or internal visibility.      

```c
          void __attribute__ ((visibility ("protected")))
          f () { /* Do something. */; }
          int i __attribute__ ((visibility ("hidden")));
     
```

See the ELF gABI for complete details, but the short story is:           

- default

  Default visibility is the normal case for ELF.  This value is available for the visibility attribute to override other options that may change the assumed visibility of symbols.            

- hidden

  Hidden visibility indicates that the symbol will not be placed into the dynamic symbol table, so no other module (executable or shared library) can reference it directly.            

- internal

  Internal visibility is like hidden visibility, but with additional processor specific semantics.  Unless otherwise specified by the psABI, GCC defines internal visibility to mean that the function is *never* called from another module.  Note that hidden symbols, while they cannot be referenced directly by other modules, can be referenced indirectly via function pointers.  By indicating that a symbol cannot be called from outside the module, GCC may for instance omit the load of a PIC register since it is known that the calling function loaded the correct value.            

- protected

  Protected visibility indicates that the symbol will be placed in the dynamic symbol table, but that references within the defining module will bind to the local symbol.  That is, the symbol cannot be overridden by another module.      

Not all ELF targets support this attribute. 

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

This function attribute affects the visibility of ELF symbols.

### Note

This attribute is a GNU compiler extension that the ARM compiler supports.

### Syntax

```
__attribute__((visibility("visibility_type"))) 
```

Where `visibility_type` is one of the following:

- `default`

  The assumed visibility of symbols can be changed by other options. Default visibility overrides such changes. Default visibility corresponds to external linkage.

- `hidden`

  The symbol is not placed into the dynamic symbol table, so no other executable or shared library can directly reference it. Indirect references are possible using function pointers.

- `internal`

  Unless otherwise specified by the processor-specific Application Binary Interface (psABI), internal visibility means that the function is never called from another module.

- `protected`

  The symbol is placed into the dynamic symbol table, but references within the defining module bind to the local symbol. That is, the symbol cannot be overridden by another module.

## Usage

Except when specifying `default` visibility, this attribute is intended for use with declarations that would otherwise have external linkage.

You can apply this attribute to functions and variables in C and C++. In C++, it can also be applied to class, struct, union, and enum types, and namespace declarations.

## Example

```c
void __attribute__((visibility("internal"))) foo()
{
   ...
}
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124978628.htm

此函数属性影响 ELF 符号的可见性。

### Note

此属性是 ARM 编译器支持的 GNU 编译器扩展。

#### 语法

```
__attribute__((visibility("visibility_type")))
```

其中，`visibility_type` 是下列值之一：

- `default`

  假定的符号可见性可通过其他选项进行更改。缺省可见性将覆盖此类更改。缺省可见性与外部链接对应。

- `hidden`

  该符号不存放在动态符号表中，因此，其他可执行文件或共享库都无法直接引用它。使用函数指针可进行间接引用。

- `internal`

  除非由 *特定于处理器的应用二进制接口* (psABI) 指定，否则，内部可见性意味着不允许从另一模块调用该函数。

- `protected`

  该符号存放在动态符号表中，但定义模块内的引用将与局部符号绑定。也就是说，另一模块无法覆盖该符号。

#### 用法

除指定 `default` 可见性外，此属性都可与在这些情况下具有外部链接的声明结合使用。

您可在 C 和 C++ 中使用此属性。在 C++ 中，还可将它应用于类型、成员函数和命名空间声明。