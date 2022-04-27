# Integer Hash Function

Thomas Wang, Jan 1997

last update Mar 2007

Version 3.1

------

## Abstract 摘要

An integer hash function accepts an integer hash key, and returns an integer hash result with uniform distribution. In this article, we will be discussing the construction of integer hash functions.

整数哈希函数接受一个整数哈希键，并返回一个均匀分布的整数哈希结果。在本文中，我们将讨论整数哈希函数的构造。

## Introduction 介绍

Hash table is an important data structure. All elementary data structure text books contain some algorithms of hash table. However, all too often the treatment of hash function is discussed as an after-thought. Thus examples abound in systems where the poor choice of the hash function resulted in inferior performance.

哈希表是一种重要的数据结构。所有的基本数据结构教科书都包含了一些哈希表算法。然而，哈希函数的处理常常被当作事后的想法来讨论。因此，系统中有很多这样的例子，糟糕的哈希函数选择导致了较差的性能。

Certainly the integer hash function is the most basic form of the hash function. The integer hash function transforms an integer hash key into an integer hash result. For a hash function, the distribution should be uniform. This implies when the hash result
is used to calculate hash bucket address, all buckets are equally likely to be picked. In addition, similar hash keys should be hashed to very different hash results. Ideally, a single bit change in the hash key should influence all bits of the hash result.

当然整数哈希函数是哈希函数的最基本形式。整数哈希函数将整型数哈希键转换为整型数哈希结果。对于哈希函数，分布应该是均匀的。这意味着当哈希结果被用来计算哈希桶地址时，所有桶被选中的可能性都是相等的。此外，类似的哈希键应该被哈希成非常不同的哈希结果。理想情况下，哈希键的单个位变化应该影响哈希结果的所有位。

## Hash Function Construction Principles 哈希函数构造原则

A good mixing function must be reversible. A hash function has form h(x) -> y. If the input word size and the output word size are identical, and in addition the operations in h() are reversible, then the following properties are true.

一个好的混合函数必须是可逆的。哈希函数的形式为 h(x) - >y。如果输入字大小和输出字大小相同，并且h()中的操作是可逆的，则下列属性为真。

1. If h(x1) == y1, then there is an inverse function h_inverse(y1) == x1                                                                               如果 h(x1) == y1，则存在反函数 h_inverse(y1) == x1
2. Because the inverse function exists, there cannot be a value x2 such that x1 != x2, and h(x2) == y1. 因为存在反函数，所以不可能有一个值 x2 使 x1 != x2 且 h(x2) == y1。

The case of h(x1) == y1, and h(x2) == y1 is called a collision. Using only reversible operations in a hash function makes collisions impossible. There is an one-to-one mapping between the input and the output of the mixing function.

h(x1) == y1 且 h(x2) == y1 的情况称为碰撞。在哈希函数中只使用可逆操作会使冲突不可能发生。在混合函数的输入和输出之间有一个一对一的映射。

Beside reversibility, the operations must use a chain of computations to achieve avalanche. Avalanche means that a single bit of difference in the input will make about 1/2 of the output bits be different. At a point in the chain, a new result is obtained by a computation involving earlier results.

除了可逆性之外，这些操作必须使用一系列计算来实现雪崩。雪崩意味着输入的单个位差异将使大约 1/2 的输出位不同。在链中的某个点，用以前的结果进行计算，得到新的结果。

For example, the operation a = a + b is reversible if we know the value of 'b', and the after value of 'a'. The before value of 'a' is obtained by subtracting the after value of 'a' with the value of 'b'.

例如，如果我们知道 'b' 的值和 'a' 的后值，则操作 a = a + b 是可逆的。'a' 的前一个值是用 'b' 的值减去 'a' 的后一个值得到的。

## Knuth's Multiplicative Method Knuth的乘法方法

In Knuth's "The Art of Computer Programming", section 6.4, a multiplicative hashing scheme is introduced as a way to write hash function. The key is multiplied by the golden ratio of 2^32 (2654435761) to produce a hash result.

在 Knuth 的“计算机编程艺术”第 6.4 节中，引入了乘法哈希方案作为编写哈希函数的一种方式。密钥乘以黄金比例 2^32 (2654435761) 以产生一个哈希结果。

