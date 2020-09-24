# `__attribute__((visibility("visibility_type")))` variable attribute

# ARM

This variable attribute affects the visibility of ELF symbols.

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

You can apply this attribute to functions and variables in C and C++. In C++, you can also apply it to `class`, `struct`, `union`, and `enum` types, and `namespace` declarations.

## Example

```c
int i __attribute__((visibility("hidden")));
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124983511.htm