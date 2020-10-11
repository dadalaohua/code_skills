# 计算奇偶校验位(并行) 

```
unsigned int v;  // word value to compute the parity of
                 // 需要计算奇偶校验位的字长度的值
v ^= v >> 16;
v ^= v >> 8;
v ^= v >> 4;
v &= 0xf;
return (0x6996 >> v) & 1;
```
这个方法需要9次运算，可以工作在32位字长的环境下。如果是只需要对字节进行计算，那么可以把“unsigned int v;”的下两行去掉，这样可以把操作数优化到5次。这个方法先是将这个32位值的分成8个半字节，通过右移和异或将v压缩到v的最低的半字节中。然后将二进制位0110 1001 1001 0110(十六位表示为0x6996)的数值右移，右移的位数是刚刚计算出来的v的最低半字节的值。这个幻数就像是一个16位的小型奇偶校验位的表，通过v的最低半字节的值可以查到v的奇偶校验位。最终结果存放在最低位中，代码最后通过掩码的方式计算出了结果并返回。

 

2002年12月15日，感谢Mathew Hendry提出了右移查表的想法。相比只使用右移和异或的方法，这个优化可以减少掉节省两次操作。

***

### Compute parity in parallel



```
unsigned int v;  // word value to compute the parity of
v ^= v >> 16;
v ^= v >> 8;
v ^= v >> 4;
v &= 0xf;
return (0x6996 >> v) & 1;
```

The method above takes around 9 operations, and works for 32-bit words.   It may be optimized to work just on bytes in 5 operations by removing the  two lines immediately following "unsigned int v;".  The method first shifts  and XORs the eight nibbles of the 32-bit value together, leaving the result  in the lowest nibble of v.  Next, the binary number 0110 1001 1001 0110  (0x6996 in hex) is shifted to the right by the value represented in the lowest  nibble of v.  This number is like a miniature 16-bit parity-table indexed by  the low four bits in v.  The result has the parity of v in bit 1, which is  masked and returned.

Thanks to Mathew Hendry for pointing out the shift-lookup idea at the end on Dec. 15, 2002.   That optimization shaves two operations off using only shifting and XORing to find the parity.

http://graphics.stanford.edu/~seander/bithacks.html