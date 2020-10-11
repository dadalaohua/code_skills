# **交换数值**(使用XOR) 

```
#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))
```
2005年1月20日，Iain A. Fleming指出如果我们交换的数值在内存中的地址相同，这个宏不会起作用，比如SWAP(a[i], a[j])，i == j。所以，如果那种情况可能发生，可以考虑增加一个判断，就像这样 (((a) == (b)) || (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))))。

2009年7月14日，Hallvard Furuseth建议，在有些机器上可能这条语句会更快一点`(((a) ^ (b)) && ((b) ^= (a) ^= (b), (a) ^= (b)))`，因为(a) ^ (b)这条表达式被再利用了（译者注：意思应该是省去了重复计算的步骤）。

***

### Swapping values with XOR

```
#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))
```

  This is an old trick to exchange the values of the variables a and b  *without using extra space for a temporary variable*.

On January 20, 2005, Iain A. Fleming pointed out that the macro above  doesn't work when you swap with the same memory location, such as SWAP(a[i], a[j]) with i == j.  So if that may occur, consider defining the macro as  (((a) == (b)) || (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))). On July 14, 2009, Hallvard Furuseth suggested that on some machines, (((a) ^ (b)) && ((b) ^= (a) ^= (b), (a) ^= (b))) might be faster,  since the (a) ^ (b) expression is reused.


http://graphics.stanford.edu/~seander/bithacks.html