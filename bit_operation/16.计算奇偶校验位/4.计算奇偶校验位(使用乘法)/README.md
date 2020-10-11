#  计算奇偶校验位(使用乘法) 

这个方法计算32位字长的值在使用乘法的情况下，只需要8次操作。
```
unsigned int v; // 32-bit word
                // 32位长度的字
v ^= v >> 1;
v ^= v >> 2;
v = (v & 0x11111111U) * 0x11111111U;
return (v >> 28) & 1;
```
对于64位，仍只需要8次操作。
```
unsigned long long v; // 64-bit word
                      // 64位长度的字

v ^= v >> 1;
v ^= v >> 2;
v = (v & 0x1111111111111111UL) * 0x1111111111111111UL;
return (v >> 60) & 1;
```
2007年9月2日，Andrew Shapira想出的这个算法，并发给了我。
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