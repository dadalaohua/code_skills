# Determine if a word has a byte less than n

### Determine if a word has a byte less than n

Test if a word x contains an unsigned byte with value < n. Specifically for n=1, it can be used to find a 0-byte by examining one long at a time, or any byte by XORing x with a mask first. Uses 4 arithmetic/logical operations when n is constant.

Requirements: x>=0; 0<=n<=128

```
#define hasless(x,n) (((x)-~0UL/255*(n))&~(x)&~0UL/255*128)
```

To count the number of bytes in x that are less than n in 7 operations, use

```
#define countless(x,n) \
(((~0UL/255*(127+(n))-((x)&~0UL/255*127))&~(x)&~0UL/255*128)/128%255)
```



Juha Järvi sent this clever technique to me on April 6, 2005.  The `countless` macro was added by Sean Anderson on  April 10, 2005, inspired by Juha's `countmore`, below.

http://graphics.stanford.edu/~seander/bithacks.html