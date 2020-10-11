# Determine if a word has a byte between m and n

### Determine if a word has a byte between m and n

When m < n, this technique tests if a word x contains an  unsigned byte value, such that m < value < n.   It uses 7 arithmetic/logical operations when n and m are constant.

Note:  Bytes that equal n can be reported by `likelyhasbetween` as false positives, so this should be checked by character if a certain result is needed.

Requirements: x>=0; 0<=m<=127; 0<=n<=128



```
#define likelyhasbetween(x,m,n) \
((((x)-~0UL/255*(n))&~(x)&((x)&~0UL/255*127)+~0UL/255*(127-(m)))&~0UL/255*128)
```

This technique would be suitable for a fast pretest.  A variation that takes one more operation (8 total for constant m and n) but provides the exact answer is:

```
#define hasbetween(x,m,n) \
((~0UL/255*(127+(n))-((x)&~0UL/255*127)&~(x)&((x)&~0UL/255*127)+~0UL/255*(127-(m)))&~0UL/255*128)
```

To count the number of bytes in x that are between m and n (exclusive) in 10 operations, use:

```
#define countbetween(x,m,n) (hasbetween(x,m,n)/128%255)
```



Juha Järvi suggested `likelyhasbetween` on April 6, 2005.   From there, Sean Anderson created `hasbetween` and  `countbetween` on April 10, 2005.

http://graphics.stanford.edu/~seander/bithacks.html