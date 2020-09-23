# Diagnostic Pragmas

GCC allows the user to selectively enable or disable certain types of diagnostics, and change the kind of the diagnostic.  For example, a project’s policy might require that all sources compile with -Werror but certain files might have exceptions allowing specific types of warnings.  Or, a project might selectively enable diagnostics and treat them as errors depending on which preprocessor macros are defined.

https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html#Diagnostic-Pragmas