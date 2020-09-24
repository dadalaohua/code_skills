# `__attribute__((used))` variable attribute

# ARM

This variable attribute informs the compiler that a static variable is to be retained     in the object file, even if it is unreferenced.

## Usage

Static variables marked as used are emitted to a single section, in the order they are        declared. You can specify the section that variables are placed in using            `__attribute__((section("name")))`.

Data marked with `__attribute__((used)) `is tagged in the object file to        avoid removal by linker unused section removal.

### Note

This variable attribute is a GNU compiler extension that the ARM compiler supports.      

### Note

Static functions can also be marked as used using          `__attribute__((used))`.      

You can use `__attribute__((used))` to build tables in the object.

## Example

```c
static int lose_this = 1;
static int keep_this __attribute__((used)) = 2;     // retained in object file
static int keep_this_too __attribute__((used)) = 3; // retained in object file
```

https://www.keil.com/support/man/docs/armcc/armcc_chr1359124983230.htm