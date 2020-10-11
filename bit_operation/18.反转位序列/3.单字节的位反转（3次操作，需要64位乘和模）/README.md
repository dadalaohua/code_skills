# 单字节的位反转（3次操作，需要64位乘和模）
```
unsigned char b; // reverse this (8-bit) byte
                 // 反转这个（8位长）字节

b = (b * 0x0202020202ULL & 0x010884422010ULL) % 1023;
```

乘法操作产生了5份8位长的串，保存在64位整数里。按位与操作选取出一些特定位置上（反转）的位，并按照10位一组的方式分组。乘法和按位与操作将需要的二进制位从原始的字节中提取出来，使得他们都只出现在10位长的组里。原始字节反转后的位置，正好是他们在每个10位小组里面的相对位置。最后一步，通过模除2^10 - 1，可以使64位整数的值按照每10位每10位的方式合并在一起。这个操作不会让他们溢出，所以这个模除的步骤看起来很像按位或。

这个方法出自 Rich Schroeppel 的[Beeler, M., Gosper, R. W., and Schroeppel, R. HAKMEM. MIT AI Memo 239, Feb. 29, 1972](http://www.inwap.com/pdp10/hbaker/hakmem/hakmem.html)中的Programming Hacks小节。

***

### Reverse the bits in a byte with 3 operations (64-bit multiply and modulus division):



```
unsigned char b; // reverse this (8-bit) byte
 
b = (b * 0x0202020202ULL & 0x010884422010ULL) % 1023;
```

The multiply operation creates five separate copies of the 8-bit  byte pattern to fan-out into a 64-bit value. The AND operation selects the bits that are in the correct (reversed)  positions, relative to each 10-bit groups of bits. The multiply and the AND operations copy the bits from the original  byte so they each appear in only one of the 10-bit sets.   The reversed positions of the bits from the original byte coincide with their relative positions within any 10-bit set. The last step, which involves modulus division by 2^10 - 1, has the effect of merging together each set of 10 bits  (from positions 0-9, 10-19, 20-29, ...) in the 64-bit value.   They do not overlap, so the addition steps underlying the modulus division behave like or operations.

This method was attributed to Rich Schroeppel in the Programming Hacks section of  [ Beeler, M., Gosper, R. W., and Schroeppel, R.  HAKMEM. MIT AI Memo 239, Feb. 29, 1972.](http://www.inwap.com/pdp10/hbaker/hakmem/hakmem.html)

http://graphics.stanford.edu/~seander/bithacks.html