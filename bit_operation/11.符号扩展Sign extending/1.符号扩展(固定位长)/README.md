# 符号扩展(固定位长)

符号扩展(sign extension)是系统内建的自动机制，比如char型和int型之间的互相转换。但当你有一个带符号长度为b位的补码数x，你想要把x转换为长度超过b位的int型时，这个机制就不能满足需求了。诚然，简单赋值对于正数x是有效的，但是负数x都不行了，因为符号位需要被扩展。举个例子来简单说明什么是符号扩展(sign extension)，我们现在有一个4位长的变量来保存数，对于-3来说，保存下来的补码形式为1101。如果我们有8位长，那么-3保存下来的补码形式为11111101。当尝试将一个4位长的数转换为更多位长的数时，符号位会向左复制填充空出来的位，直到填满。在C语言中，使用结构体或联合体的位域很容易实现固定长度的符号扩展。比如，将长度为5位的数转换成整型。
```
int x; // convert this from using 5 bits to a full int
       // 变量x中保存长度为5位的数
int r; // resulting sign extended number goes here
       // 转换的结果保存在变量r中
struct {signed int x:5;} s;
r = s.x = x;
```
下面这个是用C++的模板方法来实现. 
```
template <typename T, unsigned B>
inline T signextend(const T x)
{
  struct {T x:B;} s;
  return s.x = x;
}

int r = signextend<signed int,5>(x);  // sign extend 5 bit number x to r
                                      // 从5位长的数x转换到r
```
2005年5月2日，John Byrd找到了一处由于html格式问题导致的样式显示错误。
2006年3月4日，Pat Wood指出ANSI C标准规定带符号的位域必须要用关键字“signed”来显式地指定其带符号，否则其符号位是未定义的。
***

### Sign extending from a constant bit-width

Sign extension is automatic for built-in types, such as chars and ints. But suppose you have a signed two's complement number, x, that is stored  using only b bits.  Moreover, suppose you want to convert x to an int, which has more than b bits.  A simple copy will work if x is positive, but if negative, the sign must be extended.  For example, if we have only 4 bits to store a number, then -3 is represented as 1101  in binary.  If we have 8 bits, then -3 is 11111101.  The most-significant bit of the 4-bit representation is replicated sinistrally to fill in the destination when we convert to a representation with more bits;  this is sign extending.   In C, sign extension from a constant bit-width is trivial, since bit  fields may be specified in structs or unions.   For example, to convert from 5 bits to an full integer:

```
int x; // convert this from using 5 bits to a full int
int r; // resulting sign extended number goes here
struct {signed int x:5;} s;
r = s.x = x;
```

The following is a C++ template function that uses the same  language feature to convert from B bits in one operation (though  the compiler is generating more, of course).

```
template <typename T, unsigned B>
inline T signextend(const T x)
{
  struct {T x:B;} s;
  return s.x = x;
}

int r = signextend<signed int,5>(x);  // sign extend 5 bit number x to r
```



John Byrd caught a typo in the code (attributed to html formatting) on May 2, 2005.  On March 4, 2006, Pat Wood pointed out that the ANSI C  standard requires that the bitfield have the keyword "signed" to be signed;  otherwise, the sign is undefined.

http://graphics.stanford.edu/~seander/bithacks.html
