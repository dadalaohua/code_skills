# 根据掩码把两个数进行位合并 

根据掩码把两个数进行位合并 
```
unsigned int a;    // 将要被合并的数a
unsigned int b;    // 将要被合并的数b
unsigned int mask; // 1 where bits from b should be selected; 0 where from a.
unsigned int r;    // r = (a & ~mask) | (b & mask) 
r = a ^ ((a ^ b) & mask); 
```
***

### Merge bits from two values according to a mask

```
unsigned int a;    // value to merge in non-masked bits
unsigned int b;    // value to merge in masked bits
unsigned int mask; // 1 where bits from b should be selected; 0 where from a.
unsigned int r;    // result of (a & ~mask) | (b & mask) goes here

r = a ^ ((a ^ b) & mask); 
```

This shaves one operation from the obvious way of combining two sets of bits according to a bit mask.  If the mask is a constant, then there may be no advantage.

Ron Jeffery sent this to me on February 9, 2006.

http://graphics.stanford.edu/~seander/bithacks.html