# 计算一个数里位被置1的个数（使用64位机器指令计算14位，24位，32位数的置1的位数） 

```
unsigned int v; // count the number of bits set in v
                // 待检测的数，计算变量v的二进制中1的个数
unsigned int c; // c accumulates the total bits set in v
                // 位被置1的总数，保存计算的结果

// option 1, for at most 14-bit values in v:
//公式1 计算最大为14位的数:
c = (v * 0x200040008001ULL & 0x111111111111111ULL) % 0xf;

// option 2, for at most 24-bit values in v:
//公式2 计算最大为24位的数:
c =  ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
c += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) 
     % 0x1f;

// option 3, for at most 32-bit values in v:
//公式3 计算最大为32位的数:
c =  ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
c += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) % 
     0x1f;
c += ((v >> 24) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
```
这个算法需要在支持快速模除的64位CPU上才能达到高性能的效果。第一种情况只需要3次操作，第二种需要10次，第三种需要15次。

 

Rich Schroeppel最初想出了一个和第一种类似的9位长版本，见Programming Hacks的这一章节[Beeler, M., Gosper, R. W., and Schroeppel, R. HAKMEM. MIT AI Memo 239, Feb. 29, 1972](http://www.inwap.com/pdp10/hbaker/hakmem/hakmem.html)。他的想法是收此启发，并最终由Sean Anderson完成设计。

 

2005年5月3日，Randal E.Byrant提了几个bug修复补丁。

 

2007年2月1日，Bruce Dawson对原来的12位版本做了一些调整，将其变成了兼容性更好的14位版本，并且保持操作数不变。

***

### Counting bits set in 14, 24, or 32-bit words using 64-bit instructions



```
unsigned int v; // count the number of bits set in v
unsigned int c; // c accumulates the total bits set in v

// option 1, for at most 14-bit values in v:
c = (v * 0x200040008001ULL & 0x111111111111111ULL) % 0xf;

// option 2, for at most 24-bit values in v:
c =  ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
c += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) 
     % 0x1f;

// option 3, for at most 32-bit values in v:
c =  ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
c += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) % 
     0x1f;
c += ((v >> 24) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
```

This method requires a 64-bit CPU with fast modulus division to be efficient. The first option takes only 3 operations; the second option takes 10; and the third option takes 15.

Rich Schroeppel originally created a 9-bit version, similiar to option 1; see the Programming Hacks section of  [ Beeler, M., Gosper, R. W., and Schroeppel, R.  HAKMEM. MIT AI Memo 239, Feb. 29, 1972.](http://www.inwap.com/pdp10/hbaker/hakmem/hakmem.html) His method was the inspiration for the variants above, devised by Sean Anderson.  Randal E. Bryant offered a couple bug fixes on May 3, 2005.  Bruce Dawson tweaked what had been a 12-bit version and made it suitable for 14 bits using the same number of operations on  Feburary 1, 2007.

http://graphics.stanford.edu/~seander/bithacks.html