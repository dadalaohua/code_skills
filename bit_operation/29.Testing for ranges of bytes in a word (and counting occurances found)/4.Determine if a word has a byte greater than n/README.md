# Determine if a word has a byte greater than n

### Determine if a word has a byte greater than n

Test if a word x contains an unsigned byte with value > n.   Uses 3 arithmetic/logical operations when n is constant.

Requirements: x>=0; 0<=n<=127

```
#define hasmore(x,n) (((x)+~0UL/255*(127-(n))|(x))&~0UL/255*128)
```

To count the number of bytes in x that are more than n in 6 operations, use:

```
#define countmore(x,n) \
(((((x)&~0UL/255*127)+~0UL/255*(127-(n))|(x))&~0UL/255*128)/128%255)
```



The macro `hasmore` was suggested by Juha Järvi on  April 6, 2005, and he added `countmore` on April 8, 2005.

http://graphics.stanford.edu/~seander/bithacks.html