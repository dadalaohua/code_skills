# 位的反转（朴素方法）
```
unsigned int v;     // input bits to be reversed
                    // 需要翻转的数值输入保存在这里
unsigned int r = v; // r will be reversed bits of v; first get LSB of v
                    // 将v反转后的结果保存在变量r中；首先会算出v的最低有效位（注：推测此处的LSB是指Least Significant Bit，故翻译为最低有效位，不太确定）
int s = sizeof(v) * CHAR_BIT - 1; // extra shift needed at end
                                  // 最终需要额外左移的长度

for (v >>= 1; v; v >>= 1)
{
  r <<= 1;
  r |= v & 1;
  s--;
}
r <<= s; // shift when v's highest bits are zero
         // v的高位可能存在0，所以这里需要左移
```

2004年10月15日，Michael Hoisie指出了一个最初版本的bug。

2005年5月3日，Randal E. Bryant提议去除掉一处多余的操作。

2005年5月18日，Behdad Esfabod指出一个改动，可以让少循环一次。

2007年2月6日，Liyong Zhou给出了一个更好的版本，如果v不是0的话才进入循环，而不是循环遍历完所有位，这样可以早一些退出循环。

***

### Reverse bits the obvious way



```
unsigned int v;     // input bits to be reversed
unsigned int r = v; // r will be reversed bits of v; first get LSB of v
int s = sizeof(v) * CHAR_BIT - 1; // extra shift needed at end

for (v >>= 1; v; v >>= 1)
{   
  r <<= 1;
  r |= v & 1;
  s--;
}
r <<= s; // shift when v's highest bits are zero
```



On October 15, 2004, Michael Hoisie pointed out a bug in the original version. Randal E. Bryant suggested removing an extra operation on May 3, 2005.   Behdad Esfabod suggested a slight change that eliminated one iteration of the loop on May 18, 2005.  Then, on February 6, 2007, Liyong Zhou suggested a  better version that loops while v is not 0, so rather than iterating over  all bits it stops early.

http://graphics.stanford.edu/~seander/bithacks.html