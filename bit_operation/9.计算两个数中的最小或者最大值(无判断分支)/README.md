# 计算两个数中的最小或者最大值(无判断分支) 

```
int x;  // we want to find the minimum of x and y
int y;
        // 我们希望找出x和y之间的最小值
int r;  // the result goes here
        // 结果保存在这里
r = y ^ ((x ^ y) & -(x < y)); // min(x, y)
```
这个技巧能工作的原因是当`x<y`, 那么`-(x<y)`数值的二进制补码会是全1（-1的补码是全1），所以`r = y ^ (x ^ y) & ~0 = y ^ x ^ y = x`。反之，如果`x>=y`，那么`-(x<y)`会是全0，所以`r = y ^ ((x ^ y) & 0) = y`。在有些分支操作非常昂贵的机器，和没有提供条件跳转指令的机器上，上面的技巧会比这种常见的写法更快一些：`r = (x < y) ? x : y`，尽管这种常见的写法只使用了两三个指令。（虽然通常来讲，这种简单实现是最好的）。需要注意的是，在有的机器上，计算`x<y`的值也需要使用分支指令，所以这个时候这个技巧对比普通的实现也没有任何优势。

如果需要计算最大值，那么有

```
r = x ^ ((x ^ y) & -(x < y)); // max(x, y)
```
快但是有缺陷(dirty)的版本：

如果事先知道`INT_MIN <= x - y <= INT_MAX`(译者注：不会溢出)，那么你就可以使用以下技巧。由于(x-y)只需要计算一次，所以这个版本会更快一些。

```
r = y + ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1))); // min(x, y)
r = x - ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1))); // max(x, y) 
```

注意，1989年的ANSI C标准并没有指明带符号类型变量的右移行为，所以这个版本不具备兼容性。如果计算时由于溢出而导致抛出异常，x和y的值都应该是无符号型的或者被强制转换成无符号型的，来避免由于减法而导致不必要地抛出异常。然而，当进行右移操作是需要用强制类型转换，将数值转换成带符号的，这样才能根据数值的正负来产生全0和全1。

2003年3月7日，Angus Duggan指出了右移操作的兼容性问题。 
 2005年5月3日，Randal E.Bryant提示我只有在`INT_MIN <= x - y <= INT_MAX`的先决条件下，那个炫酷版本的代码才算完善，并且他还提出了之前那个较朴实的解法。这些问题都需要在炫酷版本的代码中考虑到。 
 2005年7月6日，Nigel Horspoon注意到gcc在一款奔腾处理器上编译这份代码时，由于其计算(x-y)的方式，而产生了和之前的简单写法相同的代码。 
 2008年7月9日，Vincent Lefèvre指出上一个版本中，即`r = y + ((x - y) & -(x < y))`，存在减法溢出的潜在风险。 
 2009年6月2日，Timothy B. Terriberry建议使用异或来代替加减以避免强制类型转换和溢出的风险。

***

### Compute the minimum (min) or maximum (max) of two integers without branching



```
int x;  // we want to find the minimum of x and y
int y;   
int r;  // the result goes here 

r = y ^ ((x ^ y) & -(x < y)); // min(x, y)
```

On some rare machines where branching is very expensive and no condition move instructions exist, the above expression might be faster than the obvious approach, r = (x < y) ? x : y, even  though it involves two more instructions.   (Typically, the obvious approach is best, though.) It works because if x < y,  then -(x < y) will be all ones,  so r = y ^ (x ^ y) & ~0 = y ^ x ^ y = x.   Otherwise, if x >= y,  then -(x < y) will be all zeros,  so r = y ^ ((x ^ y) & 0) = y.   On some machines, evaluating (x < y) as 0  or 1 requires a branch instruction, so there may be no advantage.  

To find the maximum, use:

```
r = x ^ ((x ^ y) & -(x < y)); // max(x, y)
```



#### Quick and dirty versions:

If you know that INT_MIN <= x - y <= INT_MAX, then you can use the following, which  are faster because (x - y) only needs to be evaluated once.  

```
r = y + ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1))); // min(x, y)
r = x - ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1))); // max(x, y)
```

Note that the 1989 ANSI C specification doesn't specify the result of  signed right-shift, so these aren't portable. If exceptions are thrown on overflows, then the values of x and y should be unsigned or cast to unsigned for the subtractions to avoid unnecessarily throwing an exception, however the right-shift needs a signed operand to produce all one bits when negative, so cast  to signed there.

On March 7, 2003, Angus Duggan pointed out the right-shift portability issue. On May 3, 2005, Randal E. Bryant alerted me to the need for the  precondition, INT_MIN <= x - y <= INT_MAX,  and suggested the non-quick and dirty version as a fix.   Both of these issues concern only the quick and dirty version.   Nigel Horspoon observed on July 6, 2005 that gcc produced the  same code on a Pentium as the obvious solution because of how it evaluates (x < y).  On July 9, 2008 Vincent Lefèvre pointed out the potential for overflow exceptions with subtractions in  r = y + ((x - y) & -(x < y)), which was the previous version. Timothy B. Terriberry suggested using xor rather than add and subract to avoid casting and the risk of overflows on June 2, 2009.

http://graphics.stanford.edu/~seander/bithacks.html
