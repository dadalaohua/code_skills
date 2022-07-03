# 代码自动生成-宏递归思想

http://www.cppblog.com/kevinlynx/archive/2008/08/20/59451.html

Macro Recursion
author: Kevin Lynx

**Preface**

  本文可能是[代码自动生成-宏带来的奇技淫巧](http://www.cppblog.com/kevinlynx/archive/2008/03/19/44828.html)的续写。我尽力阐述如何让宏递归（或者说重复）地有规律地产生一些符号，而让我们少写很多重复代码，也许这些代码只有那么一点点的不同。将这项小技巧用于底层库的编写，会让代码看起来干净不少，同时文件尺寸也会骤然下降。

**Problem**
  如果你曾经写过[functor](http://www.cppblog.com/kevinlynx/archive/2008/03/17/44678.html)，那么你肯定对某些代码进行粘贴复制然后修改。更让人郁闷的是，这些代码基本是一样的。
例如，一个典型的functor可能为：

```c++
    template <typename Prototype>
    class functor;
    template <typename R, typename P1>
    class functor<R(P1)>;
    template <typename R, typename P1, typename P2>
    class functor<R(P1,P2)>;

```

  //好，接下去你可能厌烦了，可能会复制一个带有两个参数的functor，然后修改为处理3个参数的。
  这只是一个很简单的问题。宏不是c++里的东西，本文自然也不是讨论各种花哨的模板技术的。如果我之前那篇关于
宏的文章只是让你去分析问题以及更深层次地认识宏，那么现在我将分享我的这部分思想给你。
  关于上面的问题，我们期待得到这样的解决方案：

```c++
    template <typename R, DEF_PARAM( 2 )>
    class functor<R( DEF_ARG( 2 ) )>;

```

  那么，它将自动生成：

```c++
    template <typename R, typename P1, typename P2>
    class functor<R(P1,P2)>; 

```

  也就是说，`DEF_PARAM(n)`这个宏将根据n值自动生成一串符号，例如`DEF_PARAM(2)`就生成typename P1, typename P2。
同样，`DEF_ARG(n)`也会根据参数生成类似于P1,P2,...,Pn的符号串。

**思考**

  仔细思考下，我们可以看出`DEF_PARAM`和`DEF_ARG`这样的宏具有一种递归的特性（其实说成重复可能更合适）：每次展
开的内容基本一样，不断调用自身直到遇到终止条件。
  那么，我们的目标锁定于，用宏来实现递归。


**Pre-Implement**

  在开始之前，我需要告诉你一些基本的东西：
  在阅读一个宏时，你最好按照预处理的处理方式去逐个展开。当我说到展开时，我的意思是把宏替换为宏体。预处理器
展开宏的过程大致为：如果宏参数也是个宏，那么先将宏参数全部展开，再展开该宏；这个时候会扫描展开后的宏，如果
遇到其他宏，则继续展开。例如有一下宏：

```c++
#define PI 3.14
#define MUL_PI( n ) n * PI
#define TWO 2
```

  当我们写下`MUL_PI( TWO )`时，预处理发现`MUL_PI`的参数TWO 是个宏，那么先将TWO展开得到2，然后将2放进宏体展开
得到 2 * PI；预处理器对 2 * PI 进行扫描，发现还有宏PI，于是对PI做展开，得到 2 * 3.14。这个过程是递归的。
  但是也有例外，如果MUL_PI对宏参数进行了#或者##，那么该宏参数不会被展开。（参见以前那篇文章吧）
  任何时候，你可以通过以下宏去查看某个宏展开后的样子，可以方便你调试你的宏：

```c++
#define TO_STRING( x ) TO_STRING1( x )
#define TO_STRING1( x ) #x 
```

  （为什么要写个TO_STRING1，因为这是为了让x充分展开，避免上面提到的那个例外）  

  其他规则我会在文中需要的地方提出来。
实现

  就像大部分介绍递归函数时候给的例子，这里我也将阶乘作为例子。考虑如下典型的阶乘函数：

```c++
    int fac( int n )
    {
        if( n == 1 ) return 1;
        return n * fac( n - 1 );
    } 
```

  其核心部分在于 n * fac( n - 1 )，我们假设我们的宏也可以写成这样的的形式：

```c++
    #define FAC( n ) n * FAC( n - 1 )
```

  但是这样的宏是有问题的：
  当宏被展开时，如果遇到了自身，那么将被处理为一般符号，例如展开`FAC( 3 )`时，会遇到 `FAC( 2 )`，那么就把`FAC( 2 )`中的FAC当成了一搬符号。
  这样的限制注定了我们无法让宏真正地调用自身来实现递归。于是，我们不得不写下以下丑陋的符号，从而去模拟递归的每一次符号调用：

```c++
#define FAC_1( n ) 1
#define FAC_2( n ) n * FAC_##(n-1)( n - 1 )
#define FAC_3( n ) n * FAC_##(n-1)( n - 1 ) 
```

  这系列宏有点别扭（如果你足够细心），因为我们明显知道`FAC_2`返回的将是2，而`FAC_3`返回的当时6。我们这里只是模拟，同样，这使得我们可以把`FAC_1`作为递归的终止条件。
  我们的预想是，当调用`FAC_`时，它把n-1的值2合并到`FAC_`中，从而调用`FAC_2`，以此类推。
  但是这依然有问题，编译器会提示‘找不到符号`FAC_`’。导致这个问题的原因在于：宏展开只是单纯的字符替换，是我们想太多了，预处理器并不会去计算( n - 1 )的值是多少，也就是我们无法得到`FAC_2`这个宏。

  所以，`FAC_3( 3 )` 会被初次替换为 `3 * FAC_(3-1)( 3 - 1 )`。这个时候编译器就把`FAC_`当成了一个普通符号。我们可以自己定义个`FAC_`来证明这一点：

```c++
#define FAC_( n ) T 
```

  那么，FAC_3( 3 )就被替换为 3 * T(3-1)( 3 - 1 )。

  解决这个问题的办法关键在于，让预处理器自动计算出( n - 1 )。记住，我们解决问题的唯一办法是：字符替换。
所以，我们可以写下如下代码：

```c++
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2 

#define DEC( n ) DEC_##n 
```

  通过，DEC( n )这个宏，我们可以获取到一个( n -1 )的数。例如，DEC( 3 )被替换为 DEC_3，继续替换为 2。

  于是，我们新的FAC系列宏变为：

```c++
#define FAC_1( n ) 1
#define FAC_2( n ) n * FAC_##DEC( n )( n - 1 )
#define FAC_3( n ) n * FAC_##DEC( n )( n - 1 ) 
```

  不好意思，这样依然是不正确的！预处理器直接把`FAC_`和`DEC( n )`连接成符号了，而不是单个地先处理他们，最后再合并他们。

  OK，先解决这个问题：先处理`FAC_`和`DEC( n )`，再合并他们，而不是先合并他们。要解决这个问题，可以通过第三个宏来实现：

```c++
#define CHR( x, y ) x##y 
```

  作为连接两个符号为一个符号的宏，这个宏显然是不正确的，因为宏展开还有个规则：如果宏体对宏参数使用了#或##，那么宏参数不会被展开，也就是说：如果`CHR( FAC_, DEC( 3 )` 那么得到的只会是 `FAC_DEC( 3 )`。通常情况下我们是再写个宏：

```c++
#define CHR( x, y ) CHR1( x, y )
#define CHR1( x, y ) x##y 
```

  从而可以保证在正式连接x和y前，x和y都被完全展开。

  这个时候，我们的FAC系列宏变为：

```c++
#define FAC_1( n ) 1
#define FAC_2( n ) n * CHR( FAC_, DEC( n ) )( n - 1 )
#define FAC_3( n ) n * CHR( FAC_, DEC( n ) )( n - 1 ) 
```

  结果呢？结果还是有问题。= =
  我们假设`CHR( FAC_, DEC( n ) )`已经真的按我们预想展开为 `FAC_2`了，那么`FAC_3( 3 )`会被展开为什么呢？
被展开为 `3 * FAC_2( 3 - 1 )`。这是错误的，传给 `FAC_2` 的参数是 3 - 1就意味着错误。我们又臆想预处理器会
帮我们计算 3 - 1的结果了。我们必须保证传给 `FAC_2`的参数是个数字2。解决这个问题的办法就是通过`DEC(n)`宏。

  于是，`FAC`系列宏变为：

```c++
#define FAC_1( n ) 1
#define FAC_2( n ) n * CHR( FAC_, DEC( n ) )( DEC( n ) )
#define FAC_3( n ) n * CHR( FAC_, DEC( n ) )( DEC( n ) ) 
```

  这个时候，`FAC_3( 3 )`将会被替换为：3*2*1。这就是我们要的结果。

**In practice**

  以上只是向你展示一个过程，用宏去计算阶乘，就像用模板去计算阶乘（模板元编程）一样，只是一个用于展示的东西，没有什么实际价值。接下来我们开始有实际的工作，完成之前的预想：

```c++
template <typename R, typename P1, typename P2, typename P3>
class functor<R (P1, P2, P3)> 
```

  直接:

```c++
template <typename R, PARAM( 3 )>
class functor<R (ARG( 3 ))> 
```

  先考虑`PARAM`宏，该宏的任务就是生成类似于：`typename P1, typename P2, typename P3`这样的符号。我们假象它每一次递归都生成` typename Pn, `的字符串，那么当他递归完时，可能就生成`typename P1, typename P2, typename P3, `结果多了个逗号，也许最后一次结果不该有逗号。

  `ARG`宏和`PARAM`宏本质上相同，只是重复的符号不是`typename Pn`，而是`Pn`。

  最直接想到的是：

```c++
#define PARAM_1( n ) typename P##n
#define PARAM_2( n ) CHR( PARAM_, DEC( n ) )( DEC( n ) )##,typename P##n
#define PARAM_3( n ) CHR( PARAM_, DEC( n ) )( DEC( n ) )##,typename P##n 
```

  结果我们得到了个错误的展开结果：
`typename PDEC( 2 ),typename PDEC( 3 ),typename P3`

  这个问题出在：`PARAM_3( 3 )`当替换为 `PARAM_2( DEC( n ) )`时，因为`PARAM_2(n)`宏对于宏参数n使用了##，也就是那个`typename P##n`，所以这里不会把 `DEC( n )`展开，而是直接接到P后面。所以就成了`typename PDEC( 3 )`。

  为了消除这个问题，我们改进`PARAM`为：

```c++
#define TYPE( n ) ,typename P##n
#define PARAM_1( n ) CHR( typename P, n )
#define PARAM_2( n ) CHR( CHR( PARAM_, DEC( n ) )( DEC( n ) ), TYPE( n ) )
#define PARAM_3( n ) CHR( CHR( PARAM_, DEC( n ) )( DEC( n ) ), TYPE( n ) ) 
```

  之所以加入`TYPE(n)`，是因为 `,typename P##n` 这个宏本身存在逗号，将其直接用于宏体会出现问题。

  于是，我们得到了正确的结果。

  其实，`PARAM`系列宏宏体基本是一样的，除了终止条件那个宏，为什么我们要写这么多呢？理由在于宏体不能自己调用自己，所以才有了`PARAM_3`, `PARAM_2`。

  我们可以将上面的一系列宏抽象化，使其具有可复用性：

```c++
#define PARAM( n ) ,typename P##n
#define PARAM_END typename P 

#define ARG( n ) ,P##n
#define ARG_END P 

#define PARAM_1( n ) CHR( typename P, n )
#define PARAM_2( n ) CHR( CHR( PARAM_, DEC( n ) )( DEC( n ) ), TYPE( n ) )
#define PARAM_3( n ) CHR( CHR( PARAM_, DEC( n ) )( DEC( n ) ), TYPE( n ) ) 

#define REPEAT_1( n, f, e ) CHR( e, n )
#define REPEAT_2( n, f, e ) CHR( CHR( REPEAT_, DEC( n ) )( DEC( n ), f, e ), f( n ) )
#define REPEAT_3( n, f, e ) CHR( CHR( REPEAT_, DEC( n ) )( DEC( n ), f, e ), f( n ) ) 

#define DEF_PARAM( n ) REPEAT_##n( n, PARAM, PARAM_END )
#define DEF_ARG( n ) REPEAT_##n( n, ARG, ARG_END ) 
```

  我们创建了可重用的`REPEAT`系列宏，用于创建诸如`typename P1, typename P2, typename P3`或者`P1,P2,P3`之类的符号，通过更上层的`DEF_PARAM(n)`和`DEF_ARG(n)`，就可以直接创建出我们上面所需要的符号串，例如：

 ` DEF_PARAM( 3 )` 就得到 `typename P1, typename P2, typename P3`
  `DEF_ARG( 3 ) `就得到 `P1, P2, P3`

**More in practice**

  下载中提供了我使用这个宏递归技术写的lua_binder(如果你看过<[实现自己的LUA绑定器-一个模板编程挑战](http://www.cppblog.com/kevinlynx/archive/2008/08/13/58684.html) >)，你
可以与上一个版本做一下比较，代码少了很多。
  同样，我希望你也能获取这种宏递归的思想。  

**相关下载**

  [使用宏递归的lua_binder](http://www.cppblog.com/Files/kevinlynx/mr_luabinder.zip)





# 代码自动生成-宏带来的奇技淫巧

http://www.cppblog.com/kevinlynx/archive/2008/03/19/44828.html

Author : Kevin Lynx

众多C++书籍都忠告我们C语言宏是万恶之首，但事情总不如我们想象的那么坏，就如同goto一样。宏有一个很大的作用，就是自动为我们产生代码。如果说模板可以为我们产生各种型别的代码(型别替换)，那么宏其实可以为我们在符号上产生新的代码(即符号替换、增加)。

关于宏的一些语法问题，可以在google上找到。相信我，你对于宏的了解绝对没你想象的那么多。如果你还不知道#和##，也不知道prescan，那么你肯定对宏的了解不够。

我稍微讲解下宏的一些语法问题(说语法问题似乎不妥，macro只与preprocessor有关，跟语义分析又无关)：

\1. 宏可以像函数一样被定义，例如：
  `#define min(x,y) (x<y?x:y)` //事实上这个宏存在BUG
  但是在实际使用时，只有当写上min()，必须加括号，min才会被作为宏展开，否则不做任何处理。

\2. 如果宏需要参数，你可以不传，编译器会给你警告(宏参数不够)，但是这会导致错误。如C++书籍中所描述的，编译器(预处理器)对宏的语法检查不够，所以更多的检查性工作得你自己来做。

\3. 很多程序员不知道的#和##
  `#`符号把一个符号直接转换为字符串，例如：
  `#define STRING(x) #x`
  `const char *str = STRING( test_string );` str的内容就是"test_string"，也就是说`#`会把其后的符号直接加上双引号。
  `##`符号会连接两个符号，从而产生新的符号(词法层次)，例如：
  `#define SIGN( x ) INT_##x`
  `int SIGN( 1 );` 宏被展开后将成为：`int INT_1;`

\4. 变参宏，这个比较酷，它使得你可以定义类似的宏：
  `#define LOG( format, ... ) printf( format, __VA_ARGS__ )`
  `LOG( "%s %d", str, count );`
  `__VA_ARGS__`是系统预定义宏，被自动替换为参数列表。

\5. 当一个宏自己调用自己时，会发生什么？例如：
  `#define TEST( x ) ( x + TEST( x ) )`
  `TEST( 1 ); `会发生什么？为了防止无限制递归展开，语法规定，当一个宏遇到自己时，就停止展开，也就是
  说，当对`TEST( 1 )`进行展开时，展开过程中又发现了一个`TEST`，那么就将这个`TEST`当作一般的符号。`TEST(1)`最终被展开为：`1 + TEST( 1)` 。

\6. 宏参数的prescan，
  当一个宏参数被放进宏体时，这个宏参数会首先被全部展开(有例外，见下文)。当展开后的宏参数被放进宏体时，
  预处理器对新展开的宏体进行第二次扫描，并继续展开。例如：
  `#define PARAM( x ) x`
  `#define ADDPARAM( x ) INT_##x`
  `PARAM( ADDPARAM( 1 ) );`
  因为`ADDPARAM( 1 )`是作为PARAM的宏参数，所以先将`ADDPARAM( 1 )`展开为`INT_1`，然后再将`INT_1`放进`PARAM`。

  例外情况是，如果PARAM宏里对宏参数使用了`#`或`##`，那么宏参数不会被展开：
  `#define PARAM( x ) #x`
  `#define ADDPARAM( x ) INT_##x`
  `PARAM( ADDPARAM( 1 ) );` 将被展开为"ADDPARAM( 1 )"。

  使用这么一个规则，可以创建一个很有趣的技术：打印出一个宏被展开后的样子，这样可以方便你分析代码：
  `#define TO_STRING( x ) TO_STRING1( x )`
  `#define TO_STRING1( x ) #x`
  TO_STRING首先会将x全部展开(如果x也是一个宏的话)，然后再传给TO_STRING1转换为字符串，现在你可以这样：
  `const char *str = TO_STRING( PARAM( ADDPARAM( 1 ) ) );`去一探PARAM展开后的样子。

\7. 一个很重要的补充：就像我在第一点说的那样，如果一个像函数的宏在使用时没有出现括号，那么预处理器只是将这个宏作为一般的符号处理(那就是不处理)。

我们来见识一下宏是如何帮助我们自动产生代码的。如我所说，宏是在符号层次产生代码。我在分析Boost.Function模块时，因为它使用了大量的宏(宏嵌套，再嵌套)，导致我压根没看明白代码。后来发现了一个小型的模板库ttl，说的是开发一些小型组件去取代部分Boost(这是一个好理由，因为Boost确实太大)。同样，这个库也包含了一个function库。
这里的function也就是我之前提到的functor。ttl.function库里为了自动产生很多类似的代码，使用了一个宏：

```
\#define TTL_FUNC_BUILD_FUNCTOR_CALLER(n) \
 template< typename R, TTL_TPARAMS(n) > \
 struct functor_caller_base##n \
    ///...
```

该宏的最终目的是：通过类似于TTL_FUNC_BUILD_FUNCTOR_CALLER(1)的调用方式，自动产生很多functor_caller_base模板：

```
template <typename R, typename T1> struct functor_caller_base1
template <typename R, typename T1, typename T2> struct functor_caller_base2
template <typename R, typename T1, typename T2, typename T3> struct functor_caller_base3
///...
```

那么，核心部分在于`TTL_TPARAMS(n)`这个宏，可以看出这个宏最终产生的是：
```
typename T1
typename T1, typename T2
typename T1, typename T2, typename T3
///...
```
我们不妨分析`TTL_TPARAMS(n)`的整个过程。分析宏主要把握我以上提到的一些要点即可。以下过程我建议你翻着ttl的代码，
相关代码文件：function.hpp, macro_params.hpp, macro_repeat.hpp, macro_misc.hpp, macro_counter.hpp。

so, here we go

分析过程，逐层分析，逐层展开，例如`TTL_TPARAMS(1)`：

```
#define TTL_TPARAMS(n) TTL_TPARAMSX(n,T) 
=> TTL_TPARAMSX( 1, T )
#define TTL_TPARAMSX(n,t) TTL_REPEAT(n, TTL_TPARAM, TTL_TPARAM_END, t)
=> TTL_REPEAT( 1, TTL_TPARAM, TTL_TPARAM_END, T )
#define TTL_TPARAM(n,t) typename t##n,
#define TTL_TPARAM_END(n,t) typename t##n
#define TTL_REPEAT(n, m, l, p) TTL_APPEND(TTL_REPEAT_, TTL_DEC(n))(m,l,p) TTL_APPEND(TTL_LAST_REPEAT_,n)(l,p)
```

注意，TTL_TPARAM, TTL_TPARAM_END虽然也是两个宏，他们被作为TTL_REPEAT宏的参数，按照prescan规则，似乎应该先将
这两个宏展开再传给TTL_REPEAT。但是，如同我在前面重点提到的，这两个宏是function-like macro，使用时需要加括号，
如果没加括号，则不当作宏处理。因此，展开TTL_REPEAT时，应该为：
```
=> TTL_APPEND( TTL_REPEAT_, TTL_DEC(1))(TTL_TPARAM,TTL_TPARAM_END,T) TTL_APPEND( TTL_LAST_REPEAT_,1)(TTL_TPARAM_END,T)
```
这个宏体看起来很复杂，仔细分析下，可以分为两部分：
```
TTL_APPEND( TTL_REPEAT_, TTL_DEC(1))(TTL_TPARAM,TTL_TPARAM_END,T)以及
TTL_APPEND( TTL_LAST_REPEAT_,1)(TTL_TPARAM_END,T)
```
先分析第一部分：

```
#define TTL_APPEND( x, y ) TTL_APPEND1(x,y) //先展开x,y再将x,y连接起来
#define TTL_APPEND1( x, y ) x ## y
#define TTL_DEC(n) TTL_APPEND(TTL_CNTDEC_, n)
```

根据先展开参数的原则，会先展开`TTL_DEC(1)`
`=> TTL_APPEND(TTL_CNTDEC_,1) => TTL_CNTDEC_1`
`#define TTL_CNTDEC_1 0 `注意，`TTL_CNTDEC_`不是宏，`TTL_CNTDEC_1`是一个宏。
`=> 0` ， 也就是说，`TTL_DEC(1)`最终被展开为0。回到TTL_APPEND部分：
`=> TTL_REPEAT_0 (TTL_TPARAM,TTL_TPARAM_END,T)`
`#define TTL_REPEAT_0(m,l,p)`
`TTL_REPEAT_0`这个宏为空，那么，上面说的第一部分被忽略，现在只剩下第二部分：
```
TTL_APPEND( TTL_LAST_REPEAT_,1)(TTL_TPARAM_END,T)
=> TTL_LAST_REPEAT_1 (TTL_TPARAM_END,T) // TTL_APPEND将TTL_LAST_REPEAT_和1合并起来
#define TTL_LAST_REPEAT_1(m,p) m(1,p)
=> TTL_TPARAM_END( 1, T )
#define TTL_TPARAM_END(n,t) typename t##n
=> typename T1
```
展开完毕。

虽然我们分析出来了，但是这其实并不是我们想要的。我们应该从那些宏里去获取作者关于宏的编程思想。很好地使用宏
看上去似乎是一些偏门的奇技淫巧，但是他确实可以让我们编码更自动化。

参考资料：
macro语法: http://developer.apple.com/documentation/DeveloperTools/gcc-4.0.1/cpp/Macros.html
ttl(tiny template library) : http://tinytl.sourceforge.net/

 