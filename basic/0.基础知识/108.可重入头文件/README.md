# 【为宏正名】99%的人从第一天学习C语言就自废的武功

https://mp.weixin.qq.com/s/9nnhAYlSv9fviPGR17smKQ

**【说在前面的话】**

------

有人的地方就有江湖。我想应该没人愿意自废武功吧？

年轻人，你可曾记得，在修习C语言的时候，见过这样的字句：在创建头文件的时候，一定要加入保护宏。例如：

```
/* 这是头文件 my_header.h 的开头 */
#ifndef __MY_HEADER_H__
#define __MY_HEADER_H__

/* 头文件的实体内容 */

#endif /* end of __MY_HEANDER_H__
```

有好问者打破砂锅问到底，定有那先来者苦口婆心：**这是防止头文件被有意无意间重复包含的时候出现内容重复定义的问题**。

此话不虚、亦非假话。

但……**它从一开始就隐藏了C语言预处理的一项普普通通的技法**，并将其活生生逼成了所谓的武林绝学——并非因为它有怎样的禁忌，仅仅只是因为自废武功的人太多——几近灭绝啊。

**【未曾设想的道路】**

------

一般情况下，我们创建的头文件都可以被归入“**不可重入**”的大类，顾名思义，就是如果这个头文件被同一个 C 源文件直接或间接的包含（include）了多次，那么就会出现“内容重复定义”的问题——正因为不可重入，才需要加入保护宏来确保：

- **头文件中的内容仅在第一次被包含时生效**
- **随后再次包含该头文件时，内容将被跳过**



与“不可重入”的头文件相对，还有另外一个大类被称为“**可重入的头文件**”——顾名思义，这类头文件不仅允许出现重复包含，而且每一次包含都会发挥（一样或者不一样的）功能。

