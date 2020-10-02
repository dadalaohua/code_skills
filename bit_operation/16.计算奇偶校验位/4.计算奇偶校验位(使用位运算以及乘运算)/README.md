#  计算奇偶校验位(使用位运算以及乘运算) 

计算奇偶校验位(使用位运算以及*运算) 
下面的运算只用了8次运算.
```
    unsigned int v; // 待计算校验位的32位数
    v ^= v >> 1;
    v ^= v >> 2;
    v = (v & 0x11111111U) * 0x11111111U;
    return (v >> 28) & 1;
```
对于64位整数也只需要8次运算. 
```
    unsigned long long v; // 64位整数
    v ^= v >> 1;
    v ^= v >> 2;
    v = (v & 0x1111111111111111UL) * 0x1111111111111111UL;
    return (v >> 60) & 1;
```
***

### Compute parity of word with a multiply

The following method computes the parity of the 32-bit value in only 8  operations using a multiply.

```
    unsigned int v; // 32-bit word
    v ^= v >> 1;
    v ^= v >> 2;
    v = (v & 0x11111111U) * 0x11111111U;
    return (v >> 28) & 1;
```

Also for 64-bits, 8 operations are still enough.

```
    unsigned long long v; // 64-bit word
    v ^= v >> 1;
    v ^= v >> 2;
    v = (v & 0x1111111111111111UL) * 0x1111111111111111UL;
    return (v >> 60) & 1;
```



Andrew Shapira came up with this and sent it to me on Sept. 2, 2007.

http://graphics.stanford.edu/~seander/bithacks.html