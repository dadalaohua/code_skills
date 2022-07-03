# 宏定义黑魔法-从入门到奇技淫巧

[宏定义黑魔法-从入门到奇技淫巧 (1)](http://feng.zone/2017/05/17/%E5%AE%8F%E5%AE%9A%E4%B9%89%E9%BB%91%E9%AD%94%E6%B3%95-%E4%BB%8E%E5%85%A5%E9%97%A8%E5%88%B0%E5%A5%87%E6%8A%80%E6%B7%AB%E5%B7%A7-1/)

[宏定义黑魔法-从入门到奇技淫巧 (2)]()

[宏定义黑魔法-从入门到奇技淫巧 (3)](http://feng.zone/2017/05/20/%E5%AE%8F%E5%AE%9A%E4%B9%89%E9%BB%91%E9%AD%94%E6%B3%95-%E4%BB%8E%E5%85%A5%E9%97%A8%E5%88%B0%E5%A5%87%E6%8A%80%E6%B7%AB%E5%B7%A7-3/)

[宏定义黑魔法-从入门到奇技淫巧 (4)](http://feng.zone/2017/05/21/%E5%AE%8F%E5%AE%9A%E4%B9%89%E9%BB%91%E9%AD%94%E6%B3%95-%E4%BB%8E%E5%85%A5%E9%97%A8%E5%88%B0%E5%A5%87%E6%8A%80%E6%B7%AB%E5%B7%A7-4/)

[宏定义黑魔法-从入门到奇技淫巧 (5)](http://feng.zone/2017/05/21/%E5%AE%8F%E5%AE%9A%E4%B9%89%E9%BB%91%E9%AD%94%E6%B3%95-%E4%BB%8E%E5%85%A5%E9%97%A8%E5%88%B0%E5%A5%87%E6%8A%80%E6%B7%AB%E5%B7%A7-5/)

[宏定义黑魔法-从入门到奇技淫巧 (6)](http://feng.zone/2017/05/28/%E5%AE%8F%E5%AE%9A%E4%B9%89%E9%BB%91%E9%AD%94%E6%B3%95-%E4%BB%8E%E5%85%A5%E9%97%A8%E5%88%B0%E5%A5%87%E6%8A%80%E6%B7%AB%E5%B7%A7-6/)

# 宏定义黑魔法-从入门到奇技淫巧 (1)

# 楔子

最近在研究如何在 C++ 里边实现反射，结果发现了很多有意思的技巧。可惜其中相当一部分都是依赖于宏实现的，晦涩难懂。这个过程中断断续续查了很多资料，发现网上不管是中文还是英文都很少有资料对宏的用法有一个比较完整的介绍。特别是一些「奇技淫巧」类的惯用法。少数几个也没有原理上的分析，十分可惜。所以在这里将自己搜集到的东西整理成一个教程，以飨列位。随着教程的深入，你会发现宏的能力远超一般的认识。利用各种猥琐的技巧，可以使宏具有接近图灵完备语言的能力。



一般来说在 C++ 中是不提倡使用宏的，模板已经能够很好地替代宏的绝大多数功能了。宏由于其自身设计的原因，使用起来不仅晦涩难懂，而且还有很多难以预料的坑。那么现在是不是就没有学习宏的必要了呢？笔者认为答案是否定的。理由有三：其一，仍有一小部分功能模板无法替代宏来实现，且有的功能使用宏比模板更加的直观。其二，以前的遗留代码中有大量的宏，而这些库在今天依旧有着广泛的应用。其三，宏的很多惯用发思路清奇又猥琐，却又暗合编程语言理论，用来把玩也是很有趣的。

*友情提示：阅读本教程时，ISO C++ 标准 16.3 节也许会对你有所帮助。*

# 宏的定义

绝大多数人对于宏的概念仅仅停留在简单替换的程度上，例如：

```c
#define N 42

N
// ->
42
```

众所周知，这个宏的作用是找到源文件中所有的 `N` 然后将其替换为 42。然而，对于 C 和 C++ 的预处理需求来说，这种功能过于简单了。有时候我们希望能够根据不同的参数来进行某种模式的替换。这就产生了第二种宏，带参数的宏。例如：

```c
#define ADD(x, y) x + y

ADD(1, 2)
// ->
1 + 2
```

`ADD` 宏中与参数一致的部分被替换为了相应的内容。事实上，我们将前一种宏叫做 object-like 的宏（下略为 obj-like），后一种叫做 function-like 的宏（下略为 func-like）。一个标准的宏定义格式如下：

```c
// obj-like
#define 宏名 替换列表 换行符

//func-like
#define 宏名 ([标识符列表]) 替换列表 换行符
```

其中**替换列表**和**标识符列表**都是将字符串 token (如果对 token 这个概念比较陌生请看文章最后) 化以后的列表。区别在于标识符列表使用`,`作为不同参数之间的分割符。每一个参数都是一个 token 化的列表。

这里有两点值得注意的地方：1. 宏的内容会被 token 化成一个**替换列表**。也就是说，预处理器在处理宏展开时并不是以字符串的形式处理，而是以 token 列表的形式处理的。这对于我们理解宏的行为非常重要。例如，在宏中空白符只起到分割 token 的作用，空白符的多少对于预处理器是没有意义的：

```c
#define VAR_1 int     name;

VAR_1
// ->
int name;
```

2.宏定义以换行符结尾，这意味着一个宏定义不论多长都只能写在一行中，如果需要分行写，请使用 `\`，例如：

```c
#define MAIN      \
int main()        \
{                 \
    return 0;     \
}
```

此外，宏可以重复定义，但前提是两次定义的内容完全一致。例如：

```
// 合法的二次定义
#define FOO int foo;
#define FOO int       foo;

//重定义错误，有的编译器会给出警告并使用最后一次的宏定义
#define FOO int* foo;
#define FOO int foo;
```

# 宏的操作符

和 C, C++ 语言本体不同，宏有着它自己特有的两个操作符。下边简单地介绍一下。

## 字符串化操作符 `#`

有时候我们希望能够讲参数转换为字符串进行处理，`#` 可以将一个 token 字符串化。例如：

```
#define WARN_IF(EXP) \
    if (EXP) \
    {\
        fprintf (stderr, "Warning: " #EXP "\n"); \
    }\

WARN_IF (x/* const char* */ == "0")
// ->
if (x == "0") { fprintf (stderr, "Warning: " "x == \"0\"" "\n"); }
```

此处有几点需要注意：

1. `#`操作符并不是简单的添加双引号，它会自动对特殊字符进行转义。
2. `#`操作符只能对 func-like 的参数使用。
3. 由于参数会转化为 token 列表，所以前后的空白符都会被忽略，中间的空白符会被压缩为一个，注释会被忽略并变成一个空白符。

## Token 粘贴操作符

然后我们再学习一个新的操作符 `##`，`##` 可以将两个 token 合并为一个。合并新的 token 有什么用呢？它可以提供给你动态的生成 token 的能力，例如：

```
#define GETTER(x, T) T get_ ## x() {return this->x;}

GETTER(foo， const int)
//->
const int get_foo() {return this->foo;}
```

此处通过`GETTER`生成了一个对于属性`x`的访问器。当然，这并不是一个明智的做法，而且还有很多漏洞。但是它展示给了我们宏动态生成 token 的能力。

有人可能注意第一个`x`需要`##`来进行连接，第二个却不需要。这是因为预处理器以 token 列表的方式处理展开过程。对于第一个`x`如果不使用`##`，那么对于预处理器来说`get_x`只是一个内容为`get_x`的 token，`x` 并不会被替换。若需要将 `x` 单独看做一个 token 则只能写成`get_ x`这样展开后中间会多一个空格，这显然不是我们想要的。

对于第二个`x`，对于预处理来说，`->`和`x`天然的就是两个 token，而且按照 C 的语法两者之间是否有空格并不会产生影响。合并以后反而会产生一个内容为`->foo`的 token。`->foo`并不是一个合法的 token，标准规定这种情况属于 ill-formed。不同编译器处理方法不同，gcc, clang 的预处理器会报错停止，vc会生成两个不同的 token。感兴趣的读者可以自己动手试验一下。

这一节的内容到此结束。到目前为止内容还比较简单，下一节的内容才是宏真正烧脑的地方。下节预告： object-like 宏的递归展开。

# 附录：什么是 token

什么是 token？token 在编译原理中只语法符号或者语法标记。可以看做是用来标记某个语法成分的抽象，一般由 token 名和一些属性组成。比如说数字 1 可以认为是一个整数常量，token 名为`integer-constant`，且其属性值为 1。对于宏来说共有这么几种：

- identifier 标识符，这个和 C 语言的标识符定义一致
- pp-number 预处理数字，其实和 C 语言中的数字也是类似的，区别在于多了一种情况，就是某种数字开头后跟非数字标识符的情况，比如 12aa，1.2bc 这种
- character-constant 字符常量，就是`'a'`, `'\n'` 等
- string-literal 字符串字面量 `"hello world"`
- punctuator 标点符号 `+ - -> >>` 等
- 除了上边所列情况以外的所有非空白字符

例如下边这个宏中的替换列表 token 化以后就是 `[identifier] [punctuator] [pp-number]`

```c
#define foo(x) x ## 12
```



# 宏定义黑魔法-从入门到奇技淫巧 (2)

这里是这个系列的第二篇。这次我们开始关注一些更复杂的宏特性————object-like 宏的递归展开。



# obj-like 的递归展开

在替换列表中出现的宏会被展开，这一过程将递归的进行下去，且是深度优先的。例如：

```
#define foo foz bar
#define bar 123
#define foz baz
#define baz 1

foo
-> foz bar
-> baz bar
-> 1 bar
-> 1 123
```

可以看到，当一个宏完全展开后，下一个宏才会被展开。但是，如果只有这一条规则那么很容易出现无限递归的情况。例如：

```
#define foo bar
#define bar foo

foo
-> bar
-> foo
-> 无限循环
```

因此在标准中对宏中涉及自指的部分做了限制：

> If the name of the macro being replaced is found during this scan of the replacement list (not including the rest of the source file’s preprocessing tokens), it is not replaced. Furthermore, if any nested replacements encounter the name of the macro being replaced, it is not replaced. These nonreplaced macro name preprocessing tokens are no longer available for further replacement even if they are later (re)examined in contexts in which that macro name preprocessing token would otherwise have been replaced.
>
> **16.3.4 cpp.recan**ISO n3690

从字面含义理解很简单，主要表达了两点：

1. 在展开的过程中，如果替换列表中出现了被展开宏，那么该被展开宏不会被展开。
2. 更进一步的，在展开的过程中，任何嵌套的展开过程中出现了被展开宏，该被展开宏也不会被展开。

听起来很绕不是么，这属于典型的，说起来绕但是实现起来简单。没关系，我们可以这样理解。每次展开的时候会创建一个「蓝色集合」（一般将标记过的 token 称作 painted-blue），这个蓝色集合由本次展开的父级展开的蓝色集合加上当前展开的宏组成。然后每次对替换列表进行扫描的时候，所有在当前蓝色集合中的宏都不会被展开。挺起来还是很绕的话，我们来看一个实际展开的例子：

```
#define foo foo a bar b bar baz c
#define bar foo 12
#define baz bar 13

foo
```

定义三个宏 `foo`, `bar`, `baz`，展开过程如下图所示：

![thb_obj_like_recur](.\picture\thb_obj_like_recur.png)

展开步骤为：

1. 对于宏 `foo` 的展开，一开始蓝色集合是空集，没有禁止展开的宏名。所以我们对 `foo` 进行展开。展开结果是 `foo a bar b bar baz c`，每次展开都会创建一个新的蓝色集合，该蓝色集合继承自父级的蓝色集合并添加本次展开的宏名。于是新的蓝色集合就是`空集`+`foo`。
2. 逐个 token 向后检查[1](http://feng.zone/2017/05/18/宏定义黑魔法-从入门到奇技淫巧-2/#fn:1)，此时蓝色集合为`{foo}`，所以第一个 `foo` 不展开。`a`不是一个宏，放着不管就行。`bar`不在蓝色集合里，展开为`foo 12`。展开的同时创建新的蓝色集合`{foo, bar}`。
3. 对 `bar` 展开的结果继续展开。此时的蓝色集合为`{foo, bar}`，`foo` 在集合内，不展开。`12`保持不变。到此 `bar`完全展开，回退至上一层。注意，展开的顺序是，当一个宏完全展开后，才会去展开下一个宏，这一点很重要。
4. `b` 不变。处理`bar`。注意，每一层展开的蓝色集合是不变的，和子展开无关。此时蓝色集合为`{foo}`。而不是`{foo bar}`。所以 `bar` 可以继续展开。展开过程和上一个 `bar` 一致，略去。
5. 处理`baz`。`baz` 不在蓝色集合里，展开为`bar 13` 创建蓝色集合`{foo baz}`。
6. 展开`bar`。注意，此处蓝色集合中并没有 `bar`，所以`bar`可以继续展开。因为蓝色集合只继承自己的父级，和其他的无关。展开过程与之前的 bar 展开过程一致，略去。但需注意和之前不同的是，展开后蓝色集合变为`{foo, baz, bar}`如果 `bar` 中有`baz`，则 `baz`不会继续展开。

最终，展开的结果是`foo a foo 12 b foo 12 foo 12 13 c`。
大家可以动手自己写几个例子试试看。虽然比较绕，但是掌握了以后还是很直白的。

本节内容到此结束。为了方便说明本节在介绍展开过程的时候略去了一些细节，这些细节将在下一节中交代。下一节我们来学习更加烧脑的 function-like 宏的递归展开。

------

1. 1.实际操作过程稍有不同，不过此处这么理解并不会产生问题。具体的差别在下一节中将会交代。



# 宏定义黑魔法-从入门到奇技淫巧 (3)

这是本系列的第三篇，也是整个系列中最核心的一篇。在这一节中将会介绍宏展开过程中最核心的机制，后续的很多技巧都是在这些特性上发展出来的。这一节的内容是 function-like 的宏展开。

# func-like 的宏展开

func-like 的宏展开基本思路和 obj-like 的宏展开是一致的。但是由于参数的存在，所以多了若干额外的规则。这使得我们无法使用上一节所讲的那种漂亮的树状规则来描述展开过程。主要过程是这么几个步骤，除了有关参数的外，obj-like 的宏也遵循相同的步骤：

1. identifier-list 也就是参数列表里的参数会被完全展开。但如果该参数在替换列表中被 `#` 或 `##` 所调用，那么该参数不展开。
2. 使用展开后的结果替换替换列表中的相关内容。
3. 执行 `#` 和 `##` 的结果，并替换相关内容。
4. 将得到的新的替换列表重新扫描找到可替换的宏名并展开。
5. 在整个过程中遵循上一节中提到的关于自指的规则。约束参数列表的起始蓝色集合与约束宏名的起始蓝色集合一致。

此外还有两个特性

1. 如果一个 func-like 的宏的宏名后边没有参数列表（括号和 identifier-list）那么这个宏名将不被视作一个宏。
2. 每次展开结束以后会向后看一个 token 是否能够与上次展开的结果形成一个 func-like 的宏。如果有就展开这个新形成的宏。

接下来，我们分析几个例子来解释上边的规则

```
#define FOO_ 0
#define FOO_1 1
#define PRIMITIVE_CAT(x, y) x y

PRIMITIVE_CAT(FOO_, 1)
-> 0 1
```

在这组宏中 `FOO_` 作为参数会被先行展开为 0，然后在替换替换列表中相应的部分。

```
#define FOO_ 0
#define FOO_1 1
#define CAT(x, y) x ## y

CAT(FOO_, 1)
-> FOO_1
-> 1
```

类似的一组宏定义。这回 `PRIMITIVE_CAT` 中的参数 `FOO_` 由于在替换列表中被 `##` 所调用，所以并不会被展开，而是直接合并成一个 token `FOO_1`。并且在重扫描的阶段被展开为 1。注意，也就是说这里在一个宏中实际上存在两次扫描展开。

那么有的时候我们就是希望先展开参数然后再进行拼接呢？这是我们需要借助一个额外的宏间接的来做这件事情。我们稍稍修改下上边的宏定义

```
#define FOO_ 0
#define FOO_1 1
#define PRIMITIVE_CAT(x, y) x ## y
#define CAT(x, y) PRIMITIVE_CAT(x, y)

CAT(FOO_, 1)
-> PRIMITIVE_CAT(0, 1)
-> 01
```

这回由于 `PRIMITIVE_CAT` 的存在参数 `FOO_` 在第一层中并没有被 `##` 直接调用。所以，`FOO_` 作为参数会被首先展开为 0。之后在 `PRIMITIVE_CAT` 中完成拼接。注意，这回的结果01之间并没有空格，因为他们被拼接成了一个 token。

接下来再看一个涉及自指的例子：

```
#define FOO(x, y) x + y
#define BAR(y) 13 + y
#define BAZ(z) FOO(BAZ(16), FOO(11, 0)) + z

BAZ(15)
-> FOO(BAZ(16), FOO(11, 0)) + 15
-> FOO(BAZ(16), 11 + 0) + 15
-> BAZ(16) + 11 + 0 + 15
```



在第一次展开 `FOO` 的时候，当前的蓝色集合为 `{BAZ}`。首先，先完全展开参数，此时展开第一个参数 `BAZ` 时，由于此时 `BAZ` 在蓝色集合中所以停止展开。第二个参数 `FOO` 则不在蓝色集合中，因此可以展开。注意，此时参数列表的蓝色集合与宏名的蓝色集合一致，`FOO`的参数中是可以继续展开`FOO`的。

但是，需要注意的一点是，虽然参数会先完全展开，然后替换替换列表中的对应部分。但参数展开后的结果在重扫描时仍然会沿用同一个蓝色集合。例如：

```
#define BAR() 1 BAZ()
#define BAZ() BAR
#define FOO(x) BAR() - x()

FOO(BAR())
-> FOO(1 BAR)
-> BAR() - 1 BAR()
-> 1 BAZ() - 1 BAR()
-> 1 BAR - 1 BAR()
```

注意，此处参数 `BAR` 展开为 `1 BAR` 以后就开始进行替换。替换完后，在重扫描时，发现后一个 `BAR()`，但是此时由于在参数完全展开时`BAR()`已经展开过，所以此时展开的蓝色集合中有 `BAR`。但是前一个`BAR()`的蓝色集合继承自`FOO`，所以并不受影响。因此，第一个`BAR()`可以展开，第二个不行。

然后再看一个更加复杂的涉及自指的例子：

```
#define FOO_(x) FOO_1(x)
#define FOO_1(x) FOO_2(x) + 1
#define FOO_2(x) FOO_1(x) - 1

#define BAR(x) FOO_ ## x (12) FOO_2

BAR(1) (5)
-> FOO_ ## 1 (12) FOO_2 (5)
-> FOO_1 (12) FOO_2 (5)
-> FOO_2(12) + 1 FOO_2 (5)
-> FOO_1(12) - 1 + 1 FOO_2 (5)
-> FOO_1(12) - 1 + 1 FOO_1(5) - 1
-> FOO_1(12) - 1 + 1 FOO_2(5) + 1 -1
```



1. 展开宏 BAR(1)。将参数替换到位，形成 `FOO_ ## 1 (12) FOO_2`
2. 重扫描替换结果展开 `FOO_1(12)` 得到 `FOO_2(12) + 1`
3. 继续展开 `FOO_2(12)` 得到 `FOO_1(12) - 1`，此时的 `FOO_1`在蓝色集合中，不继续展开。至此 `FOO_2(12)` 完全展开为 `FOO_1(12) - 1` 返回
4. `FOO_1(12)` 完全展开为 `FOO_1(12) - 1 + 1`
5. `BAR(1)` 完全展开为 `FOO_1(12) - 1 + 1 FOO_2`
6. 根据上边提到的特性 2。展开后的结果中最后一个 token `FOO_2` 与 `(5)` 形成了一个 func-like 的宏。所以展开`FOO_2 (5)` 过程与之前雷同，略去。

整个展开过程越来越复杂，不过核心只需记住几点，1. 参数先展开。2. 替换后重扫描。3. 蓝色集合中不展开。4. `#`, `##` 不展开。 5. 最后的括号要检查。

# 可变长参数 __VA_ARGS__

此外 func-like 宏还支持边长的参数。只需在参数列表的最后写上 `...` 就能够使用 `__VA_ARGS__` 来表示边长参数了。例如：

```
#define FOO(x, ...) __VA_ARGS__

FOO(1, (1, 2), (1,2,3))

-> (1, 2), (1,2,3)
```

本节的内容到此结束，枯燥的内容基本上讲完了。很多人可能感觉这些理论不是很必要，又绕有麻烦，大部分例子看起来也是生造出来的。这只是为了说明方便，下一节我们将利用目前学到的特性来实现些有用的东西，尽情期待下一节：宏的惯用法及实现图灵完备的宏。



# 宏定义黑魔法-从入门到奇技淫巧 (4)

这是本系列的第四篇，终于我们要开始写一些有实际意义的东西了。这一节我们将介绍一些比较难看懂的宏的惯用法(黑魔法)，本来准备一口气同时介绍如何实现图灵完备的宏的，结果发现篇幅太长。图灵完备宏放在下一篇中介绍了。那么就让我们开始学习真正的奇技淫巧吧！(๑•̀ㅂ•́)و✧

# Token 粘贴

首先我们来复习下上一节的一个例子，这也是我们今天要介绍的第一个惯用法，token 粘贴的直接展开。

```
#define FOO_ 0
#define FOO_1 1
#define PRIMITIVE_CAT(x, y) x ## y
#define CAT(x, y) PRIMITIVE_CAT(x, y)

CAT(FOO_, 1)
-> PRIMITIVE_CAT(0, 1)
-> 01
```

这里如过直接调用 `##` 由于宏本身语言的限制 `FOO_` 并不会直接展开。而间接的（多加一层调用）调用后就能够克服宏本身的语言限制。后续我们将会看到，间接调用是宏中非常常见的一个技巧。

# 括号表达式

括号表达式这个名字是我自己起的。准确的叫法并不是很清楚，但是在宏当中却很常用。括号表达式指的是，将参数用括号括起来使用。这样利用 func-like 的宏不接括号不会被展开的特性可以完成一些有意思的东西。比如：

```
#define EXPAND_IF_PAREN(x) EXPAND x
#define EAT(x)

EXPAND_IF_PAREN((12))
-> EAT (12)
->

EXPAND_IF_PAREN(12)
-> EAT 12
```

这个例子中如果参数带括号就会返回一个空。当然这个例子是没有什么意义的，但是在下边的例子中你会发现这一技巧将被反复的使用。

# 模式匹配

利用 Token 粘贴我们能够动态的创建不同的宏名。相当于我们可以描述一个宏名的结构，这和编程语言里的模式匹配正好不谋而合。我们可以利用这个特性我们可以实现类似 if 语句或者 switch 语句的功能。例如：

```
#define IIF(c) PRIMITIVE_CAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define IF_TRUE() printf("In true branch");
#define IF_FALSE() printf("In false branch");

IIF(cond) ( \
    IF_TRUE(), /*comma needed*/ \
    IF_FALSE() \
)
```

整个过程相当于 构造了不同的宏名，如果为 c 值为0就动态生成`IIF_0`，反之亦然。相当于变相决定了宏的展开方向。此时如果 cond 等于 1 则执行第一个参数，如果等于0 则执行第二个参数。注意这里用了 `PRIMITIVE_CAT` 这个宏，因为我们一般希望参数能够完全展开。

此外同样的结构还能玩一些不同的小花样，比如取补

```
#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

COMPL(1)
-> 0
COMPL(0)
-> 1
```



# 检测

在阅读很多库文件的源代码时（比如 boost），我们总会看到很多 `XXX_CHECK`，`XXX_PROBE`之类的宏。我第一次见到的时候非常的懵逼。从命名上根本看不出来作用是什么，而且还很难找出个准确的关键字去搜索。后来才明白这是一种宏中的惯用法，叫做「检测」(detection)。

检测给了我们这样一种能力，检测某个参数是否是特定的值。众所周知，在宏的基本语法中是不存在 if 这种东西的（宏不是预处理的#if）。但是根据不同的参数展现出不同的行为又是一个很常见的需求。因此，拥有判断某个参数是否是特定值的能力会给我们带来极大的便利。我们先来看看「检测」的写法：

```
#define GET_SEC(x, n, ...) n
#define CHECK(...) GET_SEC(__VA_ARGS__, 0)
#define PROBE(x) x, 1

CHECK(PROBE())
-> CHECK(x, 1,)
-> GET_SEC(x, 1, 0)
-> 1

CHECK(sth_not_empty)
-> GET_SEC(sth_not_empty, 0)
-> 0
```

可以看到这个技巧主要是利用了宏的可变长参数的特性。如果有 PROBE的调用 则第二个参数变为1，否则第二个参数保持不变为0。

具体应用的例子，比如可以检测参数是否为空：

```
#define IS_EMPTY(x) CHECK(CAT(PRIMITIVE_CAT(IS_EMPTY_, x), 0))
#define IS_EMPTY_0 PROBE()

IS_EMPTY()
-> CHECK(IS_EMPTY_0)
-> CHECK(PROBE())
-> 1

IS_EMPTY(param)
-> CHECK(IS_EMPTY_param_0)
-> 0
```

如果 x 为空则能够匹配到`IS_EMPTY_0`调用带有 `PROBE()` 的宏，否则就只是一串没有意义的字符串而已。利用一个小技巧就能够很方便的实现检测参数是否为空。注意此处我们使用了`CAT`和`PRIMITIVE_CAT`这是因为一般我们期望被判断参数应该被完全展开。

再比如，检测参数是否是括号表达式：

```
#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE()
IS_PAREN(())
-> CHECK(IS_PAREN_PROBE ())
-> CHECK(PROBE())
-> 1

IS_PAREN(xxx)
-> CHECK(IS_PAREN_PROBE xxx)
-> 0
```

我们还可以利用这个技巧实现取反（C 语言中除了0取反是1其他的取反都是0）。

```
#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE()

NOT(das)
-> 0
NOT(0)
-> 1
```

然后是转换为布尔值和 if 条件判断，限于篇幅就不推导了，请读者自行尝试：

```
#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))

IF(1)
-> 1
IF(0)
-> 0
IF(12)
-> 1
```

这一节到此结束。本节从这里借了很多例子[Cloak](https://github.com/pfultz2/Cloak)。下一节介绍如何实现图灵完备的宏。



# 宏定义黑魔法-从入门到奇技淫巧 (5)

这里是本系列的第五篇。如果你已经耐心看到了这里，那么恭喜你这一篇是我觉得最有趣的一部分。整个系列的前四篇都可以说是在给这篇的内容做铺垫。终于要开始正片了，将宏的语言能力拓展到接近图灵完备。当然我承认这个说法有点噱头的意思，因为最终实现的方法递归栈是有限的。但是这世界上递归栈有限的语言基本上递归栈都是有限的嘛，所以说是图灵完备也没有问题（逃）。

# 完整的 IF 语句

在上一篇中我们学习了一个可以作为 if 语句时用的宏 `IF`，但是使用逗号作为 if else 的分隔符多多少少有些不优雅，这一节我们在介绍一个书写起来更加漂亮的 if-else 语句实现：

```
#define IF_ELSE(condition) CAT(_IF_,  BOOL(condition))
#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

IF_ELSE (0) (      \
    True branch    \
)(                 \
    False branch   \
)
-> CAT(_IF_, 0) (True branch) (False branch)
-> _IF_0 (True branch) (False branch)
-> _IF_0_ELSE (False branch)
-> False branch

IF_ELSE (1) (      \
    True branch    \
)(                 \
    False branch   \
)
-> CAT(_IF_, 1) (True branch) (False branch)
-> _IF_1 (True branch) (False branch)
-> True branch _IF_1_ELSE_ (False branch)
-> True branch
```

里边用到的 `CAT` 和 `BOOL` 宏在上一篇中已经定义过了。忘记了的可以返回去查阅，这里就略去了。新的 `IF_ELSE` 宏可以使用括号作为两个分支的分隔符，写起来也更加接近 C 语言本身的写法。原理上来说，其实就是利用了宏会向后查找一个括号的特性。使得，不同的分支会“吞掉”另外一个分支的内容。对于「真分支」来说`_IF_1_ELSE_` 会吞掉「假分支」的展开过程。对于「假分支」来说直接跳过参数处理就可以了。

# 循环的实现

有了分支判断的能力，我们离图灵完备之间就只差循环了。原始的宏是不能够进行循环的，因为蓝色集合的存在，所以宏无法递归的展开。但是，我们有一些猥琐的方法可以绕开蓝色集合的限制，最终达到我们的目的。这里提供两种不同的循环实现方式，各有利弊，大家酌情选择。

## 非递归方案

首先介绍一个比较好理解，但是写起来不是那么自然地一个方案。经过这几篇教程的例子，大家对蓝色集合都很熟悉了。但是有一个比较复杂的极端情况还是要拿出来说说。这种情况是我们方案的基础。首先复习一下前几篇的知识点。

宏展开后，会后看一个 token 看是否能够组成`func-like`的宏以便继续展开，例如：

```
#define BAR() 1
#define FOO(x) BAR

FOO(1)()
-> BAR ()
-> 1
```

此处的 `BAR` 向后搜索发现了 ()，构成了一个 func-like 的宏，所以展开了。

前几节没有明确提醒大家注意的是，最后的这一次额外的展开，与蓝色集合也是有关的。

```
#define BAR_I() BAR
#define BAR() 1 BAR_I()

BAR() () // 蓝色集合 {}
-> 1 BAR_I() () // 蓝色集合 {BAR}
-> 1 BAR () // 蓝色集合 {BAR BAR_I}
```

此时由于蓝色集合中含有 `BAR` 所以即使满足 func-like 展开的条件 `BAR` 也不会被展开。

然而，预处理器只会保持当前的「蓝色集合」。在额外的展开后蓝色集合会被更新，所以我们可以这么做：

```
#define BAR_I() BAR
#define BAR() 1 BAR_I

BAR () () () // 蓝色集合 {}
-> BAR_I () () // 蓝色集合 {BAR}
-> BAR () // 蓝色集合 {BAR_I} 注意！在执行上一步的展开时，蓝色集合更新了
-> BAR_I // 蓝色集合 {BAR} 此处也更新了蓝色集合
```

画成图是这样的：

![seq_expand](.\picture\seq_expand.png)

也就是说通过引入 `BAR_I` 使得这几次展开得以在继承关系上互相平行的蓝色集合中展开。规避了禁止递归展开的问题。聪明的读者已经发现这个过程是可以无限重复下去的。这相当于给了我们近似于循环的能力，比如我想要生成一系列的函数名

```
#define FUNCTION(name) void name();
#define FUNCTION_TABLE(seq) CAT(FUNCTION_TABLE_1 seq, _END)
#define FUNCTION_TABLE_1(x) FUNCTION(x) FUNCTION_TABLE_2
#define FUNCTION_TABLE_2(x) FUNCTION(x) FUNCTION_TABLE_1
#define FUNCTION_TABLE_1_END
#define FUNCTION_TABLE_2_END

FUNCTION_TABLE((x) (y) (z) (e))
-> void x(); void y(); void z(); void e();
```

但是问题在于，使用这种方法并不能给出一个通用的类似 `FOR_EACH` 的函数，而且对于迭代的数据要就写成括号表达式的形式。这个不符合我们平时的习惯。因此，我们给出第二种实现循环的方式。

## 递归方案

第二种方法是基于递归调用来实现的，这种方法书写起来更加自然，但是展开效率并没有上边的高。这次要绕开蓝色集合的限制，先让我们学习一个新的技巧——**延迟展开**：

```
#define EMPTY()
#define DEFER(id) id EMPTY()

#define FOO() macro
FOO()
-> macro

DEFER(FOO)()
-> FOO()
```

神奇的事情出现了！`FOO`居然没有被展开！这就是我们走向递归调用的突破口。首先我们先来看看为什么此处 `FOO` 没有被展开:

```
DEFER(FOO)()
-> FOO EMPTY() ()
-> FOO()
```

此处，`EMPTY()` 展开后虽然会先后看一个 token，但是由于此处展开结果为空，所以并不会触发新的展开。而前边的 `FOO` 由于已经处理过了，所以并不会拿来和后边的`()` 配对。如果要展开则需要再多一次扫描的过程，比如这样：

```
#define EXPAND(...) __VA_ARGS__

EXPAND(DEFER(FOO)())
-> EXPAND(FOO EMPTY() ())
-> EXPAND(FOO ())
-> FOO ()
-> macro
```

在前边的内容中我们讲过，宏展开会有两次扫描。一次是参数展开，另一次是替换完毕后的重扫描，重扫描时会重新搜索可以展开的宏名。所以此处参数完全展开后成为`FOO()`，在重扫描的阶段被展开了!

那么延迟展开有什么用呢？延迟展开意味着你可以构造一个能够展开的式子，但是不将他加入蓝色集合，而是选则在下一次扫描中展开。我们知道宏的展开首先会对参数进行完全展开。然而，参数的完全展开是不会对宏自身的替换列表的蓝色集合产生影响的。那么我们就可以交替的使用这两次不同展开的蓝色集合树来规避蓝色集合的限制，例如：

```
#define BAR_I() BAR
#define BAR()  DEFER(BAR_I)()() 1

BAR()                 -> BAR_I()() 1
EXPAND(BAR())         -> BAR_I()() 1 1
EXPAND(EXPAND(BAR())) -> BAR_I()() 1 1 1
```

可以看到，神奇的事情出现了，`BAR_I` 这个宏只要存在额外的扫描，就能够不断展开。并且每次展开后都能保持同样的结构(`BAR_I()()`)。那么如果我们不加 `DEFER` 会怎么样呢？

```
#define BAR_I() BAR
#define BAR()  BAR_I()() 1

BAR()                 -> BAR_I() 1
EXPAND(BAR())         -> BAR_I() 1
EXPAND(EXPAND(BAR())) -> BAR_I() 1
```

`EXPAND` 并没有对 `BAR_I` 进行新的展开。即使多次扫描也不行，由于蓝色集合的存在，展开被阻止了。我们来看看为什么。接下来的部分比较难以理解，所以需要借助示意图来说明， 首先我们分析一下为什么没有`DEFER`就不能展开了：

![recur_fail](.\picture\recur_fail.png)

展开过程如上图所示。首先先完全展开参数部分`BAR()`。参数完全展开后，我们得到`BAR() 1`，注意此处参数的蓝色集合（图中用红色表示）为 `{BAR BAR_I}`。之后执行替换和重扫描，由于`BAR`在参数的蓝色集合中，所以重扫描并不会再次展开 `BAR`，整个展开到此结束。因为后续对于`BAR()`的展开都属于参数 `BAR()`的嵌套展开。

如果是有 `DEFER` 的情况，则展开过程如下图所示：

![recur_success](.\picture\recur_success.png)

参数完全展开后得到 `BAR_I ()() 1`，此时蓝色集合中并没有`BAR_I`因此可以继续展开得到`BAR()1`。此时，我们构造了一个和第一种方案类似的情况，也是两个宏交替展开，区别在于，上一个方案每次回消耗掉一个`()`，由于 DEFER 的存在每次都能够早出一个新的不被消耗的`()`，所以并不需要括号表达式来辅助。此时我们可以用同样的结构构造一个通用的`FOR_EACH`宏：

```
#define FOR_EACH(macro, x, ...) macro(x) DEFER(FOR_EACH_I)() (macro, __VA_ARGS__)
#define FOR_EACH_I() FOR_EACH

#define FOO(x) void x();

FOR_EACH(FOO, x, y, z)                  -> void x(); FOR_EACH_I () (FOO, y, z)
EXPAND(FOR_EACH(FOO, x, y, z))          -> void x(); void y(); FOR_EACH_I () (FOO, z)
EXPAND(EXPAND(FOR_EACH(FOO, x, y, z)))  -> void x(); void y(); void z(); FOR_EACH_I () (FOO, )
```

基本的雏形已经出现，但是当参数列表为空时，展开结果会有一个丑陋的小尾巴。还记不记的上一节提到过的模式匹配和检测？此处就派上了用场。

```
#define FOR_EACH(macro, x, ...) CAT(FOR_EACH_, IS_EMPTY(__VA_ARGS__)) (macro, x, __VA_ARGS__)
#define FOR_EACH_0(macro, x, ...) macro(x) DEFER(FOR_EACH_I)() (macro, __VA_ARGS__)
#define FOR_EACH_1(...) macro(x)
#define FOR_EACH_I() FOR_EACH

#define FOO(x) void x();

EXPAND(EXPAND(EXPAND(FOR_EACH(FOO, x, y, z))))  -> void x(); void y(); void z();
```

大致思路就是通过判断参数是否为空决定是否继续展开。注意这里不能使用我们上一节的 `IF_ELSE` 宏，因为其中有多次展开（多次扫面），所以 `DEFER` 宏会失效。如果想要使用的话，应该嵌套多层 `DEFER` 有兴趣的读者可以尝试一下。

现在还有最后一个问题，就是每多扫描一次，我们就需要多写一个 `EXPAND` 宏，这显然是不实用的。怎么解决呢？嘛，答案是真的没办法解决这个问题，因为扫描数是有限的，这也保证了无论如何宏展开一定会终止。但是我们可以使用一个折中的方案，用 n^3 的增长速率来定义多个扫描，例如：

```
#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

EVAL(FOR_EACH(FOO, x, y, z)) -> void x(); void y(); void z();
```

我们定义了 5 个宏，大概能有 243 次扫描。有人说这也太丑了吧，说好的图灵完备呢？嘛，其实这里相当于我们的「宏程序」拥有一个深度为 243 的递归栈。要知道默认情况下 Python 也就 900 多的递归栈，写十个`EVAL`也够用了。而且像 Boost 这种经典库的预处理实现也是一模一样的原理。现实生活中并不存在内存无限大的机器，所以笔者认为，这里把他叫做图灵完备，至少是弱图灵完备，是没有问题的。搭配上一节的内容，你就可以像写普通程序一样写宏了。不过限于篇幅就不在这里赘述了。

本节到此结束，下节预告，宏的那些坑。



# 宏定义黑魔法-从入门到奇技淫巧 (6)

这是本系列的最后一篇，介绍一些宏在日常使用中常见的一些坑。 由于宏本质上是对程序的文本进行操作，且宏和 C 语言本身完全是两套系统，所以很多时候总会引入一些奇怪到的错误，这一节我们就来介绍一些常见的需要注意的地方。



不知为什么，似乎在宏的教程中实现最小值宏是某种传统，所以这回我们也以实现一个标准的求最小值的宏为例，进行讲解。

# 操作符优先级

假设我们定义一个 `MIN` 宏如下：

```
#define MIN(X, Y) X < Y ? X : Y

MIN(2, 3);
-> 2 < 3 ? 2 : 3;
=> 2
```

该宏正常运行。但是如果我们调用的时候稍微复杂一点：

```
12 * MIN(2, 3);
-> 12 * 2 < 3 ? 2 : 3;
=> 3
```

看出问题所在了么？由于算法优先级的问题，所以此处 `12 * 2` 被先行计算了。导致了错误的结果。解决办法也很简单，就是加括号。

```
#define MIN(X, Y) (X < Y ? X : Y)
```

但是这样就没有问题了么？并不是，只要遇到相同优先级的运算符还是会出问题，比如我想要比较三个数：

```
MIN(2, MIN(3, 4))
-> MIN(2, 3 < 4 ? 3 : 4)
-> 2 < 3 < 4 ? 3 : 4 ? 2 : 3 < 4 ? 3 : 4
=> 1 ? 3 : 4 ? 2 : 3 < 4 ? 3 : 4
=> 3
```

还是会存在问题。所以比较好的实践是给每一个参数和整体都加上括号。于是我们的 `MIN` 宏变成了：

```
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
```

# 拷贝副作用

宏的本质是替换。这就引入一个问题，每一个参数都会在字面上被拷贝一份，并替换到相应的位置。这会导致有副作用的函数被调用多次，例如, 我有一个 `count` 函数，记录自己被调用的次数，并将次数返回：

```
int _count_ = 1;
int count() {
    _count_ += 1;
    return _count_;
}
```

那么不同的写法会导致不同的结果，例如：

```
int cur_count = count();

MIN(cur_count, 123);
printf("%d", count()); // 输出 2
MIN(count(), 123);
printf("%d", count()); // 输出 3
```

两次的结果居然不一样。这是为什么呢？因为第二次的时候宏展开会变成这个样子：

```
MIN(count(), 123);
-> count() < 123 ? count() : 123;
```

`count` 在这里被调用了 2 次。处理方法就是我们在这里加入一个临时变量：

```
#define MIN(X, Y) ({  \
    typeof(X) X_ = (X); \
    typeof(Y) Y_ = (Y); \
    ((X_ < Y_) ? (X_) : (Y_)); \
})
```

其中`({})`是一个 GNU 的扩展，它能够使其中的最后一个语句的值作为整个式子的返回值。如果这个扩展不被支持的话……我目前也没什么好办法了。

不过使用临时变量的话就有一个问题，有可能会出现命名冲突的情况。比如在 Clang 中的 MIN 是这么实现的：

```
#define __NSX_PASTE__(A,B) A##B
#define MIN(A,B) __NSMIN_IMPL__(A,B,__COUNTER__)
#define __NSMIN_IMPL__(A,B,L) ({ \
    __typeof__(A) __NSX_PASTE__(__a,L) = (A); \
    __typeof__(B) __NSX_PASTE__(__b,L) = (B); \
    (__NSX_PASTE__(__a,L) < __NSX_PASTE__(__b,L)) ? __NSX_PASTE__(__a,L) : __NSX_PASTE__(__b,L); })
```

第一个宏 `__NSX_PASTE__` 我们很熟悉了，这就是我们前几节提到的 `PRIMITIVE_CAT`，之所以分开写是因为保证参数完全展开。第二个宏里边有个 `__COUNTER__` 这个宏的意思是是个计数器，每次调用的时候 +1。这样的话，这个宏就很清楚了。其实就是在我们上一个版本的基础上，对每一个变量后边都添加一个数字，比如**a12321这种，这样的话就能最大限度的防止明明冲突。正常人也不会用**a1234 之类的当做变量名吧。至此这个 `MIN` 宏就能在大多数情况下正常使用了。那么问题来了，这是 `MIN` 的最佳实践么？当然不是，真正的最佳实践是这样的：

```
template <typename T>
inline T const& MIN (T const& a, T const& b)  {
   return a < b ? a:b;
}
```

# 吞分号

一般来说我们在调用宏的时候都会在最后加一个分号，就是这个分号会引入新的问题。例如我定义了一个宏用来跳过无用的内存空间：

```
#define SKIP_SPACES(p, limit)  \
{ char *lim = (limit);         \
  while (p < lim) {            \
    if (*p++ != ' ') {         \
      p--; break; }\
    }\
}\
```

为了防止命名冲突，在这里为语句加上了{}。那么如果有人这么写：

```
if(cond)
    SKIP_SPACE(p, limit);
else
    //something
```

那么展开后就变成了：

```
if(cond)
{
    char *lim = (limit);         
    while (p < lim) {            
        if (*p++ != ' ') {         
          p--;
          break;
        }
    }
};
else
    // something
```



注意最后的那个小分号。这使得后边的 else 空置了。(其实如果不加{}也会有类似的问题，读者可以想想看。)为了解决这个额外的分号的问题，我们使用一种惯用法`do...while(0)`：

```
#define SKIP_SPACES(p, limit)  \
do{ char *lim = (limit);         \
  while (p < lim) {            \
    if (*p++ != ' ') {         \
      p--; break; }\
    }\
}while(0)
```

注意此处的 while(0) 后边是没有分号的（某大厂高 t 员工就写错了 (๑•̀ㅂ•́)و✧ ）编译器一般会把这个多余的一次循环优化掉，所以性能也不会有什么损失。

到这里整个系列就完结了，感谢大家能够看到这里，作为答谢，送大家一个奇技淫巧，如何判断两个指针变量是否同类型：

```
#define CHECK_PTR_OF(type, p) (1 ? p : (type)0)
```

如果不是同类型这个三元操作符会在编译期间报错，你说这些人是怎么想到的呢 _(:з」∠)_