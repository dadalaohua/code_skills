# 不定参数

函数如何实现不定参数：由于在C语言中没有函数重载，解决不定数目函数参数问题变得比较麻烦，即使采用C++，如果参数个数不能确定，也很难采用函数重载。对这种情况，提出了指针参数来解决问题。

type va_arg(va_list argptr, type);  
void va_end(va_list argptr);  
void va_start(va_list argptr, last_parm); 

（1）va_list 
定义了一个指针arg_ptr, 用于指示可选的参数.
（2）va_start(arg_ptr, argN)
使参数列表指针arg_ptr指向函数参数列表中的第一个可选参数，argN是位于第一个可选参数之前的固定参数, 或者说最后一个固定参数.如有一va
函数的声明是void va_test(char a, char b, char c, ...), 则它的固定参数依次是a,b,c, 最后一个固定参数argN为c, 因此就是va_start
(arg_ptr, c).
（3）va_arg(arg_ptr, type)
返回参数列表中指针arg_ptr所指的参数, 返回类型为type. 并使指针arg_ptr指向参数列表中下一个参数.返回的是可选参数, 不包括固定参数.
（4）va_end(arg_ptr)
清空参数列表, 并置参数指针arg_ptr无效.
（注：va在这里是variable-argument(可变参数)的意思.   这些宏定义在stdarg.h中,所以用到可变参数的程序应该包含这个头文件）

除此之外，我们还需要注意一个陷阱，即va_arg宏的第2个参数不能被指定为char、short或者float类型。《C和C++经典著作：C陷阱与缺陷》在可变参数函数传递时，因为char和short类型的参数会被提升为int类型，而float类型的参数会被提升为double类型 。 
