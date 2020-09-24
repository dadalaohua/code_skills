# `__attribute__((noinline))` constant variable attribute

# ARM

The `noinline` variable attribute prevents     the compiler from making any use of a constant data value for optimization     purposes, without affecting its placement in the object.

You can use this feature for patchable constants, that is, data that is        later patched to a different value. It is an error to try to use such constants in a context        where a constant value is required. For example, an array dimension.

## Example

```c
__attribute__((noinline)) const int m = 1;
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124981967.htm