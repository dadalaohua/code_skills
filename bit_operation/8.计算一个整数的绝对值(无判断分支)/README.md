# 计算一个整数的绝对值(无判断分支) 

## 计算一个整数的绝对值(无判断分支)  
```
int v;           // we want to find the absolute value of v
                 // 我们希望算出变量v的绝对值
unsigned int r;  // the result goes here
                 // 结果保存在这里
int const mask = v >> sizeof(int) * CHAR_BIT - 1;

r = (v + mask) ^ mask;
```
一个简单的变形:
```
r = (v ^ mask) - mask;
```
有些CPU并不支持计算整数绝对值的指令（也可以说有些编译器没用上这些指令）。在有的机器上，分支判断操作非常昂贵，会消耗较多计算资源。在这些机器上，上面的表达式会比 `r = (v < 0) ? -(unsigned)v : v` 这种简单的实现更快一些，尽管他们的操作数都是相同的。

 

2003年3月7日，Augus Duggan指出1989 ANSI C标准指明带符号数右移的结构是由编译器实现时定义(implementation-defined)的，所以这个技巧有可能不会正常工作。同时，我也阅读了ANSI C标准，发现ANSI C并没有要求数值一定要以二补数（two’s complement，即补码）的形式表示出来，所以由于这个原因，上面的技巧（在一些极少部分仍使用一补数(one’s complement)的古董机器上）也有可能不工作。

 

2004年3月14日，Keith H. Duggar提出了上面的变形。这个版本比我一开始想出来的初始版本更好，`r=(+1|(v>>(sizeof(int)*CHAR_BIT-1)))*v`，其中有一次乘法是没用的。

 

不幸的是，2000年6月6日，这个技巧已经被Vladimir Yu Volkonsky在美国申请了专利，并且归属于[Sun公司的Microsystems](http://www.sun.com/)。 
 2006年8月13日，Yuriy Kaminskiy告诉我这个专利可能是无效的，因为这个技巧在申请专利之前就被人公开发表了，见1996年11月9日，由Agner Fog发表的[How to Optimize for the Pentium Processor](http://www.goof.com/pcg/doc/pentopt.txt)。Yuriy同时也提到这份文档在1997年被翻译成了俄语，所以Vladimir有可能阅读过。除此之外，The Internet Archive（网站时光倒流机器）网站也收录了这个老旧的链接。



2007年1月30日，Peter Kankowski给我分享了一个他的[发现](http://www.strchr.com/optimized_abs_function)。这来源于他在观察微软的Visual C++编译器的输出时的发现。这个技巧在这里被采用为最优解法。

(译者注，Peter发现了VC++的编译器有可能使用了之前那个被Sun公司专利保护的技巧，但在评论中也同时有人指出Sun公司的这个专利是无效的)

2007年12月6日，Hai Jin提出反对意见，算法的结果是带符号的，所以在计算最大的负数时，结果会依然是负的。

2008年4月15日，Andrew Shapira指出上面的那个简单实现的版本可能会溢出，需要一个`(unsigned)`来做强制类型转换；为了最大程度的兼容性，他提议使用`(v < 0) ? (1 + ((unsigned)(-1-v))) : (unsigned)v`。但是根据2008年7月9日的ISO C99标准，Vincent Lefèvre说服我删除了这个版本，因为即便是在非基于二补数的机器上，`-(unsigned)v`这条语句也会做我们希望他做的事情。在计算`-(signed)v`时，程序会通过将负数v增加`2**N`来得到无符号类型的数，这个数正好是v的补码表示形式，我们令U等于这个数。然后将U的符号取负，就能得出结果，有`-U=0-U=2**N-U=2**N-(v+2**N)=-v=abs(v)`。

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
