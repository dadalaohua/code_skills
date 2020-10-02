# 交换两个变量的值(只使用+，-还有位操作,无多余变量)

交换两个变量的值（只使用+，-还有位操作,无多余变量） 
```
#define SWAP(a, b) ((&(a) == &(b)) || /
                    (((a) -= (b)), ((b) += (a)), ((a) = (b) - (a))))
```
不建议对浮点数使用这个方法，会比XOR的方法慢.
***

### Swapping values with subtraction and addition

```
#define SWAP(a, b) ((&(a) == &(b)) || \
                    (((a) -= (b)), ((b) += (a)), ((a) = (b) - (a))))
```

This swaps the values of a and b *without using a temporary variable.* The initial check for a and b being the same location in memory may be omitted when you know this can't happen.  (The compiler may omit it anyway as an optimization.)  If you enable overflows exceptions, then pass unsigned  values so an exception isn't thrown. The XOR method that follows may be slightly faster on some machines.  Don't use this with floating-point numbers (unless you operate on their raw integer representations).

Sanjeev Sivasankaran suggested I add this on June 12, 2007.   Vincent Lefèvre pointed out the potential for overflow exceptions on July 9, 2008


http://graphics.stanford.edu/~seander/bithacks.html