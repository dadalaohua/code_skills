# 将一个固定位数的整数进行扩展更大的位数的整数 

## 将一个固定位数的整数进行扩展更大的位数的整数
小整数向大整数的转换一般是cpu自动转换的，如将char转成int. 下面的例子是将5位宽的int转换成一个32位的int: 
```
int x; // 待转换的数
int r; // 结果
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

int r = signextend<signed int,5>(x); 
```

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
