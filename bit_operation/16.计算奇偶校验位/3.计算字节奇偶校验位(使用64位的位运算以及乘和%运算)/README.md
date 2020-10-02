#  计算字节奇偶校验位(使用64位的位运算以及*和%运算) 

计算字节奇偶校验位(使用64位的位运算以及*和%运算) 
```
unsigned char b;  // byte value to compute the parity of
bool parity = 
  (((b * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
The method above takes around 4 operations, but only works on bytes. 
```
***

### Compute parity of a byte using 64-bit multiply and modulus division



```
unsigned char b;  // byte value to compute the parity of
bool parity = 
  (((b * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
```

The method above takes around 4 operations, but only works on bytes.

http://graphics.stanford.edu/~seander/bithacks.html