其实，在本系列之前的文章《[【为宏正名】什么？我忘了去上“数学必修课”！](http://mp.weixin.qq.com/s?__biz=MzAxMzc2ODMzNg==&mid=2656102292&idx=1&sn=7aa67ef981e68974e929a3f307f6592d&chksm=8039c46bb74e4d7d9ceafb2b96fb95e6142c04178ce39e1ffdf3f91871967f6754af17f9a8ea&scene=21#wechat_redirect)》就已经介绍过一个可重入头文件 ***mf_u8_dec2str.h*** 了，它的作用是在每次调用时“将用户给定的表达式计算出结果并转化为十进制字符串”（当然这里的数值必须小于256），例如：



```c
//! 一个用于表示序号的宏，初值是0
#define MY_INDEX      0
```

每次使用下面的预编译代码，我们就可以实现将 MY_INDEX的值加一的效果：


```c
//! MFUNC_IN_U8_DEC_VALUE = MY_INDEX + 1; 给脚本提供输入
#define MFUNC_IN_U8_DEC_VALUE    (MY_INDEX + 1)

//! 让预编译器执行脚本
#include "mf_u8_dec2str.h"

#undef MY_INDEX
//! MY_INDEX = MFUNC_OUT_DEC_STR; 获得脚本输出#define MY_INDEX    MFUNC_OUT_DEC_STR
```



作为一个可重入头文件，你调用他多少次都可以——每次都可以发挥应有的作用。对于这个头文件的用途和原理感到好奇的小伙伴，[不妨单击这里，重新阅读一下这篇文章](http://mp.weixin.qq.com/s?__biz=MzAxMzc2ODMzNg==&mid=2656102292&idx=1&sn=7aa67ef981e68974e929a3f307f6592d&chksm=8039c46bb74e4d7d9ceafb2b96fb95e6142c04178ce39e1ffdf3f91871967f6754af17f9a8ea&scene=21#wechat_redirect)。**需要注意的是，最新的源代码已经进行了更新，文章中提及的只是原理，具体实现以最新的源代码为准**：

https://github.com/GorgonMeducer/Generic_MCU_Software_Infrastructure/blob/master/sources/gmsi/utilities/preprocessor/mf_u8_dec2str.h



**【重复包含头文件的意义何在】**

------

我们什么时候回会用到“可重入的头文件”呢？或者换个问法：“可重入头文件究竟有何作用”？

从发挥作用的方式来说，“可重入头文件”可以被主要分为三大类：

1. 重复提供简单的预处理服务（比如前面提到过的 ***mf_u8_dec2str.h***）
2. 通过递归调用的方式来进行代码生成（比如在编译时刻给一个数组填充0~255的初始值）；
3. 为同样的宏模板提供不同的解释

第一个大类，我们已经在文章[【为宏正名】什么？我忘了去上“数学必修课”！](http://mp.weixin.qq.com/s?__biz=MzAxMzc2ODMzNg==&mid=2656102292&idx=1&sn=7aa67ef981e68974e929a3f307f6592d&chksm=8039c46bb74e4d7d9ceafb2b96fb95e6142c04178ce39e1ffdf3f91871967f6754af17f9a8ea&scene=21#wechat_redirect)》中详细介绍过，这里就不再赘述。而借助 ***mf_u8_dec2str.h*** 的帮助，我们也可以很轻松的实现第二类功能。

------

假设，我们要定义一系列数据，以固定间隔向其中填充指定数量的初始值，比如：


```c
// 2位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA4Table[4] = {
    0,  85, 170, 255
};

// 4位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA4Table[16] = {
    0,  17, 34,  51,
    68, 85, 102, 119,
    136, 153, 170, 187,
    204, 221, 238, 255
};

// 8位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA8Table[256] = {
    0,1,2,3...255,
};
```

另外，别问我为啥有这么傻的代码，LVGL源代码中就有，而且非常合理。



***https://github.com/lvgl/lvgl/blob/master/src/draw/sw/lv_draw_sw_letter.c***

![1](.\1.png)

所以，就不要质疑这里的合理性——我也只是举个例子，作为技术介绍，能简单的把事情讲清楚，用简单的例子无可厚非，领会精神即可。

理想中，如果有一个可重入的头文件 ***mf_u8_fill_dec.h***，它接受三个宏作为输入参数：

- **MFUNC_IN_START**——起始数字
- **MFUNC_IN_DELTA**——间隔
- **MFUNC_IN_COUNT**——填充的数量



那么上述代码完全可以改写成以下的形式：


```c
// 2位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA4Table[4] = {

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    4
#define MFUNC_IN_DELTA    (255 / (MFUNC_COUNT - 1))
#include “mf_u8_fill_dec.h”

};

// 4位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA4Table[16] = {

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    16
#define MFUNC_IN_DELTA    (255 / (MFUNC_COUNT - 1))
#include “mf_u8_fill_dec.h”

};

// 8位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA8Table[256] = {

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    256
#define MFUNC_IN_DELTA    (255 / (MFUNC_COUNT - 1))
#include “mf_u8_fill_dec.h”

};
```

是不是简单多了？——苦力活让预编译器去做，我们只管描述任务本身即可。



那么要如何实现 ***mf_u8_fill_dec.h*** 呢？这就离不开“可重入头文件”的固定结构了。



**【可重复头文件的固定结构】**

------

可重入头文件的基本结构一般固定为5个分区，如下图所示：

![2](.\2.png)

- **文档区**：主要用于放置头文件使用说明，当然，也包括可选的License和版本信息等；

- **输入参数检查区**：对作为输入参数的宏进行必要的检测，比如：

- - 如果用户忘记定义某些可选参数时提供默认值
  - 如果用户忘记定义某些必填的参数时，提供错误提示
  - 如果用户给的输入参数非法时，提供错误提示

- **#undef 区**：对功能区里会定义的宏首先进行无脑 undef

- **功能区**：实现具体功能的区域，一般会包含如下的内容：

- - 定义一些宏、带参数的宏等等
  - 进行条件编译
  - 包含其它头文件，或者进行递归包含

- **垃圾清理区**：主要用于清理头文件所产生的宏垃圾，其中包括：

- - 【可选】根据情况决定是否 #undef 作为输入参数的宏
  - 【可选】清除一些在功能区产生的、不希望暴露给用户的宏



可重入头文件的五个区域，抛开文档区，也就只剩下4个，看起来似乎并不复杂。下面我们就以 ***mf_u8_fill_dec.h*** 为例，手把手带大家建立一个麻雀虽小五脏俱全的可重入头文件：



**第一步：对输入参数进行检查（设计输入参数检查区）**

如前面例子中所介绍的那样，**mf_u8_fill_dec.h** 包含了三个参数：

- - **MFUNC_IN_START**——起始数字
  - **MFUNC_IN_DELTA**——间隔
  - **MFUNC_IN_COUNT**——填充的数量



由于并不复杂，我们可以简单的构建出如下的代码：


```c
#ifndef MFUNC_IN_START   
#   define MFUNC_IN_START    0    /* 默认从 0 开始 */
#endif
#ifndef MFUNC_IN_DELTA
#   define MFUNC_IN_DELTA    1    /* 默认以 1 为间隔 */
#endif
#ifndef MFUNC_IN_COUNT
/* 连数量都不提供，这就不能忍了！*/
#    error "Please at least define MFUNC_COUNT!!!"
#endif
```

这里，***MFUNC***是***Macro Function***（宏函数）的缩写，***IN***表示这是输入参数。



**第二步：编写功能（实现功能区）**

由于无法事先知道功能区会定义哪些宏，因此无法在“**#undef区**”进行清理，索性直接跳过，进入功能的实现——完成以后，再回头编写“**#undef区**”就是水到渠成了。



对**mf_u8_fill_dec.h**来说，它是一个典型的循环体结构，由于C语言的预编译器并没有提供类似 FOR之类的循环支持，我们的可以通过“用递归来模拟迭代”的方式来实现一个循环，基本思路如下：

- 通过***mf_u8_dec2str.h***来维护一个计数器
- 只要计数器值不为0，就递归调用头文件
- 如果计数器为0，则退出头文件



对应代码如下：

```c

/* 如果计数器为0就退出 */
#if MFUNC_IN_COUNT

/* 实现 MFUNC_IN_COUNT-- */
// MFUNC_IN_U8_DEC_VALUE = MFUNC_IN_COUNT - 1; 给脚本提供输入
#define MFUNC_IN_U8_DEC_VALUE    (MFUNC_IN_COUNT - 1)
#include "mf_u8_dec2str.h"
#undef MFUNC_IN_COUNT
//! MFUNC_IN_COUNT = MFUNC_OUT_DEC_STR; 获得脚本输出
#define MFUNC_IN_COUNT    MFUNC_OUT_DEC_STR

#include "mf_u8_fill_dec.h"

#endif
```



对一个循环来说，我们一定有一个循环体。这里的技巧是，将循环体放置在递归调用的后面，换句话说：**我们的做法是先一口气积攒足够的递归深度，然后在逐层返回的过程中执行循环体**。这样做的好处是不用担心循环的终止条件了——因此次数就是递归深度，这已经固定了。



在这个例子中，循环体要做的事情就是以固定间隔填充数值，因此，当我们从递归的最深处逐层返回时，我们要做的就是维护填充数值，实现类似：

```c
FUNC_IN_START += FUNC_IN_DELTA
```

这样的功能。具体代码为：

```c
/* 如果计数器为0就退出 */
#if MFUNC_IN_COUNT

/* 实现 MFUNC_IN_COUNT-- */
// MFUNC_IN_U8_DEC_VALUE = MFUNC_IN_COUNT - 1; 给脚本提供输入
#define MFUNC_IN_U8_DEC_VALUE    (MFUNC_IN_COUNT - 1)
#include "mf_u8_dec2str.h"
#undef MFUNC_IN_COUNT
//! MFUNC_IN_COUNT = MFUNC_OUT_DEC_STR; 获得脚本输出
#define MFUNC_IN_COUNT    MFUNC_OUT_DEC_STR

#include "mf_u8_fill_dec.h"


/* Loop body begin ------------------------------- */
MFUNC_IN_START,

/* 实现 FUNC_IN_START += FUNC_IN_DELTA */
#define MFUNC_IN_U8_DEC_VALUE    (MFUNC_IN_START + MFUNC_IN_DELTA)
#include "mf_u8_dec2str.h"
#undef MFUNC_IN_START
#define MFUNC_IN_START    MFUNC_OUT_DEC_STR
/* Loop Body End --------------------------------- */

#endif
```



**第三步：更新 #undef区**

通过观察，发现功能区并没有定义什么新的宏，因此略过此步骤。



**第四步：清理垃圾（更新垃圾清理区）**

在这个例子中，由于我们是通过递归返回的方法来实现功能，因此不能在尾部 #undef 关键的两个参数 **MFUNC_IN_START**和 **MFUNC_IN_DELTA，**但我们却可以清理输入参数 **MFUNC_IN_COUNT**：

```c
#undef MFUNC_IN_COUNT
```



**第五步：添加使用说明（更新文档区）**

注意到 三个输入参数中的两个 需要用户在使用前自行#undef，因此应该将这一条关键信息写入文档区——并最好提供一个范例代码。

至此，我们就获得了一个可以进行数据填充的可重入宏，其完整代码如下：

```c
/* 
How To Use
1. Please #undef macros MFUNC_IN_START and MFUNC_IN_DELTA before using
2. [optional]Define macro MFUNC_IN_START to specify the starting value
3. [optional]Define macro MFUNC_IN_DELTA to specify the increasing step
4. Define macro MFUNC_IN_COUNT to specify the number of items. 

NOTE: the MFUNC_IN_COUNT should not larger than 200

// 4位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA4Table[16] = {

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    16
#define MFUNC_IN_DELTA    17
#include "mf_u8_fill_dec.h"

};
*/

#ifndef MFUNC_IN_START   
#   define MFUNC_IN_START    0    /* 默认从 0 开始 */
#endif
#ifndef MFUNC_IN_DELTA
#   define MFUNC_IN_DELTA    1    /* 默认以 1 为间隔 */
#endif
#ifndef MFUNC_IN_COUNT
/* 连数量都不提供，这就不能忍了！*/
#    error "Please at least define MFUNC_COUNT!!!"
#endif

/* 如果计数器为0就退出 */
#if MFUNC_IN_COUNT

/* 实现 MFUNC_IN_COUNT-- */
// MFUNC_IN_U8_DEC_VALUE = MFUNC_IN_COUNT - 1; 给脚本提供输入
#define MFUNC_IN_U8_DEC_VALUE    (MFUNC_IN_COUNT - 1)
#include "mf_u8_dec2str.h"
#undef MFUNC_IN_COUNT
//! MFUNC_IN_COUNT = MFUNC_OUT_DEC_STR; 获得脚本输出
#define MFUNC_IN_COUNT    MFUNC_OUT_DEC_STR

#include "mf_u8_fill_dec.h"


/* Loop body begin ------------------------------- */
MFUNC_IN_START,

/* 实现 FUNC_IN_START += FUNC_IN_DELTA */
#define MFUNC_IN_U8_DEC_VALUE    (MFUNC_IN_START + MFUNC_IN_DELTA)
#include "mf_u8_dec2str.h"
#undef MFUNC_IN_START
#define MFUNC_IN_START    MFUNC_OUT_DEC_STR

/* Loop body End --------------------------------- */

#endif

#undef MFUNC_IN_COUNT
```



别忘记根据使用说明，对例子代码进行适当的修改：

```c
// 2位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA4Table[4] = {

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    4
#define MFUNC_IN_DELTA    85
#include "mf_u8_fill_dec.h"

};

// 4位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA4Table[16] = {

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    16
#define MFUNC_IN_DELTA    17
#include "mf_u8_fill_dec.h"

};


// 8位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA8Table[256] = {

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    128
#include "mf_u8_fill_dec.h"

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    128
#define MFUNC_IN_COUNT    128
#include "mf_u8_fill_dec.h"

};
```



大功告成！



**【说在后面的话】**

------

受到篇幅限制，本文只介绍了“可重入头文件”的两种常见形式，并着重介绍了以“递归”方式来批量进行代码生成的例子。

虽然填充数组看起来用处并不很大，但它充分展示了通过可重入头文件进行指定次数递归的方法。相信只要打开了思路，我对大家举一反三的能力从不怀疑。

需要强调一下：**可重入头文件只是一类非常基本的方法，并不是所谓的旁门左道，其构建方式有固定的方法，且有章可循，人人都能掌握**。



下一章，我将介绍一种“可重入头文件”在大型系统维护中最为耀眼的应用方式——**不仅可以大幅度降低代码的复杂度、提高可维护性，还能有效实现模块化和可读性**——这就是使用可重入头文件所实现的“**表格范式**”，尽情期待。