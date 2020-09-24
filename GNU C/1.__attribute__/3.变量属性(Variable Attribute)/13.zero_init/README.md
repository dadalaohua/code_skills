# `__attribute__((zero_init))` variable attribute

# ARM

The `section` attribute specifies that a variable must be placed in a     particular data section. The `zero_init` attribute specifies that a variable with     no initializer is placed in a ZI data section. If an initializer is specified, an error is     reported.

## Example

```c
__attribute__((zero_init)) int x;                    /* in section ".bss" */
__attribute__((section("mybss"), zero_init)) int y;  /* in section "mybss" */
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124984244.htm