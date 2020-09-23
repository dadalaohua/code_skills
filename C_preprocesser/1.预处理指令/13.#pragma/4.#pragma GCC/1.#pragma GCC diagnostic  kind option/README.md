# `#pragma GCC diagnostic kind option`

Modifies the disposition of a diagnostic.  Note that not all diagnostics are modifiable; at the moment only warnings (normally controlled by ‘-W…’) can be controlled, and not all of them. Use -fdiagnostics-show-option to determine which diagnostics are controllable and which option controls them.

kind is ‘error’ to treat this diagnostic as an error, ‘warning’ to treat it like a warning (even if -Werror is in effect), or ‘ignored’ if the diagnostic is to be ignored. option is a double quoted string that matches the command-line option.

```c
#pragma GCC diagnostic warning "-Wformat"
#pragma GCC diagnostic error "-Wformat"
#pragma GCC diagnostic ignored "-Wformat"
```

Note that these pragmas override any command-line options.  GCC keeps track of the location of each pragma, and issues diagnostics according to the state as of that point in the source file.  Thus, pragmas occurring after a line do not affect diagnostics caused by that line.

https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html#Diagnostic-Pragmas