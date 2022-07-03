# C语言宏定义使用总结与递归宏

https://www.jianshu.com/p/442f35ba8a6f

C语言的宏可以用来做宏定义、条件编译和文件包含，本文主要总结宏定义`#define`的用法。

以下例子通过Xcode12.0测试，gnu99标准。

## 特殊符号`#`和`##`

在一个宏参数前面使用`#`号，则此参数会变为字符串：



```c
#define LOG(X) printf(#X)
LOG(abc);   // printf("abc");
```

`##`是连接符号，可在宏参数前后使用：



```c
#define DefineValue(NAME, TYPE, VAL) TYPE NAME##_##TYPE = VAL;

DefineValue(aaa, int, 91) // int aaa_int = 91;
DefineValue(aaa, float, 3.26)  // float aaa_float = 3.26;
printf("%d--%f\n", aaa_int, aaa_float); // 91--3.260000
```

## 变长参数`__VA_ARGS__`和`...`



```c
#define PrintStderr(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

int aa = 1;
int bb = 2;
PrintStderr("%d--%d\n", aa, bb); // fprintf(stderr, "%d--%d\n", aa, bb)
PrintStderr("Huimao Chen\n"); // fprintf(stderr, "Huimao Chen\n");
```

简单来说，`...`表示所有剩下的参数，`__VA_ARGS__`被宏定义中的`...`参数所替换。

需要注意的是，上面例子用`##`连接逗号和后面的`__VA_ARGS__`，这在c语言的GNU扩展语法里是一个特殊规则：当`__VA_ARGS__`为空时，会消除前面这个逗号。如果上面例子的宏定义去掉`##`号，第一个例子无影响，但第二个例子则会替换成`fprintf(stderr, "Huimao Chen", );`多出的一个逗号导致编译失败。

## do{}while(0)

宏定义里可以有多行语句，`do{}while(0)`就能保证了这个宏成为独立的语法单元。
 如果有这样一个宏定义  `#define SWAP(A, B) int tmp = A; A = B; B = tmp;`，虽然如下代码能正常执行：



```c
int aa = 1;
int bb = 2;
SWAP(aa, bb);
printf("%d--%d\n", aa, bb); // 2--1
```

但是，下面的代码就有问题了，编译报错：



```c
int aa = 1;
int bb = 2;
if (aa < bb)
    SWAP(aa, bb);
printf("%d--%d\n", aa, bb);
```

此时把这个宏改成如下这种形式就能正常运行：
 `#define SWAP(A, B) do {int tmp = A; A = B; B = tmp;} while(0)`

## 参数用括号保护

宏定义只是简单的替换，通过替换可能会导致运算优先级不符合预期，此时需要用括号保护参数。



```c
#define MAX(A, B) A > B ? A : B
int aa = 2;
int bb = 3;
printf("%d\n", 2 * MAX(aa, bb));
// printf("%d\n", 2 * aa > bb ? aa : bb);
// printf("%d\n", 2 * 2 > 3 ? 2 : 3);
// printf("%d\n", 4 > 3 ? 2 : 3);
// 2
```

上面的例子最后输出的是2，与预期的结果6不符，此时把宏定义改为如下形式就能解决问题：



```c
#define MAX(A, B) ((A) > (B) ? (A) : (B))
int aa = 2;
int bb = 3;
printf("%d\n", 2 * MAX(aa, bb));
// printf("%d\n", 2 * ((aa) > (bb) ? (aa) : (bb)));
// printf("%d\n", 2 * ((2) > (3) ? (2) : (3)));
// printf("%d\n", 2 * (3));
// 6
```

## `({})`包裹语句

GNU扩展语法。有时候，宏的参数可以是个复合结构，而参数可能有多次取值。如果传入的宏参数是一个函数，则这个函数会有多次调用：



```c
#define MAX(A, B) ((A) > (B) ? (A) : (B))
int aa = 5;
int bb = MAX(2, foo(aa)); // 函数foo被调用了两次
```

为了防止此类副作用，可以改写为如下形式：



```c
#define MAX(A, B) ({ __typeof__(A) __a = (A); \
                     __typeof__(B) __b = (B); \
                     __a > __b ? __a : __b; })
```

`({})`在顺序执行语句之后，返回最后一条表达式的值，这也是其区别于`do{}while(0)`的地方。

## 嵌套使用宏

在使用了`#` 或`##`的宏中，如果宏的参数是另一个宏，则会阻止另一个宏展开。为了**保证参数优先展开**，需要多嵌套一层宏定义。具体可以看如下例子：



