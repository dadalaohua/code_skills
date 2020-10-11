# Determine if a word has a zero byte

### Determine if a word has a zero byte



```
// Fewer operations:
unsigned int v; // 32-bit word to check if any 8-bit byte in it is 0
bool hasZeroByte = ~((((v & 0x7F7F7F7F) + 0x7F7F7F7F) | v) | 0x7F7F7F7F);
```

The code above may be useful when doing a fast string copy in which a word  is copied at a time; it uses 5 operations.   On the other hand, testing for a null byte in the obvious ways (which follow) have at least 7 operations (when counted in the most sparing way), and at most 12.

```
// More operations:
bool hasNoZeroByte = ((v & 0xff) && (v & 0xff00) && (v & 0xff0000) && (v & 0xff000000))
// OR:
unsigned char * p = (unsigned char *) &v;  
bool hasNoZeroByte = *p && *(p + 1) && *(p + 2) && *(p + 3);
```

The code at the beginning of this section (labeled "Fewer operations")  works by first zeroing the high bits of the 4 bytes in the word. Subsequently, it adds a number that will result in an overflow to  the high bit of a byte if any of the low bits were initialy set.   Next the high bits of the original word are ORed with these values;  thus, the high bit of a byte is set iff any bit in the byte was set.   Finally, we determine if any of these high bits are zero by ORing with  ones everywhere except the high bits and inverting the result.   Extending to 64 bits is trivial; simply increase the constants to be  0x7F7F7F7F7F7F7F7F.

For an additional improvement, a fast pretest that requires only 4 operations may be performed to determine if the word *may* have a zero byte.   The test also returns true if the high byte is 0x80, so there are  occasional false positives, but the slower and more reliable version  above may then be used on candidates for an overall increase in speed with correct output.



```
bool hasZeroByte = ((v + 0x7efefeff) ^ ~v) & 0x81010100;
if (hasZeroByte) // or may just have 0x80 in the high byte
{
  hasZeroByte = ~((((v & 0x7F7F7F7F) + 0x7F7F7F7F) | v) | 0x7F7F7F7F);
}
```



There is yet a faster method —  use [`hasless`](http://graphics.stanford.edu/~seander/bithacks.html#HasLessInWord)(v, 1),  which is defined below; it  works in 4 operations and requires no subsquent verification.  It simplifies to 

```
#define haszero(v) (((v) - 0x01010101UL) & ~(v) & 0x80808080UL)
```

The subexpression (v - 0x01010101UL), evaluates to a high bit set in any byte whenever the corresponding byte in v is zero or greater than 0x80.   The sub-expression ~v & 0x80808080UL  evaluates to high bits set in bytes where the byte of v doesn't have its high  bit set (so the byte was less than 0x80).  Finally, by ANDing these two  sub-expressions the result is the high bits set where the bytes in v  were zero, since the high bits set due to a value greater than 0x80  in the first sub-expression are masked off by the second.

Paul Messmer suggested the fast pretest improvement on October 2, 2004.   Juha Järvi later suggested `hasless(v, 1)` on April 6, 2005, which he found on [Paul Hsieh's Assembly Lab](http://www.azillionmonkeys.com/qed/asmexample.html); previously it was written in a newsgroup post  on April 27, 1987 by Alan Mycroft.

http://graphics.stanford.edu/~seander/bithacks.html