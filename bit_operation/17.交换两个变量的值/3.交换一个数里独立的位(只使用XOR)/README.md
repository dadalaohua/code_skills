# 交换一个数里独立的位(只使用XOR) 

交换一个数里独立的位(只使用XOR) 
```
unsigned int i, j; // 要交换的位的起始位置
unsigned int n;    // 要交换的位数
unsigned int b;    // 被交换的数
unsigned int r;    // 交换独立位之后的结果
 
unsigned int x = ((b >> i) ^ (b >> j)) & ((1U << n) - 1); // XOR temporary
r = b ^ ((x << i) | (x << j));
```
例如b = 00101111 (二进制) ,我们要交换从起始位1和起始位5的位(从右边数)，交换的位数是3个，所以起始位1的3个位数111(从右边数), 起始位5的3个位数是001(从右边数),那么交换的结果就是r = 11100011 (二进制). 

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