Since 2654435761 and 2^32 has no common factors in common, the multiplication produces a complete mapping of the key to hash result with no overlap. This method works pretty well if the keys have small values. Bad hash results are produced if the keys vary in the upper bits. As is true in all multiplications, variations of upper digits do not influence the lower digits of the multiplication result.

由于 2654435761 和 2^32 没有共同的公因子，因此乘法产生了键到哈希结果的完全映射，没有重叠。如果键的值很小，这种方法效果很好。如果键的高位不同，就会产生坏的哈希结果。与所有乘法一样，高位数字的变化不会影响乘法结果的低位数字。

## Robert Jenkins' 96 bit Mix Function

[Robert Jenkins](https://gist.github.com/web/20071223173210/http://www.burtleburtle.net/bob/hash/doobs.html) has developed a hash function based on a sequence of subtraction, exclusive-or, and bit shift.

Robert Jenkins 开发了一个基于减法、异或和位移位序列的哈希函数。

All the sources in this article are written as Java methods, where the operator '>>>' represents the concept of unsigned right shift. If the source were to be translated to C, then the Java 'int' data type should be replaced with C 'uint32_t' data type, and
the Java 'long' data type should be replaced with C 'uint64_t' data type.

本文中的所有源代码均以 Java 方法编写，其中运算符“>>>”表示无符号右移的概念。如果源要转换为 C，则 Java 'int' 数据类型应替换为 C 'uint32_t' 数据类型，并且 Java 'long' 数据类型应替换为 C 'uint64_t' 数据类型。

The following source is the mixing part of the hash function.

下面的源代码是哈希函数的混合部分。

```java
int mix(int a, int b, int c)
{
  a=a-b;  a=a-c;  a=a^(c >>> 13);
  b=b-c;  b=b-a;  b=b^(a << 8);
  c=c-a;  c=c-b;  c=c^(b >>> 13);
  a=a-b;  a=a-c;  a=a^(c >>> 12);
  b=b-c;  b=b-a;  b=b^(a << 16);
  c=c-a;  c=c-b;  c=c^(b >>> 5);
  a=a-b;  a=a-c;  a=a^(c >>> 3);
  b=b-c;  b=b-a;  b=b^(a << 10);
  c=c-a;  c=c-b;  c=c^(b >>> 15);
  return c;
}
```

Variable 'c' contains the input key. When the mixing is complete, variable 'c' also contains the hash result. Variable 'a', and 'b' contain initialized random bits. Notice the total number of internal state is 96 bits, much larger than the final output of 32 bits. Also notice the sequence of subtractions rolls through variable 'a' to variable 'c' three times. Each row will act on one variable, mixing in information from the other two variables, followed by a shift operation.

变量'c'包含输入键。当混合完成时，变量'c'也包含哈希结果。变量'a'和'b'包含初始化的随机位。注意内部状态的总数是96位，比最终输出的32位要大得多。还要注意减法序列在变量'a'到变量'c'之间滚动了三次。每一行将作用于一个变量，混合来自其他两个变量的信息，然后进行移位操作。

Subtraction is similar to multiplication in that changes in upper bits of the key do not influence lower bits of the addition. The 9 bit shift operations in Robert Jenkins' mixing algorithm shifts the key to the right 61 bits in total, and shifts the key to the left 34 bits in total. As the calculation is chained, each exclusive-or doubles the number of states. There are at least 2^9 different combined versions of the original key, shifted by various amounts. That is why a single bit change in the key can influence widely apart bits in the hash result.

减法与乘法相似，键高位的改变不会影响加法的低位。Robert Jenkins 混合算法中的9位移位操作，将键向右移位共61位，向左移位共34位。由于计算是链式的，每个异或都会使状态数加倍。原来的键至少有 2^9 种不同的组合版本，移动了不同的数量。这就是为什么键的单个位变化会对哈希结果中的各个位产生很大的影响。

The uniform distribution of the hash function can be determined from the nature of the subtraction operation. Look at a single bit subtraction operation between a key, and a random bit. If the random bit is 0, then the key remains unchanged. If the random bit is 1, then the key will be flipped. A carry will occur in the case where both the key bit and the random bit are 1. Subtracting the random bits will cause about half of the key bits to be flipped. So even if the key is not uniform, subtracting the random bits will result in uniform distribution.

哈希函数的均匀分布可以由减法运算的性质来确定。看看一个键和一个随机位之间的单个位的减法操作。如果随机位为0，则键保持不变。如果随机位为1，那么键将被翻转。当键位和随机位同时为1时，就会出现进位。减去随机位将导致大约一半的键位被翻转。因此，即使键不是均匀的，减去随机位也会得到均匀分布。

## 32 bit Mix Functions

Based on an original suggestion on Robert Jenkin's part in 1997, I have done some research for a version of the integer hash function. This is my latest version as of January 2007. The specific value of the bit shifts are obtained from running the accompanied search program.

基于 Robert Jenkin 在 1997 年提出的一个原始建议，我对整数哈希函数的一个版本做了一些研究。这是我 2007 年 1 月的最新版本。所述位移的具体值是通过运行随附的搜索程序获得的。

```java
public int hash32shift(int key)
{
  key = ~key + (key << 15); // key = (key << 15) - key - 1;
  key = key ^ (key >>> 12);
  key = key + (key << 2);
  key = key ^ (key >>> 4);
  key = key * 2057; // key = (key + (key << 3)) + (key << 11);
  key = key ^ (key >>> 16);
  return key;
}
```

(~x) + y is equivalent to y - x - 1 in two's complement representation.

(~x) + y 等价于二进制补码表示中的 y - x - 1。

By taking advantages of the native instructions such as 'add complement', and 'shift & add', the above hash function runs in 11 machine cycles on HP 9000 workstations.

通过利用诸如“添加补码”和“移位和添加”等本机指令，上述哈希函数在 HP 9000 工作站上运行 11 个机器周期。

Having more rounds will strengthen the hash function by making the result more random looking, but performance will be slowed down accordingly. Simulation seems to prefer small shift amounts for inner rounds, and large shift amounts for outer rounds.

增加轮次会增强哈希函数，让结果看起来更随机，但性能也会相应降低。模拟似乎更喜欢内轮的小位移量和外轮的大位移量。

## Robert Jenkins' 32 bit integer hash function

```c
uint32_t hash( uint32_t a)
{
   a = (a+0x7ed55d16) + (a<<12);
   a = (a^0xc761c23c) ^ (a>>19);
   a = (a+0x165667b1) + (a<<5);
   a = (a+0xd3a2646c) ^ (a<<9);
   a = (a+0xfd7046c5) + (a<<3);
   a = (a^0xb55a4f09) ^ (a>>16);
   return a;
}
```

This version of integer hash function uses operations with integer constants to help producing a hash value. I suspect the actual values of the magic constants are not very important. Even using 16 bit constants may still work pretty well.

这个版本的整数哈希函数使用带有整数常量的操作来帮助生成一个哈希值。我怀疑魔数的实际值不是很重要。即使使用16位常量也可以很好地工作。

These magic constants open up the construction of perfect integer hash functions. A test program can vary the magic constants until a set of perfect hashes are found.

这些神奇的常量打开了构造完美整数哈希函数的大门。测试程序可以改变魔术常数，直到找到一组完美的哈希值。

## Using Multiplication for Hashing 使用乘法进行哈希运算

Using multiplication requires a mechanism to transport changes from high bit positions to low bit positions. Bit reversal is best, but is slow to implement. A viable alternative is left shifts.

使用乘法需要一种机制来传输从高位位置到低位位置的变化。位反转是最好的，但执行起来很慢。一个可行的替代方案是左移。

Using multiplication presents some sort of dilemma. Certain machine platforms supports integer multiplication in hardware, and an integer multiplication can be completed in 4 or less cycles. But on some other platforms an integer multiplication could take 8 or more cycles to complete. On the other hand, integer hash functions implemented with bit shifts perform equally well on all platforms.

使用乘法会遇到一些难题。某些机器平台在硬件上支持整数乘法，一个整数乘法可以在4个或更少的周期内完成。但在其他一些平台上，整数乘法可能需要8个或更多的周期才能完成。另一方面，用位移实现的整数哈希函数在所有平台上的性能都一样好。

A compromise is to multiply the key with a 'sparse' bit pattern, where on machines without fast integer multiplier they can be replaced with a 'shift & add' sequence. An example is to multiply the key with (4096 + 8 + 1), with an equivalent expression of (key + (key << 3)) + (key << 12).

一种折衷方案是将键与“稀疏”位模式相乘，在没有快速整数乘法器的机器上，它们可以用“移位和加法”序列替换。 一个例子是将键与 (4096 + 8 + 1) 相乘，等效表达式为 (key + (key << 3)) + (key << 12)。

On most machines a bit shift of 3 bits or less, following by an addition can be performed in one cycle. For example, Pentium's 'lea' instruction can be used to good effect to compute a 'shift & add' in one cycle.

在大多数机器上，可以在一个周期内执行 3 位或更少的位移，然后进行加法运算。 例如，Pentium 的“lea”指令可以很好地用于在一个周期内计算“移位和添加”。

Function hash32shiftmult() uses a combination of bit shifts and integer multiplication to hash the input key.

函数 hash32shiftmult() 使用位移和整数乘法的组合来哈希输入键。

```java
public int hash32shiftmult(int key)
{
  int c2=0x27d4eb2d; // a prime or an odd constant
  key = (key ^ 61) ^ (key >>> 16);
  key = key + (key << 3);
  key = key ^ (key >>> 4);
  key = key * c2;
  key = key ^ (key >>> 15);
  return key;
}
```

## 64 bit Mix Functions

```java
public long hash64shift(long key)
{
  key = (~key) + (key << 21); // key = (key << 21) - key - 1;
  key = key ^ (key >>> 24);
  key = (key + (key << 3)) + (key << 8); // key * 265
  key = key ^ (key >>> 14);
  key = (key + (key << 2)) + (key << 4); // key * 21
  key = key ^ (key >>> 28);
  key = key + (key << 31);
  return key;
}
```

The longer width of 64 bits require more mixing than the 32 bit version.

64 位的较长宽度需要比 32 位版本更多的混合。

## 64 bit to 32 bit Hash Functions

One such use for this kind of hash function is to hash a 64 bit virtual address to a hash table index. Because the output of the hash function is narrower than the input, the result is no longer one-to-one.

这种哈希函数的一个用途是将 64 位虚拟地址哈希到哈希表索引。因为哈希函数的输出比输入窄，所以结果不再是一对一的。

Another usage is to hash two 32 bit integers into one hash value.

另一种用法是将两个 32 位整数散列成一个哈希值。

```java
public int hash6432shift(long key)
{
  key = (~key) + (key << 18); // key = (key << 18) - key - 1;
  key = key ^ (key >>> 31);
  key = key * 21; // key = (key + (key << 2)) + (key << 4);
  key = key ^ (key >>> 11);
  key = key + (key << 6);
  key = key ^ (key >>> 22);
  return (int) key;
}
```

## Parallel Operations 并行操作

If a CPU can dispatch multiple instructions in the same clock cycle, one can consider adding more parallelism in the formula.

如果 CPU 可以在同一时钟周期内调度多条指令，则可以考虑在公式中添加更多并行性。

For example, for the following formula, the two shift operations can be performed in parallel. On certain platforms where there are multiple ALUs but a single shifter unit, this idea does not offer a speed increase.

例如，对于下面的公式，两个移位操作可以并行执行。 在有多个 ALU 但只有一个移位器单元的某些平台上，这个想法并不能提高速度。

```java
key ^= (key << 17) | (key >>> 16);
```

For 32 bit word operations, only certain pairs of shift amounts will be reversible. The valid pairs include: (17,16) (16,17) (14,19) (19,14) (13,20) (20,13) (10,23) (23,10) (8,25) (25,8)

对于 32 位字操作，只有特定的移位量对是可逆的。 有效对包括： (17,16) (16,17) (14,19) (19,14) (13,20) (20,13) (10,23) (23,10) (8,25) (25,8)

Multiplication can be computed in parallel. Any multiplication with odd number is reversible.

乘法可以并行计算。 任何奇数的乘法都是可逆的。

```java
key += (key << 3) + (key << 9); // key = key * (1 + 8 + 512)
```

On certain machines, bit rotation can be performed in one cycle. Any odd number bits rotation can be made reversible when exclusive-or is applied to the un-rotated key with one particular bit set to 1 or 0.

在某些机器上，位旋转可以在一个周期内完成。 当一个特定位设置为 1 或 0 的异或应用于未旋转的键时，任何奇数位旋转都可以是可逆的。

```java
key = (key | 64) ^ ((key >>> 15) | (key << 17));
```

However, on certain machine and compiler combinations, this code sequence can run as slow as 4 cycles. 2 cycles: a win, 3 cycles: tie, more than 3 cycles: a loss.

但是，在某些机器和编译器组合上，此代码序列的运行速度可能低至 4 个周期。 2个循环：赢，3个循环：平局，超过3个循环：输。

## Pseudo Random Usages 伪随机用法

There has been queries whether these mix functions can be used for pseudo random purposes. Although the out does look random to the naked eye, the official recommendation is to use a real pseudo random number generator instead, such as the [Mercenne Twister](https://gist.github.com/web/20071223173210/http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html).

有人质疑这些混合函数是否可用于伪随机目的。 虽然肉眼看起来确实是随机的，但官方建议使用真正的伪随机数生成器，例如 Mercenne Twister。

The hash functions listed in this article were only tested for hashing purpose. No tests of randomness were performed.

本文中列出的哈希函数只是出于哈希目的进行了测试。没有进行随机性测试。

## Test Program 测试程序

This is a [test program](https://gist.github.com/web/20071223173210/http://www.concentric.net/~Ttwang/tech/testchange.java) testing the choices of the shift amounts with regard to the resulting avalanche property. The program detects if a certain bit position has both changes and no changes, based on a single bit flip. Promising candidates are further tested to verify the percentage chance of bit flip is sufficiently close to 50% for all input and output bit pairs.

这是一个[测试程序](https://gist.github.com/web/20071223173210/http://www.concentric.net/~Ttwang/tech/testchange.java)，测试与雪崩属性有关的偏移量的选择。该程序根据单个位翻转来检测某个位位置是否有变化或没有变化。对有希望的候选对象进行进一步测试，以验证对于所有输入和输出位对，位翻转的百分比概率足够接近50%。

The test program prints out the name of the algorithm under test, followed by the list of shift amounts that pass the avalanche test.

测试程序打印出被测算法的名称，然后是通过雪崩测试的移位量列表。

## Power of 2 Hash Table Size 哈希表大小是 2 的幂

Programmer uses hash table size that is power of 2 because address calculation can be performed very quickly. The integer hash function can be used to post condition the output of a marginal quality hash function before the final address calculation is done.

程序员使用的哈希表大小是2的幂，因为地址计算可以非常快地执行。整数哈希函数可用于在进行最终地址计算之前对边缘质量哈希函数的输出进行后置处理。

```java
addr = inthash(marginal_hash_value) & (tablesize - 1);
```

Using the inlined version of the integer hash function is faster than doing a remaindering operation with a prime number! An integer remainder operation may take up to 18 cycles or longer to complete, depending on machine architecture.

使用内联版本的整数哈希函数比使用素数进行求余运算更快！整数的余数运算可能需要18个周期或更长的时间来完成，这取决于机器的结构。

## Conclusions 结论

In this article, we have examined a number of hash function construction algorithms. Knuth's multiplicative method is the simplest, but has some known defects. Robert Jenkins' 96 bit mix function can be used as an integer hash function, but is more suitable for hashing long keys. A dedicated hash function is well suited for hashing an integer number.

在本文中，我们研究了一些哈希函数的构造算法。Knuth 的乘法方法是最简单的，但有一些已知的缺陷。Robert Jenkins 的96位混合函数可以用作整数哈希函数，但更适合哈希长键。专用哈希函数非常适合于哈希整数。

We have also presented an application of the integer hash function to improve the quality of a hash value.

我们还介绍了一个整数哈希函数的应用，以提高哈希值的质量。



***

引用自 https://gist.[github](https://so.csdn.net/so/search?q=github&spm=1001.2101.3001.7020).com/badboy/6267743



Original link: http://www.concentric.net/~Ttwang/tech/inthash.htm
Taken from:http://web.archive.org/web/20071223173210/http://www.concentric.net/~Ttwang/tech/inthash.htm
Reformatted using pandoc