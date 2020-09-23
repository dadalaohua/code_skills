# `#pragma message string`

Prints string as a compiler message on compilation.  The message is informational only, and is neither a compilation warning nor an error.  Newlines can be included in the string by using the ‘\n’ escape sequence.
```c
#pragma message "Compiling " __FILE__ "..."
```
string may be parenthesized, and is printed with location information.  For example,
```c
#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

TODO(Remember to fix this)
```
prints ‘/tmp/file.c:4: note: #pragma message: TODO - Remember to fix this’.

https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html#Diagnostic-Pragmas
