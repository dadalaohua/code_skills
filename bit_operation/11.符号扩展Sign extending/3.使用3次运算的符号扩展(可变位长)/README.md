# 使用3次运算的符号扩展(可变位长)

这个技巧由于乘法和除法的关系，在某些机器上可能会慢一些。这个版本准确来说需要4次运算。如果你知道你的初始位长大于1的话，那么你就可以用`r = (x * multipliers[b]) / multipliers[b]`这种方法来完成符号扩展。这个技巧是基于一个事先初始化的表，它只需要3次操作。

```
unsigned b; // number of bits representing the number in x
            // 变量b指定需要扩展的位长
int x;      // sign extend this b-bit number to r
            // 需要将变量x中的数值符号扩展的结果保存到r中
int r;      // resulting sign-extended number
            // 存放计算结果到变量r
#define M(B) (1U << ((sizeof(x) * CHAR_BIT) - B)) // CHAR_BIT=bits/byte
                                                  // CHAR_BIT是指一个字节中有多少位
static int const multipliers[] =
{
  0,     M(1),  M(2),  M(3),  M(4),  M(5),  M(6),  M(7),
  M(8),  M(9),  M(10), M(11), M(12), M(13), M(14), M(15),
  M(16), M(17), M(18), M(19), M(20), M(21), M(22), M(23),
  M(24), M(25), M(26), M(27), M(28), M(29), M(30), M(31),
  M(32)
}; // (add more if using more than 64 bits)
   // (如果需要支持到64位的话，可以继续添加)
static int const divisors[] =
{
  1,    ~M(1),  M(2),  M(3),  M(4),  M(5),  M(6),  M(7),
  M(8),  M(9),  M(10), M(11), M(12), M(13), M(14), M(15),
  M(16), M(17), M(18), M(19), M(20), M(21), M(22), M(23),
  M(24), M(25), M(26), M(27), M(28), M(29), M(30), M(31),
  M(32)
}; // (add more for 64 bits)
   // (继续添加以支持64位)
#undef M
r = (x * multipliers[b]) / divisors[b];
```
下面这个变种可能兼容性不高，但在某些支持算术右移架构，可以保持符号位的系统上，这个变种会更快一些。
```
const int s = -b; // OR:  sizeof(x) * CHAR_BIT - b;
                  // 或者：sizeof(x) * CHAR_BIT - b;
r = (x << s) >> s;
```
2005年3月3日，Randal E.Bryant指出了一个最初版本的bug(即使用查表的版本)，当x和b都为1时，这个技巧就会失效。
***
# Sign extending from a variable bit-width in 3 operations

The following may be slow on some machines, due to the effort required for multiplication and division.  This version is 4 operations.  If you know that your initial bit-width, b, is greater than 1, you might do this type of sign extension in 3 operations by using  r = (x * multipliers[b]) / multipliers[b], which requires only one array lookup.

```
unsigned b; // number of bits representing the number in x
int x;      // sign extend this b-bit number to r
int r;      // resulting sign-extended number
#define M(B) (1U << ((sizeof(x) * CHAR_BIT) - B)) // CHAR_BIT=bits/byte
static int const multipliers[] = 
{
  0,     M(1),  M(2),  M(3),  M(4),  M(5),  M(6),  M(7),
  M(8),  M(9),  M(10), M(11), M(12), M(13), M(14), M(15),
  M(16), M(17), M(18), M(19), M(20), M(21), M(22), M(23),
  M(24), M(25), M(26), M(27), M(28), M(29), M(30), M(31),
  M(32)
}; // (add more if using more than 64 bits)
static int const divisors[] = 
{
  1,    ~M(1),  M(2),  M(3),  M(4),  M(5),  M(6),  M(7),
  M(8),  M(9),  M(10), M(11), M(12), M(13), M(14), M(15),
  M(16), M(17), M(18), M(19), M(20), M(21), M(22), M(23),
  M(24), M(25), M(26), M(27), M(28), M(29), M(30), M(31),
  M(32)
}; // (add more for 64 bits)
#undef M
r = (x * multipliers[b]) / divisors[b];
```

The following variation is not portable,  but on architectures that employ an arithmetic right-shift, maintaining the sign, it should be fast.  

```
const int s = -b; // OR:  sizeof(x) * CHAR_BIT - b;
r = (x << s) >> s;
```

Randal E. Bryant pointed out a bug on May 3, 2005 in an earlier version  (that used multipliers[] for divisors[]), where it failed on the case of  x=1 and b=1. 

http://graphics.stanford.edu/~seander/bithacks.html
