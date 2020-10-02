# 设置或清除位(无判断分支) 

## 设置或清除位(无判断分支)
```
bool f;         // 条件flag
unsigned int m; // 位掩码
unsigned int w; // 需要被修改的数:  if (f) w |= m; else w &= ~m; 
 
w ^= (-f ^ w) & m;
 
// 或者:
w = (w & ~m) | (-f & m);
```
因为有些cpu的系统架构使用if分支判断时会使用多次操作。例如：非正式的测试中AMD Athlon XP 2100+显示出使用上述方法比用if快5-10%, Intel Core 2 Duo 则是快16%。
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