```c
#define Stringify(A) _Stringify(A)
#define _Stringify(A) #A

#define Concat(A, B) _Concat(A, B)
#define _Concat(A, B) A##B

printf("%s\n", Stringify(Concat(Hel, lo))); // 输出:Hello
// printf("%s\n", Stringify(Hello));
// printf("%s\n", _Stringify(Hello));
// printf("%s\n", "Hello");
// Hello

printf("%s\n", _Stringify(Concat(Hel, lo))); // 输出:Concat(Hel, lo)
// printf("%s\n", "Concat(Hel, lo)");
// Concat(Hel, lo)
```

## 宏的递归展开

虽然宏定义只是简单替换，但也有令人眼前一亮的小技巧，如模式匹配、参数检测、递归宏等等。这里只介绍递归宏，只要看懂了这篇文章的递归宏，遇到其他宏理解起来也是小意思。以下例子参考了我的开源框架[HMLog](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Fchenhuimao%2FHMLog)，带上了前缀`HM`。

在介绍递归宏之前，先来介绍一个获取宏参数个数的技巧。

### 获取宏参数个数

这是一个常见的宏，其构建思维广泛使用于各种宏功能。下面的宏适用于1到10个参数，最后一个例子给出了解释：



```c
#define HMMacroArgCount(...) _HMMacroArgCount(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define _HMMacroArgCount(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, COUNT, ...) COUNT

HMMacroArgCount(a); // 1;
HMMacroArgCount(a, a); // 2;
HMMacroArgCount(a, b, c, d); // 4;
// MacroArgCount(a, b, c, d); >>> _MacroArgCount(a, b, c, d, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
// _MacroArgCount定义里是固定取第11个参数，这里命名为COUNT，而上面第11个参数就是4，故最终展开结果为4;
```

举个实际应用的例子：



```c
double average(int num, ...) {
    va_list valist;
    double sum = 0.0;
    va_start(valist, num);
    for (int i = 0; i < num; ++i) {
       sum += va_arg(valist, int);
    }
    va_end(valist);
    return sum / num;
}
#define HMAverage(...) average(HMMacroArgCount(__VA_ARGS__), __VA_ARGS__)

double result = average(5, 10, 20, 30, 40, 50);
printf("%f\n", result); // 30.000000

// 可以少输入一个总数5，预编译期间就替换为double result2 = average(5, 10, 20, 30, 40, 50);
double result2 = HMAverage(10, 20, 30, 40, 50);
printf("%f\n", result2); // 30.000000
```

`average`是个可变参数的函数，计算输入整数的平均值。直接调用可变参数函数往往需要传入参数的长度。使用宏`HMAverage`，则省略了这个长度参数，在函数调用频繁的情况下大大降低了出错概率，而且是在预编译期间完成替换，并不影响实际运行速度。

此时`HMMacroArgCount`并不支持0个参数的情况，其实根据前面总结的规律稍作修改就可以支持0个参数，留给读者思考。

接下来正式介绍递归宏，这里给出两种方法。

### 1. 连接宏的参数个数，定义一系列结构相似的宏。

我需要一个`HMPrint`宏，输入任意个整数（这个例子是5个以内），就能省略格式化参数，按照指定格式打印出来。



```c
#define HMMacroArgCount(...) _HMMacroArgCount(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define _HMMacroArgCount(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, COUNT, ...) COUNT

#define HMStringify(A) _HMStringify(A)
#define _HMStringify(A) #A

#define HMConcat(A, B) _HMConcat(A, B)
#define _HMConcat(A, B) A##B

#define HMPrint(...) printf(HMStringify(_HMFormat(__VA_ARGS__)), __VA_ARGS__)
#define _HMFormat(...) HMConcat(_HMFormat, HMMacroArgCount(__VA_ARGS__))(__VA_ARGS__)

#define _HMFormat1(_0)                  _0->%d\n
#define _HMFormat2(_0, _1)              _HMFormat1(_0)_1->%d\n
#define _HMFormat3(_0, _1, _2)          _HMFormat2(_0, _1)_2->%d\n
#define _HMFormat4(_0, _1, _2, _3)      _HMFormat3(_0, _1, _2)_3->%d\n
#define _HMFormat5(_0, _1, _2, _3, _4)  _HMFormat4(_0, _1, _2, _3)_4->%d\n

int a = 1991, b = 3, c = 26;
HMPrint(a, b, c); // 预编译时被替换为 printf("a->%d\nb->%d\nc->%d\n", a, b, c);
//a->1991
//b->3
//c->26
```

根据定义，`HMPrint`展开后就是`printf`函数，后面的参数部分保持不变。前面格式化宏`_HMFormat`用连接符`##`把`_HMFormat`和`HMMacroArgCount(__VA_ARGS__)`连接起来，后者返回参数的个数，如果`HMPrint`传入3个参数，连接后变为`_HMFormat3`并传入原始参数。把`_HMFormat3`前两个参数传递给`_HMFormat2`，第3个参数替换为`c->%d\n`，继续就是`_HMFormat2`展开，依次类推，直到格式化部分为`HMStringify(a->%d\nb->%d\nc->%d\n)`，最终变为`"a->%d\nb->%d\nc->%d\n"`。

