# 交换两个变量的值(只使用XOR) 

交换两个变量的值(只使用XOR) 
```
#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))
```

***

### Swapping values with XOR

```
#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))
```

  This is an old trick to exchange the values of the variables a and b  *without using extra space for a temporary variable*.

On January 20, 2005, Iain A. Fleming pointed out that the macro above  doesn't work when you swap with the same memory location, such as SWAP(a[i], a[j]) with i == j.  So if that may occur, consider defining the macro as  (((a) == (b)) || (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))). On July 14, 2009, Hallvard Furuseth suggested that on some machines, (((a) ^ (b)) && ((b) ^= (a) ^= (b), (a) ^= (b))) might be faster,  since the (a) ^ (b) expression is reused.


http://graphics.stanford.edu/~seander/bithacks.html