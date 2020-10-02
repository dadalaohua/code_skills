# 计算一个整数的绝对值(无判断分支) 

## 计算一个整数的绝对值(无判断分支)  
```
int v;           // 待计算的值
unsigned int r;  // 结果
int const mask = v >> sizeof(int) * CHAR_BIT - 1;

r = (v + mask) ^ mask;
```
//或者
```
r = (v ^ mask) - mask;
```
有些cpu没有计算绝对值的指令，或者编译器不会使用机器的求绝对值的指令，使用分支判断的代价是相对比较高的，所以使用上面的方法会比用分支的判读的方法快， 例如下面是用判断分支`r = (v < 0) ? -(unsigned)v : v`
即使这个方法运算符的次数与上面的是一样的，这个的速度还是慢。

***

### Compute the integer absolute value (abs) without branching



```
int v;           // we want to find the absolute value of v
unsigned int r;  // the result goes here 
int const mask = v >> sizeof(int) * CHAR_BIT - 1;

r = (v + mask) ^ mask;
```

Patented variation:

```
r = (v ^ mask) - mask;
```

Some CPUs don't have an integer absolute value instruction (or the compiler fails to use them).  On machines where branching is expensive, the above expression can be faster than the obvious approach,  r = (v < 0) ? -(unsigned)v : v, even though the number of operations  is the same.

On March 7, 2003, Angus Duggan pointed out that the 1989 ANSI C  specification leaves the result of signed right-shift implementation-defined, so on some systems this hack might not work.  I've read that ANSI C does not require values to be represented as two's complement, so it may not work  for that reason as well (on a diminishingly small number of old machines  that still use one's complement). On March 14, 2004, Keith H. Duggar sent me the patented variation above; it is  superior to the one I initially came up with,  `r=(+1|(v>>(sizeof(int)*CHAR_BIT-1)))*v`,  because a multiply is not used.   Unfortunately, this method has been [ patented](http://patft.uspto.gov/netacgi/nph-Parser?Sect1=PTO2&Sect2=HITOFF&p=1&u=/netahtml/search-adv.htm&r=1&f=G&l=50&d=ptxt&S1=6073150&OS=6073150&RS=6073150) in the USA on June 6, 2000 by Vladimir Yu Volkonsky and  assigned to [Sun Microsystems](http://www.sun.com/).  On August 13, 2006, Yuriy  Kaminskiy told me that the patent is likely invalid because the method was published well before the patent was even filed, such as in  [How to Optimize for the Pentium Processor](http://www.goof.com/pcg/doc/pentopt.txt) by Agner Fog, dated November, 9, 1996.  Yuriy also  mentioned that this document was translated to Russian in 1997, which  Vladimir could have read.  Moreover, the Internet Archive also has an old  [link](http://web.archive.org/web/19961201174141/www.x86.org/ftp/articles/pentopt/PENTOPT.TXT) to it.  On January 30, 2007, Peter Kankowski shared with me an  [abs version](http://smallcode.weblogs.us/2007/01/31/microsoft-probably-uses-the-abs-function-patented-by-sun/)  he discovered that was inspired by Microsoft's Visual C++ compiler output.   It is featured here as the primary solution. On December 6, 2007, Hai Jin complained that the result was signed, so when computing the abs of the most negative value, it was still negative. On April 15, 2008 Andrew Shapira pointed out that the obvious approach could overflow, as it lacked an (unsigned) cast then;  for maximum portability he suggested `(v < 0) ? (1 + ((unsigned)(-1-v))) : (unsigned)v`.   But citing the ISO C99 spec on July 9, 2008,  Vincent Lefèvre convinced me to remove it becasue even on non-2s-complement machines -(unsigned)v  will do the right thing.  The evaluation of -(unsigned)v first converts the negative value of v to an unsigned by adding 2**N,  yielding a 2s complement representation of v's value that I'll call U.   Then, U is negated, giving the desired result,  -U = 0 - U = 2**N - U = 2**N - (v+2**N) = -v = abs(v).

http://graphics.stanford.edu/~seander/bithacks.html
