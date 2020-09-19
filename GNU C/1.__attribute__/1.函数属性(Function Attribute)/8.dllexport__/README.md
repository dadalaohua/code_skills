# `__attribute__((dllexport))` 函数属性

# GNU

On Microsoft Windows targets and Symbian OS targets the `dllexport` attribute causes the compiler to provide a global pointer to a pointer in a DLL, so that it can be referenced with the `dllimport` attribute.  On Microsoft Windows targets, the pointer name is formed by combining `_imp__` and the function or variable name.      

You can use `__declspec(dllexport)` as a synonym for `__attribute__ ((dllexport))` for compatibility with other compilers.      

On systems that support the `visibility` attribute, this attribute also implies “default” visibility, unless a `visibility` attribute is explicitly specified.  You should avoid the use of `dllexport` with “hidden” or “internal” visibility; in the future GCC may issue an error for those cases.      

Currently, the `dllexport` attribute is ignored for inlined functions, unless the -fkeep-inline-functions flag has been used.  The attribute is also ignored for undefined symbols.      

When applied to C++ classes, the attribute marks defined non-inlined member functions and static data members as exports.  Static consts initialized in-class are not marked unless they are also defined out-of-class.      

For Microsoft Windows targets there are alternative methods for including the symbol in the DLL's export table such as using a .def file with an `EXPORTS` section or, with GNU ld, using the --export-all linker flag.       

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes