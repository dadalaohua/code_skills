# `__attribute__((section("name")))` variable attribute

# ARM

The `section` attribute specifies that a variable must be placed in a particular data section. 

Normally, the ARM compiler places the objects it generates in sections like     `.data` and `.bss`. However, you might require additional data sections or you might want a variable to appear in a special section, for example, to        map to special hardware.

If you use the `section` attribute, read-only variables are placed in RO data sections, read-write variables are placed in RW data sections unless you use the          `zero_init` attribute. In this case, the variable is placed in a ZI        section. 

### Note

This variable attribute is a GNU compiler extension that the ARM compiler supports.      

## Example

```c
/* in RO section */
const int descriptor[3] __attribute__((section ("descr"))) = { 1,2,3 };
/* in RW section */
long long rw_initialized[10] __attribute__((section ("INITIALIZED_RW"))) = {5};
/* in RW section */
long long rw[10] __attribute__((section ("RW")));
/* in ZI section */
long long altstack[10] __attribute__((section ("STACK"), zero_init));
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124982450.htm