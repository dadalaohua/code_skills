# 计算一个数里位被置1的个数(并行的)

计算一个数里位被置1的个数(并行的)
```
unsigned int v; // count the number of bits set in v
                // 计算变量v的二进制中1的个数，待检测的数(32位)
unsigned int c; // c accumulates the total bits set in v
                // 保存计算的结果，位被置1的总数
static const int S[] = {1, 2, 4, 8, 16}; // Magic Binary Numbers// 参照表1
static const int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF}; //参照表2

c = v - ((v >> 1) & B[0]);
c = ((c >> S[1]) & B[1]) + (c & B[1]);
c = ((c >> S[2]) + c) & B[2];
c = ((c >> S[3]) + c) & B[3];
c = ((c >> S[4]) + c) & B[4];
```
B数组的二进制显示为: 
```
B[0] = 0x55555555 = 01010101 01010101 01010101 01010101
B[1] = 0x33333333 = 00110011 00110011 00110011 00110011
B[2] = 0x0F0F0F0F = 00001111 00001111 00001111 00001111
B[3] = 0x00FF00FF = 00000000 11111111 00000000 11111111
B[4] = 0x0000FFFF = 00000000 00000000 11111111 11111111
```
通过添加两个魔数数组B和S，就能够扩展这个方法，以适应位长更多的整数类型。如果有k位的话，那么我们只需要把数组S和B扩展到ceil(lg(k))个元素就好，同时添加对应数量的计算c的表达式。对于32位长度的v来说，一共需要16次操作。

然而对于计算32位整型数来说，最好的计算方法下面这种：

```
v = v - ((v >> 1) & 0x55555555);                    // reuse input as temporary
                                                    // 将输入变量作为临时变量重复使用	
v = (v & 0x33333333) + ((v >> 2) & 0x33333333);     // temp
                                                    // 临时变量
c = ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
                                                    // 计算结果
```
这种计算方法只需要12次操作，虽然和上面查表的方法差不多，但是却能够节省了内存和避免了潜在的缓存未命中而导致的额外操作。这是在并行计算方法和之前使用乘法的那种方法（在64位架构下，二进制位中1的个数那一小节中）之间的结合，然而这个方法却不需要64位架构的指令。每个比特中的1统计可以并行的计算，最终的结果计算是通过乘以0x1010101后右移24位来得出的。

这个方法还有一个推广，可以计算长度多达128位的整型数(128位整型的数据类型使用T来代替)，如下： 

```
v = v - ((v >> 1) & (T)~(T)0/3);                           // temp
v = (v & (T)~(T)0/15*3) + ((v >> 2) & (T)~(T)0/15*3);      // temp
v = (v + (v >> 4)) & (T)~(T)0/255*15;                      // temp
c = (T)(v * ((T)~(T)0/255)) >> (sizeof(T) - 1) * CHAR_BIT; // count
```

在[Ian Ashdown’s nice newsgroup post](http://groups.google.com/groups?q=reverse+bits&num=100&hl=en&group=comp.graphics.algorithms&imgsafe=off&safe=off&rnum=2&ic=1&selm=4fulhm%248dn%40atlas.uniserve.com)还可以看到更多关于计算二进制位中1个数（也被人称为sideways addition）的相关信息。

2005年12月14日，Charlie Gordon提出了一种方法，可以让纯平行计算的版本减少一次操作。2005年12月30日，Don Clugston在此之上又优化掉了3次操作。

2006年1月8日，Eric Cole指出了我在按照Don的建议修改本文时留下的一处显示错误。

2006年11月17日，Eric提出了最好计算方法的可变位长推广方案。

2007年4月5日，Al Williams发现我在第一个方法中留下了一行无用的代码。

***

### Counting bits set, in parallel

```
unsigned int v; // count bits set in this (32-bit value)
unsigned int c; // store the total here
static const int S[] = {1, 2, 4, 8, 16}; // Magic Binary Numbers
static const int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

c = v - ((v >> 1) & B[0]);
c = ((c >> S[1]) & B[1]) + (c & B[1]);
c = ((c >> S[2]) + c) & B[2];
c = ((c >> S[3]) + c) & B[3];
c = ((c >> S[4]) + c) & B[4];
```

The B array, expressed as binary, is:

```
B[0] = 0x55555555 = 01010101 01010101 01010101 01010101
B[1] = 0x33333333 = 00110011 00110011 00110011 00110011
B[2] = 0x0F0F0F0F = 00001111 00001111 00001111 00001111
B[3] = 0x00FF00FF = 00000000 11111111 00000000 11111111
B[4] = 0x0000FFFF = 00000000 00000000 11111111 11111111
```

We can adjust the method for larger integer sizes by continuing with  the patterns for the *Binary Magic Numbers,* B and S.   If there are k bits, then we need the arrays S and B to be ceil(lg(k))  elements long, and we must compute the same number of expressions for c as S or B are long.  For a 32-bit v, 16 operations are used.

The best method for counting bits in a 32-bit integer v is the following:

```
v = v - ((v >> 1) & 0x55555555);                    // reuse input as temporary
v = (v & 0x33333333) + ((v >> 2) & 0x33333333);     // temp
c = ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
```



The best bit counting method takes only 12 operations,  which is the same as the lookup-table method,  but avoids the memory and potential cache misses of a table.   It is a hybrid between the purely parallel method above and the earlier methods using multiplies (in the section on counting bits  with 64-bit instructions), though it doesn't use 64-bit instructions. The counts of bits set in the bytes is done in parallel, and the sum  total of the bits set in the bytes is computed by multiplying by 0x1010101 and shifting right 24 bits.

A generalization of the best bit counting method to integers  of bit-widths upto 128 (parameterized by type T) is this:

```
v = v - ((v >> 1) & (T)~(T)0/3);                           // temp
v = (v & (T)~(T)0/15*3) + ((v >> 2) & (T)~(T)0/15*3);      // temp
v = (v + (v >> 4)) & (T)~(T)0/255*15;                      // temp
c = (T)(v * ((T)~(T)0/255)) >> (sizeof(T) - 1) * CHAR_BIT; // count
```



See [  Ian Ashdown's nice newsgroup post](http://groups.google.com/groups?q=reverse+bits&num=100&hl=en&group=comp.graphics.algorithms&imgsafe=off&safe=off&rnum=2&ic=1&selm=4fulhm%248dn%40atlas.uniserve.com) for more information on counting the number of bits set (also known as *sideways addition*). The best bit counting method was brought to my attention on October 5, 2005  by [Andrew Shapira](http://onezero.org/);  he found it in pages 187-188 of [Software  Optimization Guide for AMD Athlon™ 64 and Opteron™ Processors](http://www.amd.com/us-en/assets/content_type/white_papers_and_tech_docs/25112.PDF). Charlie Gordon suggested a way to shave off one operation from the  purely parallel version on December 14, 2005, and Don Clugston trimmed three more from it on December 30, 2005.  I made a typo with Don's suggestion that  Eric Cole spotted on January 8, 2006.  Eric later suggested the  arbitrary bit-width generalization to the best method on November 17, 2006.  On April 5, 2007, Al Williams observed that I had a line of dead code at the  top of the first method.

http://graphics.stanford.edu/~seander/bithacks.html