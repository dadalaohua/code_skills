#  计算奇偶校验位(查表法) 

```
static const bool ParityTable256[256] =
{
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};

unsigned char b;  // byte value to compute the parity of
                  // 需要计算的值保存在变量b中
bool parity = ParityTable256[b];

// OR, for 32-bit words:
// 或者，32位字长下
unsigned int v;
v ^= v >> 16;
v ^= v >> 8;
bool parity = ParityTable256[v & 0xff];

// Variation:
// 变种
unsigned char * p = (unsigned char *) &v;
parity = ParityTable256[p[0] ^ p[1] ^ p[2] ^ p[3]];
```
2005年5月3日，Randal E.Bryant提出了使用变量p的那个变种版本。
2005年9月27日，Bruce Rawles发现了表中有一处变量名拼写错误，并获得了10美刀的奖励。
2006年10月9日，Fabrice Bellard提出了32位字长的变种，这个变种只需要查表一次；最初的版本需要4次查表（每个字节一次），明显更慢一些。
2009年7月14日，Hallvard Furuseth提出用宏来精简表的长度。

***

### Compute parity by lookup table

```
static const bool ParityTable256[256] = 
{
#   define P2(n) n, n^1, n^1, n
#   define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#   define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};

unsigned char b;  // byte value to compute the parity of
bool parity = ParityTable256[b];

// OR, for 32-bit words:
unsigned int v;
v ^= v >> 16;
v ^= v >> 8;
bool parity = ParityTable256[v & 0xff];

// Variation:
unsigned char * p = (unsigned char *) &v;
parity = ParityTable256[p[0] ^ p[1] ^ p[2] ^ p[3]];
```

Randal E. Bryant encouraged the addition of the (admittedly) obvious  last variation with variable p on May 3, 2005.  Bruce Rawles found a typo  in an instance of the table variable's name on September 27, 2005, and  he received a $10 bug bounty.  On October 9, 2006, Fabrice Bellard  suggested the 32-bit variations above, which require only one table lookup; the previous version had four lookups (one per byte) and were slower. On July 14, 2009 Hallvard Furuseth suggested the macro compacted table.

http://graphics.stanford.edu/~seander/bithacks.html