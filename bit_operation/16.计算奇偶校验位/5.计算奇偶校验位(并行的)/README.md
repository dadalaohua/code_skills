# 计算奇偶校验位(并行的) 

计算奇偶校验位(并行的) 
```
unsigned int v;  //待计算校验位的32位数
v ^= v >> 16;
v ^= v >> 8;
v ^= v >> 4;
v &= 0xf;
return (0x6996 >> v) & 1;
```
上面的方法用了9次运算，对32位数适用。
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