为了帮助理解，我这里给出展开的过程，只需让依次让参数优先展开，就能得到想要的结果：



```c
// 依次替换展开宏，参数优先展开
HMPrint(a, b, c);
printf(HMStringify(_HMFormat(a, b, c)), a, b, c);
printf(HMStringify(HMConcat(_HMFormat, HMMacroArgCount(a, b, c))(a, b, c)), a, b, c);
printf(HMStringify(HMConcat(_HMFormat, 3)(a, b, c)), a, b, c);
printf(HMStringify(_HMFormat3(a, b, c)), a, b, c);
printf(HMStringify(_HMFormat2(a, b)c->%d\n), a, b, c);
printf(HMStringify(_HMFormat1(a)b->%d\nc->%d\n), a, b, c);
printf(HMStringify(a->%d\nb->%d\nc->%d\n), a, b, c);
printf(_HMStringify(a->%d\nb->%d\nc->%d\n), a, b, c);
printf("a->%d\nb->%d\nc->%d\n", a, b, c);
```

`_HMFormat`也可以写成这种方式，更容易理解：



```c
#define _HMFormat1(_0)                  _0->%d\n
#define _HMFormat2(_0, _1)              _0->%d\n_1->%d\n
#define _HMFormat3(_0, _1, _2)          _0->%d\n_1->%d\n_2->%d\n
#define _HMFormat4(_0, _1, _2, _3)      _0->%d\n_1->%d\n_2->%d\n_3->%d\n
#define _HMFormat5(_0, _1, _2, _3, _4)  _0->%d\n_1->%d\n_2->%d\n_3->%d\n_4->%d\n

// 再次给出这种方式下展开的过程，可以看到_HMFormat3一次到位替换为需要的格式
HMPrint(a, b, c);
printf(HMStringify(_HMFormat(a, b, c)), a, b, c);
printf(HMStringify(HMConcat(_HMFormat, HMMacroArgCount(a, b, c))(a, b, c)), a, b, c);
printf(HMStringify(HMConcat(_HMFormat, 3)(a, b, c)), a, b, c);
printf(HMStringify(_HMFormat3(a, b, c)), a, b, c);
printf(HMStringify(a->%d\nb->%d\nc->%d\n), a, b, c);
printf(_HMStringify(a->%d\nb->%d\nc->%d\n), a, b, c);
printf("a->%d\nb->%d\nc->%d\n", a, b, c);
```

不建议用后面这种方式，一是递归写法更加简洁统一；二是结合`HMMacroArgCount`这个宏一起可以扩展成支持10个参数的`HMPrint`，此时只需要测试最多参数的例子，没有出错就几乎保证了所有这类宏都没写错。再次强调一点，宏的递归展开只发生在预编译期间，这种递归并不影响运行时效率。

### 2. 利用宏的延迟展开和多次扫描

这种方法较难理解，还是用`HMPrint`的例子：



```c
#define HMStringify(A) _HMStringify(A)
#define _HMStringify(A) #A

#define HMConcat(A, B) _HMConcat(A, B)
#define _HMConcat(A, B) A##B

#define HMMacroArgCheck(...) _HMMacroArgCheck(__VA_ARGS__, N, N, N, N, N, N, N, N, N, 1)
#define _HMMacroArgCheck(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, TARGET, ...) TARGET

#define HMPrint(...) printf(HMStringify(HMExpand(HMForeach(_HMFormat, __VA_ARGS__))), __VA_ARGS__)
#define _HMFormat(A) A->%d\n

#define HMForeach(MACRO, ...) HMConcat(_HMForeach, HMMacroArgCheck(__VA_ARGS__)) (MACRO, __VA_ARGS__)
#define _HMForeach() HMForeach
#define _HMForeach1(MACRO, A) MACRO(A)
#define _HMForeachN(MACRO, A, ...) MACRO(A)HMDefer(_HMForeach)() (MACRO, __VA_ARGS__)

#define HMEmpty()
#define HMDefer(ID) ID HMEmpty()

#define HMExpand(...)   _HMExpand1(_HMExpand1(_HMExpand1(__VA_ARGS__)))
#define _HMExpand1(...) _HMExpand2(_HMExpand2(_HMExpand2(__VA_ARGS__)))
#define _HMExpand2(...) _HMExpand3(_HMExpand3(_HMExpand3(__VA_ARGS__)))
#define _HMExpand3(...) __VA_ARGS__

int a = 1991, b = 3, c = 26;
HMPrint(a, b, c); // 预编译时被替换为 printf("a->%d\nb->%d\nc->%d\n", a, b, c);
//a->1991
//b->3
//c->26

int a1 = 11, a2 = 22, a3 = 33, a4 = 44, a5 = 55, a6 = 66, a7 = 77, a8 = 88, a9 = 99, a10 = 100;
HMPrint(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
//a1->11
//a2->22
//a3->33
//a4->44
//a5->55
//a6->66
//a7->77
//a8->88
//a9->99
//a10->100
```

