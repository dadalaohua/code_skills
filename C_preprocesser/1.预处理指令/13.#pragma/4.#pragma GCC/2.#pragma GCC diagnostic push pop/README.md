# `#pragma GCC diagnostic push`
# `#pragma GCC diagnostic pop`

Causes GCC to remember the state of the diagnostics as of each `push`, and restore to that point at each `pop`.  If a `pop` has no matching `push`, the command-line options are restored.

```c
#pragma GCC diagnostic error "-Wuninitialized"
  foo(a);                       /* error is given for this one */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
  foo(b);                       /* no diagnostic for this one */
#pragma GCC diagnostic pop
  foo(c);                       /* error is given for this one */
#pragma GCC diagnostic pop
  foo(d);                       /* depends on command-line options */
```

https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html#Diagnostic-Pragmas