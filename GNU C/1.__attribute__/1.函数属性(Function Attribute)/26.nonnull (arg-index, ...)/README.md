# `__attribute__((section("nonnull")))` 函数属性
# GNU

```
nonnull (`arg-index`, ...)
```

The `nonnull` attribute specifies that some function parameters should be non-null pointers.  For instance, the declaration:      

```c
          extern void *
          my_memcpy (void *dest, const void *src, size_t len)
          	__attribute__((nonnull (1, 2)));
     
```

causes the compiler to check that, in calls to `my_memcpy`, arguments dest and src are non-null.  If the compiler determines that a null pointer is passed in an argument slot marked as non-null, and the -Wnonnull option is enabled, a warning is issued.  The compiler may also choose to make optimizations based on the knowledge that certain function arguments will not be null.      

If no argument index list is given to the `nonnull` attribute, all pointer arguments are marked as non-null.  To illustrate, the following declaration is equivalent to the previous example:      

```c
          extern void *
          my_memcpy (void *dest, const void *src, size_t len)
          	__attribute__((nonnull));
```

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes

# ARM

This function attribute specifies function parameters that are not supposed to be null pointers. This enables the compiler to generate a warning on encountering such a parameter.

### Syntax

```
__attribute__((nonnull[(arg-index, ...)]))
```

Where `[(arg-index, ...)]` denotes an optional argument index list.

If no argument index list is specified, all pointer arguments are marked as nonnull.

### Note

The argument index list is 1-based, rather than 0-based.

## Examples

The following declarations are equivalent:

```c
void * my_memcpy (void *dest, const void *src, size_t len) __attribute__((nonnull (1, 2)));
void * my_memcpy (void *dest, const void *src, size_t len) __attribute__((nonnull));
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124976631.htm

nonnull (arg-index, ...),参数不能为空

my_memcpy的第一个和第二个参数不能为空,注意是指向空,就是不能为空指针