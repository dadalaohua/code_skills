# 单字节的位反转（7次操作，不需要64位操作）

```
b = ((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
```
这个技巧借助高位溢出来消除计算中产生的无用数值，使用前要确保操作的结果保存在无符号char型变量里，以避免这个技巧失效。

2001年7月13日，出自Sean Anderson之手。 
2002年1月3日，Mike Keith指出并纠正了书写错误。

***

### Reverse the bits in a byte with 7 operations (no 64-bit):



```
b = ((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16; 
```

  Make sure you assign or cast the result to an unsigned char to remove  garbage in the higher bits.   Devised by Sean Anderson, July 13, 2001.  Typo spotted and correction supplied by Mike Keith, January 3, 2002.

http://graphics.stanford.edu/~seander/bithacks.html