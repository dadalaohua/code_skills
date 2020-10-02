# 计算两个数中的最小或者最大值(无判断分支) 

## 计算两个数中的最小或者最大值(无判断分支) 

```
int x;  //需要取最小（大）值的两个数
int y; 
int r;  //比较结果

r = y ^ ((x ^ y) & -(x < y)); // min(x, y)
```
在某些机器，有判断分支的的指令花的时间会很长而且没有条件移动指令，所以上面这个方法会比下面这个方法快, r = (x < y) ? x : y.
要得到最大值：
```
r = x ^ ((x ^ y) & -(x < y)); // max(x, y)
```
假如你知道INT_MIN <= x-y <= INT_MAX 而不会溢出,那么你可以用下面的方法会更快。
```
r = y + ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1))); // min(x, y)
r = x - ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1))); // max(x, y) 
```

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
