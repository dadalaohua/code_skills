# 交换数值(使用加法和减法) 

```
#define SWAP(a, b) ((&(a) == &(b)) || /
                    (((a) -= (b)), ((b) += (a)), ((a) = (b) - (a))))
```
这个交换的方法不使用临时变量。一开始有一个检查变量a和变量b在内存中的位置是否相同，如果你能确保这种情况不会发生，那么这个检查可以去掉。（编译器可能也会把这个给优化掉）如果程序有溢出时抛异常的机制，那么传入无符号型的值就不会抛异常了。待会儿会介绍一个使用异或的方法，这个方法在某些机器上可能会稍微快一些。注意这个方法不能应用在浮点数的交换上（除非你就是想使用他们的整数形式）。
***

### Swapping values with subtraction and addition

```
#define SWAP(a, b) ((&(a) == &(b)) || \
                    (((a) -= (b)), ((b) += (a)), ((a) = (b) - (a))))
```

This swaps the values of a and b *without using a temporary variable.* The initial check for a and b being the same location in memory may be omitted when you know this can't happen.  (The compiler may omit it anyway as an optimization.)  If you enable overflows exceptions, then pass unsigned  values so an exception isn't thrown. The XOR method that follows may be slightly faster on some machines.  Don't use this with floating-point numbers (unless you operate on their raw integer representations).

Sanjeev Sivasankaran suggested I add this on June 12, 2007.   Vincent Lefèvre pointed out the potential for overflow exceptions on July 9, 2008


http://graphics.stanford.edu/~seander/bithacks.html