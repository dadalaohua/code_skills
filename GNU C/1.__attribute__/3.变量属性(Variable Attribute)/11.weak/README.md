# `__attribute__((weak))` variable attribute

# ARM

The declaration of a weak variable is permitted, and acts in a similar way to       `__weak`.

- In GNU mode:

  ```c
  extern int Variable_Attributes_weak_1 __attribute__((weak));
  ```

- The equivalent in non-GNU mode is:

  ```c
  __weak int Variable_Attributes_weak_compare;
  ```

### Note

The `extern` qualifier is required in GNU mode. In non-GNU mode the compiler assumes that if the variable is not `extern` then it is treated like any other non weak variable.

### Note

This variable attribute is a GNU compiler extension that the ARM compiler supports.

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124983745.htm