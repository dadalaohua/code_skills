# 根据条件取某数的相反数（无判断分支） 

在不使用分支指令的情况下，你可能会需要判断某个flag是否false，来将某个变量置为其相反数：
```
bool fDontNegate;  // Flag indicating we should not negate v.
                   // Flag标志，用于判断我们是否需要将变量v置为相反数
int v;             // Input value to negate if fDontNegate is false.
                   // 输入的数值保存在v中，当fDontNegate为false时，就将变量v置为相反数
int r;             // result = fDontNegate ? v : -v;

r = (fDontNegate ^ (fDontNegate - 1)) * v;
```
如果只有flag为真时求v的相反数，可以用下面的方法: 
```
bool fNegate;  // Flag indicating if we should negate v.
               // Flag标志，用于判断我们是否需要将变量v置为相反数
int v;         // Input value to negate if fNegate is true.
               // 输入的数值保存在v中，当fDontNegate为true时，就将变量v置为相反数
int r;         // result = fNegate ? -v : v;

r = (v ^ -fNegate) + fNegate;
```
2009年6月2日，Avraham Plotnitzky建议我添加第一个版本。
2009年6月8日，为了去除掉乘法，我想出了第二个版本。
2009年11月26日，Alfonso De Gregorio指出某个地方缺少括号。这是一个合理的bug，所以它得到了指出bug的赏金。
***

### Conditionally negate a value without branching

If you need to negate only when a flag is false, then use the following  to avoid branching:

```
bool fDontNegate;  // Flag indicating we should not negate v.
int v;             // Input value to negate if fDontNegate is false.
int r;             // result = fDontNegate ? v : -v;

r = (fDontNegate ^ (fDontNegate - 1)) * v;
```

If you need to negate only when a flag is true, then use this:

```
bool fNegate;  // Flag indicating if we should negate v.
int v;         // Input value to negate if fNegate is true.
int r;         // result = fNegate ? -v : v;

r = (v ^ -fNegate) + fNegate;
```

Avraham Plotnitzky suggested I add the first version on June 2, 2009.   Motivated to avoid the multiply, I came up with the second version on June 8, 2009.  Alfonso De Gregorio pointed out that some parens were missing on November 26, 2009, and received a bug bounty.

http://graphics.stanford.edu/~seander/bithacks.html