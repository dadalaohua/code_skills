# Interleave bits with 64-bit multiply

### Interleave bits with 64-bit multiply

In 11 operations, this version interleaves bits of two bytes  (rather than shorts, as in the other versions),  but many of the operations are 64-bit multiplies  so it isn't appropriate for all machines.  The input parameters, x and y, should be less than 256.

```
unsigned char x;  // Interleave bits of (8-bit) x and y, so that all of the
unsigned char y;  // bits of x are in the even positions and y in the odd;
unsigned short z; // z gets the resulting 16-bit Morton Number.

z = ((x * 0x0101010101010101ULL & 0x8040201008040201ULL) * 
     0x0102040810204081ULL >> 49) & 0x5555 |
    ((y * 0x0101010101010101ULL & 0x8040201008040201ULL) * 
     0x0102040810204081ULL >> 48) & 0xAAAA;
```

Holger Bettag was inspired to suggest this technique on October 10, 2004 after reading the multiply-based bit reversals here.

http://graphics.stanford.edu/~seander/bithacks.html