# 根据条件取某数的相反数（无判断分支） 

根据条件取某数的相反数（无判断分支） 
```
bool fDontNegate;  //条件flag.
int v;             // 输入的数.
int r;             // result = fDontNegate ? v : -v;

r = (fDontNegate ^ (fDontNegate - 1)) * v;
```
如果只有flag为真时求v的相反数，可以用下面的方法: 
```
bool fNegate;  // 条件flag.
int v;         // 输入的数.
int r;         // result = fNegate ? -v : v;

r = (v ^ -fNegate) + fNegate;
```
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