`HMMacroArgCheck`用于检测参数数量，如果是1个参数则返回1，当参数大于1个，且小于等于10个的情况下返回N。`HMDefer`用于延迟展开，而`HMExpand`是为了多次扫描宏，理解这种技巧需要知道宏展开的一般规则，可以阅读[这个系列的文章](https://links.jianshu.com/go?to=https%3A%2F%2Fzhuanlan.zhihu.com%2Fp%2F26978356)，本文不再赘述。`HMForeach(MACRO, ...)`这个宏的用处是每个参数都会被传递给`MACRO`宏，为`HMForeach(MACRO, ...)`举个简化的例子用于理解用处：



```c
#define Increase(X) X += 1; // 定义一个宏，准备用来处理每一个参数。注意最后有分号
int aa = 10, bb = 20, cc = 30;
// 使用HMForeach需要有HMExpand包裹起来，以便多次扫描顺利展开
HMExpand(HMForeach(Increase, aa, bb, cc))
// 相当于：Increase(aa)Increase(bb)Increase(cc)
// 最后变为：aa += 1;bb += 1;cc += 1;
    
printf("%d--%d--%d", aa, bb, cc); // 输出：11--21--31
```

这种方法不需要去写`_HMFormat1`、`_HMFormat2`、`_HMFormat3`等这一类相似结构的宏，支持参数个数取决于`HMMacroArgCheck`，所以增加支持的参数数量变得轻而易举，当参数比较多的情况使用这种方式更加方便。不足之处是只能对每个参数做相同的处理，而第1种方式是可以对每个参数做不同处理的。

最后，我同样给出展开的过程，但这并非实际展开过程，比如忽略了`HMExpand`展开的时机，仅在最后直接消除：



```c
// 这并非实际展开过程，比如忽略了HMExpand展开的时机，仅在最后直接消除
HMPrint(a, b, c);
printf(HMStringify(HMExpand(HMForeach(_HMFormat, a, b, c))), a, b, c);
printf(HMStringify(HMExpand(HMConcat(_HMForeach, HMMacroArgCheck(a, b, c)) (_HMFormat, a, b, c))), a, b, c);
printf(HMStringify(HMExpand(HMConcat(_HMForeach, N) (_HMFormat, a, b, c))), a, b, c);
printf(HMStringify(HMExpand(_HMForeachN (_HMFormat, a, b, c))), a, b, c);
printf(HMStringify(HMExpand(_HMFormat(a)HMDefer(_HMForeach)() (_HMFormat, b, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\n_HMForeach() (_HMFormat, b, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nHMForeach (_HMFormat, b, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nHMConcat(_HMForeach, HMMacroArgCheck(b, c)) (_HMFormat, b, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nHMConcat(_HMForeach, N) (_HMFormat, b, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\n_HMForeachN (_HMFormat, b, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\n_HMFormat(b)HMDefer(_HMForeach)() (_HMFormat, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nb->%d\n_HMForeach() (_HMFormat, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nb->%d\nHMForeach (_HMFormat, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nb->%d\nHMConcat(_HMForeach, HMMacroArgCheck(c)) (_HMFormat, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nb->%d\nHMConcat(_HMForeach, 1) (_HMFormat, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nb->%d\n_HMForeach1 (_HMFormat, c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nb->%d\n_HMFormat(c))), a, b, c);
printf(HMStringify(HMExpand(a->%d\nb->%d\nc->%d\n)), a, b, c);
printf(HMStringify(a->%d\nb->%d\nc->%d\n), a, b, c);
printf(_HMStringify(a->%d\nb->%d\nc->%d\n), a, b, c);
printf("a->%d\nb->%d\nc->%d\n", a, b, c);
```

利用宏能写出很多有意思的代码，如果你是iOS开发者，强烈建议看看我写的一个最佳实践[HMLog](https://github.com/chenhuimao/HMLog)（有且仅有一个`HMLog.h`文件），另外也可以看[libextobjc](https://github.com/jspahrsummers/libextobjc)库对宏的使用。关于宏更多的使用技巧，可以查看[p99](https://gitlab.inria.fr/gustedt/p99/-/tree/master/tests)或[Boost preprocessor](https://www.boost.org/doc/libs/1_41_0/libs/preprocessor/doc/index.html)。

