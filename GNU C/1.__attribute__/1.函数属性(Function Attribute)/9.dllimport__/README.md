# `__attribute__((dllimport))` 函数属性

# GNU

On Microsoft Windows and Symbian OS targets, the `dllimport` attribute causes the compiler to reference a function or variable via a global pointer to a pointer that is set up by the DLL exporting the symbol.  The attribute implies `extern` storage.  On Microsoft Windows targets, the pointer name is formed by combining `_imp__` and the function or variable name.      

You can use `__declspec(dllimport)` as a synonym for `__attribute__ ((dllimport))` for compatibility with other compilers.      

Currently, the attribute is ignored for inlined functions.  If the attribute is applied to a symbol *definition*, an error is reported.  If a symbol previously declared `dllimport` is later defined, the attribute is ignored in subsequent references, and a warning is emitted.  The attribute is also overridden by a subsequent declaration as `dllexport`.      

When applied to C++ classes, the attribute marks non-inlined member functions and static data members as imports.  However, the attribute is ignored for virtual methods to allow creation of vtables using thunks.      

On the SH Symbian OS target the `dllimport` attribute also has another affect—it can cause the vtable and run-time type information for a class to be exported.  This happens when the class has a dllimport'ed constructor or a non-inline, non-pure virtual function and, for either of those two conditions, the class also has a inline constructor or destructor and has a key function that is defined in the current translation unit.      

For Microsoft Windows based targets the use of the `dllimport` attribute on functions is not necessary, but provides a small performance benefit by eliminating a thunk in the DLL.  The use of the `dllimport` attribute on imported variables was required on older versions of the GNU linker, but can now be avoided by passing the --enable-auto-import switch to the GNU linker.  As with functions, using the attribute for a variable eliminates a thunk in the DLL.      

One drawback to using this attribute is that a pointer to a function or variable marked as `dllimport` cannot be used as a constant address.  On Microsoft Windows targets, the attribute can be disabled for functions by setting the -mnop-fun-dllimport flag.      

https://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html#Function-Attributes