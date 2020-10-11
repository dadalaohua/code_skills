#  计算字节奇偶校验位(使用64位的乘法和模除) 

```
unsigned char b;  // byte value to compute the parity of
                  // 需要计算的值保存在变量b中
bool parity =
  (((b * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
```
这个方法只需要4次操作，然而只能计算单个字节。
***

### Compute parity of a byte using 64-bit multiply and modulus division



```
unsigned char b;  // byte value to compute the parity of
bool parity = 
  (((b * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
```

The method above takes around 4 operations, but only works on bytes.

http://graphics.stanford.edu/~seander/bithacks.html