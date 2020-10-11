# 交换特定位(使用XOR) 

```
unsigned int i, j; // positions of bit sequences to swap
                   // 指定交换的位置
unsigned int n;    // number of consecutive bits in each sequence
                   // 区间的长度
unsigned int b;    // bits to swap reside in b
                   // 变量b中的二进制位需要交换
unsigned int r;    // bit-swapped result goes here
                   // 变量r存放位交换后的结果

unsigned int x = ((b >> i) ^ (b >> j)) & ((1U << n) - 1); // XOR temporary
                                                          // 异或操作的临时变量
r = b ^ ((x << i) | (x << j));

```
举一个 指定二进制位范围来交换数值 的例子，我们有b = 00101111（二进制形式），希望交换的位长度为n = 3，起始点是i = 1（从右往左数第2个位）的连续3个位，以及起点为j = 5的连续3个位；那么结果就会是r = 11100011(二进制)。

这个交换数值的技巧很像之前那个通用的异或交换的技巧，区别于这个技巧是用来操作特定的某些位。变量x中保存我们想要交换的两段二进制位值异或后的结果，然后用x与原来的值进行异或，便可以达到交换的效果。当然如果指定的范围溢出了的话，计算结果是未定义的。

2009年7月14日，Hallvard Furuseth建议我将1 << n 改成 1U << n，因为使用无符号整型可以防止移位操作覆盖掉了符号位。

***

### Swapping individual bits with XOR



```
unsigned int i, j; // positions of bit sequences to swap
unsigned int n;    // number of consecutive bits in each sequence
unsigned int b;    // bits to swap reside in b
unsigned int r;    // bit-swapped result goes here

unsigned int x = ((b >> i) ^ (b >> j)) & ((1U << n) - 1); // XOR temporary
r = b ^ ((x << i) | (x << j));
```

As an example of swapping ranges of bits suppose we have have b = **001**0**111**1  (expressed in binary) and we want to swap the n = 3 consecutive bits starting at i = 1 (the second bit from the right) with the 3 consecutive bits starting at j = 5; the result would be r =  **111**0**001**1 (binary).

This method of swapping is similar to the general purpose XOR swap trick, but intended for operating on individual bits.  The variable x  stores the result of XORing the pairs of bit values we want to swap,  and then the bits are set to the result of themselves XORed with x.   Of course, the result is undefined if the sequences overlap.

On July 14, 2009 Hallvard Furuseth suggested that I change the  1 << n to 1U << n because the value was being assigned to an unsigned and to avoid shifting into a sign bit. 


http://graphics.stanford.edu/~seander/bithacks.html