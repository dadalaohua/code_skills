# 设置或清除位(无判断分支) 

```
bool f;         // conditional flag
                // 使用这个标志来表示条件判断
unsigned int m; // the bit mask
                // 位掩码
unsigned int w; // the word to modify:  if (f) w |= m; else w &= ~m;
                // 需要进行操作的变量

w ^= (-f ^ w) & m;

// OR, for superscalar CPUs:
// 在一些超标量架构的CPU上，也可以这样:
w = (w & ~m) | (-f & m);
```
在某些架构上，不使用分支指令会比使用分支指令多出2个甚至更多的操作。举个例子，通过非正式速度测试表明，AMD Athlon™ XP 2100+能快5-10%； Intel Core 2 Duo的超标量版本能比能比前一个快16%。 
 2003年12月11日，Gelnn Slayden告诉了我第一个算法。 
 2007年4月3日，Marco Yu给我分享了超标量版本的算法，在两天后给我提出了一处显示排版错误。

***

### Conditionally set or clear bits without branching

```
bool f;         // conditional flag
unsigned int m; // the bit mask
unsigned int w; // the word to modify:  if (f) w |= m; else w &= ~m; 

w ^= (-f ^ w) & m;

// OR, for superscalar CPUs:
w = (w & ~m) | (-f & m);
```

On some architectures, the lack of branching can more than make up for what appears to be twice as many operations.  For instance, informal  speed tests on an AMD Athlon™ XP 2100+ indicated it was 5-10%  faster.  An Intel Core 2 Duo ran the superscalar version about 16%  faster than the first. Glenn Slayden informed me of the first expression on  December 11, 2003.  Marco Yu shared the superscalar version with me on  April 3, 2007 and alerted me to a typo 2 days later.

http://graphics.stanford.edu/~seander/bithacks.html