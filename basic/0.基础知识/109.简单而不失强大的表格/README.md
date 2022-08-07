# 【非常C结构】简单而不失强大的表格

原创 GorgonMeducer 傻孩子 裸机思维 *2022-03-13 10:28*

https://mp.weixin.qq.com/s/amJEowL6ke3aBe1a7GoIrA

**【说在前面的话】**

------

2022年了，想必已经不会有人对嵌入式开发中“数据结构（Data Structure）”的作用产生疑问了吧？无论你是否心存疑惑，本文都将给你一个完全不同的视角。



每每说起数据结构，很多人脑海里复现的一定是以下的内容：

- 看似简单，但实际操作起来很容易出错的链表；
- 每天都挂在嘴边的队列；
- 程序跑飞的第一嫌疑人（没有之一）：栈——其实平时根本没有自己用过；
- 稀里糊涂揉在一起说的“堆栈”——其实脑海里想的只是malloc，其实跟栈（Stack）一毛钱关系都没有
- 几乎从未触碰过的树（Tree）和图（Graph）



数据结构其实不是一个高大上的名词，它意外的非常朴实——你也许每天都在用。作为一个新坑，我将在【非常C结构】系列文章中为大家分享很多嵌入式开发中很多**“非常”而又“好用”的数据结构**。



**【人人都可以学会的“表格”】**

------

你不必学过所谓的“关系数据库”也可以理解“表格（Table）”这种数据结构的本质含义。



在C语言环境中，表格的本质就是结构体数组，即：由结构体组成的数组。这里：

- **表格由一条条的“记录（Record）”构成，有时候也被称为“条目（Item）”**
- **结构体负责定义每条“记录”中内容的构成**
- **一个表格就是一个结构体数组**



在嵌入式系统中，表格具有以下特点：

- **是一个常量数组，以const来修饰，一般保存在ROM（比如Flash）中**
- **在编译时刻初始化**
- **在运行时刻使用**
- 以极其紧凑的形式保存数据
- 能够以“数组+下标”的形式加以访问





如果一个需求能够1）**接受上述的特点**；或者2）**本身就具有上述特点**；或者3）**部分内容经过改造后可以接受上述特点**——那么，就可以使用表格来保存数据了。



一个典型的例子就是：交互菜单。



![1](.\1.jpg)



很容易看到，每一级菜单本质上都“可以”是一个表格。



------

虽然在很多UI设计工具中（比如LVGL），菜单的内容是在运行时刻动态生成的（用链表来实现），但在嵌入式系统中，动态生成表格本身并不是一个“必须使用”的特性，相反，由于产品很多时候功能固定——菜单的内容也是固定的，因此完全没有必要在运行时刻进行动态生成——这就满足了表格的“在编译时刻初始化”的要求。

------



**采用表格的形式来保存菜单，就获得了在ROM中保存数据、减少RAM消耗的的优势。同时，数组的访问形式又进一步简化了用户代码。**



另外一个常见用到表格的例子是消息地图（**Message Map**），它在通信协议栈解析类的应用中非常常见，在很多结构紧凑功能复杂的bootloader中也充当着重要的角色。



**如果你较真起来，菜单也不过消息地图的一种**。表格不是实现消息地图的唯一方式，但却是最简单、最常用、数据存储密度最高的形式。在后续的例子中，我们就以“消息地图”为例，深入聊聊表格的使用和优化。



**【表格的定义】**

------

一般来说，表格由两部分构成：

- **记录（又叫条目）**
- **记录的容器**



因此，表格的定义也分为两个部分：

- **定义记录/条目的结构体类型**
- **定义容器的类型**



记录的定义一般格式如下：

```
typedef struct <表格名称>_item_t  <表格名称>_item_t;

struct <表格名称>_item_t {
    // 每条记录中的内容
};
```

这里，第一行的**typedef**所在行的作用是“前置声明”；**struct**所在行的作用是定义结构体的实际内容。虽然我们完全可以将“前置声明”和“结构体定义”合二为一，写作：

```
typedef struct <表格名称>_item_t {
    // 每条记录中的内容
} <表格名称>_item_t;
```

但基于以下原因，我们还是推荐大家坚持第一种写法：

- 由于“前置声明”的存在，我们可以在结构体定义中直接使用“<表格名称>_item_t” 来定义指针；
- 由于“前置声明”的存在，多个不同类型的记录之间可以“交叉”定义指针。



以消息地图为例，一个常见的记录结构体定义如下：

```c
typedef struct msg_item_t msg_item_t;

struct msg_item_t {
    uint8_t chID;                 //!< 指令
    uint8_t chAccess;             //!< 访问权限检测
    uint16_t hwValidDataSize;          //!< 数据长度要求
    bool (*fnHandler)(msg_item_t *ptMSG,   
                      void *pData, 
                      uint_fast16_t hwSize);
};
```

在这个例子中，我们脑补了一个通信指令系统，当我们通过通信前端进行数据帧解析后，获得了以下的内容：

- 8bit的指令
- 用户传来的不定长数据



为了方便指令解析，我们也需要有针对性的来设计每一条指令的内容，因此，我们加入了 ***chID*** 来存储指令码；并加入了函数指针***fnHandler***来为当前指令绑定一个处理函数；考虑到每条指令所需的最小有效数据长度是已知的，因此，我们通过***hwValidDataSize***来记录这一信息，以便进行信息检索时快速的做出判断。具体如何使用，我们后面再说。



对表格来说，**容器是所有记录的容身之所，可以简单，但不可以缺席**。最简单的容器就是数组，例如：

```c
const msg_item_t c_tMSGTable[20];
```

这里，***msg_item_t*** 类型的数组就是表格的容器，而且我们手动规定了数组中元素的个数。实践中，我们通常不会像这样手动的“限定”表格中元素的个数，而是直接“偷懒”——埋头初始化数组，然后让编译器替我们去数数——根据我们初始化元素的个数来确定数组的元素数量，例如：

```c
const msg_item_t c_tMSGTable[] = {
    [0] = {
        .chID = 0,
        .fnHandler = NULL,
    },
    [1] = {
        ...
    },
    ...
};
```

上述写法是C99语法，不熟悉的小伙伴可以再去翻翻语法书哦。说句题外话，**2022年了，连顽固不化的Linux都拥抱C11了，不要再抱着C89规范不放了，起码用个C99没问题的**。



上面写法的好处主要是方便我们偷懒，减少不必要的“数数”过程。那么，我们要如何知道一个表格中数组究竟有多少个元素呢？别慌，我们有 ***sizeof()***：


```c
#ifndef dimof
#   dimof(__array)     (sizeof(__array)/sizeof(__array[0]))
#endif
```

这个语法糖 ***dimof()*** 可不是我发明的，不信你问Linux。它的原理很简单，当我们把数组名称传给 ***dimof()*** 时，它会：

1. 通过 sizeof(<数组>) 来获取整个目标数组的字节尺寸；
2. 通过 sizeof(<数组>[0]) 来获取数组第一个元素的字节尺寸——也就是数组元素的尺寸；
3. 通过除法获取数组中元素的个数。



**【表格的访问（遍历）】**

------

由于表格的本质是结构体数组，因此，针对表格最常见的操作就是遍历（搜索）了。还以前面消息地图为例子：

```c
static volatile uint8_t s_chCurrentAccessPermission;

/*! \brief 搜索消息地图，并执行对应的处理程序
 *! \retval false  消息不存在或者消息处理函数觉得内容无效
 *! \retval true   消息得到了正确的处理
 */
bool search_msgmap(uint_fast8_t chID,
                   void *pData,
                   uint_fast16_t hwSize)
{
    for (int n = 0; n < dimof(c_tMSGTable); n++) {
        msg_item_t *ptItem = &c_tMSGTable[n];
        if (chID != ptItem->chID) {
            continue;
        }
        if (!(ptItem->chAccess & s_chCurrentAccessPermission)) {
            continue;  //!< 当前的访问属性没有一个符合要求
        }
        if (hwSize < ptItem->hwSize) {
            continue;  //!< 数据太小了
        }
        if (NULL == ptItem->fnHandler) {
            continue;  //!< 无效的指令？（不应该发生）
        }
        
        //! 调用消息处理函数
        return ptItem->fnHandler(ptItem, pData, hwSize);
    }
    
    return false;   //!< 没找到对应的消息
}
```

别看这个函数“很有料”的样子，其本质其实特别简单：

- 通过for循环依次访问表格的中的每一个条目；
- 通过 dimof 来确定 for 循环的次数
- 找到条目后做一系列所谓的“把关工作”，比如检查权限啊，检查数据有效性啊之类的——这些部分都是具体项目具体实现的，并非访问表格所必须的——放在这里只是一种参考。
- 如果条目符合要求，就通过函数指针执行对应的处理程序。



------

其实上述代码隐藏了一个特性：就是这个例子中的消息地图中允许出现chID相同的消息的——这里的技巧是：对同一个chID值的消息，我们可以针对不同的访问权限（chAccess值）来提供不同的处理函数。比如，通信系统中，我们可以设计多种权限和模式，比如：只读模式、只写模式、安全模式等等。不同模式对应不同的chAccess值。这样，对哪怕同样的指令，我们也可以根据当前模式的不同提供不同的处理函数——这只是一种思路，供大家参考。

------



**【由多实例引入的问题】**

------

前面的例子为我们展示表格使用的大体细节，对很多嵌入式应用场景来说，已经完全够用了。但爱思考的小伙伴一定已经发现了问题：



**如果我的系统中有多个消息地图（每个消息地图中消息数量是不同的），我改怎么复用代码呢？**



为了照顾还一脸懵逼的小伙伴，我把这个问题给大家翻译翻译：

- 系统中会有多个消息地图（多个表格），这意味着，系统中会有多个表格的数组；

- 前面的消息地图访问函数 ***search_msgmap()*** 跟某一个数组（也就是c_tMSGTable）绑定死了：

- - 只会遍历这一个固定的数组 c_tMSGTable；

  - for 循环的次数也只针对数组 c_tMSGTable；

    

简而言之，***search_msgmap()*** 现在跟某一个消息地图（数组）绑定死了，如果要让它支持其它的消息地图（其它数组），就必须想办法将其与特定的数组解耦，换句话说，在使用 ***search_msgmap()*** 的时候，**要提供目标的消息地图的指针，以及消息地图中元素的个数**。



一个头疼医头脚疼医脚的修改方案呼之欲出：

```c
bool search_msgmap(msg_item_t *ptMSGTable,
                   uint_fast16_t hwCount,
                   uint_fast8_t chID,
                   void *pData,
                   uint_fast16_t hwSize)
{
    for (int n = 0; n < hwCount; n++) {
        msg_item_t *ptItem = &ptMSGTable[n];
        if (chID != ptItem->chID) {
            continue;
        }
        ...
        
        //! 调用消息处理函数
        return ptItem->fnHandler(ptItem, pData, hwSize);
    }
    
    return false;   //!< 没找到对应的消息
}
```

假设我们有多个消息地图，对应不同的工作模式：

```c
const msg_item_t c_tMSGTableUserMode[] = {
    ...
};
const msg_item_t c_tMSGTableSetupMode[] = {
    ...
};

const msg_item_t c_tMSGTableDebugMode[] = {
    ...
};

const msg_item_t c_tMSGTableFactoryMode[] = {
    ...
};

```

在使用的时候，可以这样：

```c
typedef enum {
    USER_MODE = 0,    //!< 普通的用户模式
    SETUP_MODE,       //!< 出厂后的安装模式
    DEBUG_MODE,       //!< 工程师专用的调试模式
    FACTORY_MODE,     //!< 最高权限的工厂模式
} comm_mode_t;

bool frame_process_backend(comm_mode_t tWorkMode,
                           uint_fast8_t chID,
                           void *pData,
                           uint_fast16_t hwSize)
{
    bool bHandled = false;
    switch (tWorkMode) {
        case USER_MODE:
            bHandled = search_msgmap(
                          c_tMSGTableUserMode, 
                          dimof(c_tMSGTableUserMode),
                          chID,
                          pData,
                          hwSize);
            break;
         case SETUP_MODE:
            bHandled = search_msgmap(
                          c_tMSGTableSetupMode, 
                          dimof(c_tMSGTableUserMode),
                          chID,
                          pData,
                          hwSize);
            break;
         ...
    }

    return bHandled;
}
```



看起来很不错，对吧？非也非也！早得很呢。



**【表格定义的完全体】**

------

前面我们说过，表格的定义分两个部分：

- **定义记录/条目的结构体类型**
- **定义容器的类型**



其中，关于容器的定义，我们说过，数组是容器的最简单形式。**那么容器定义的完全体是怎样的呢？**



**“还是结构体”**！



是的，表格条目的本质是结构体，表格容器的本质也是一个结构体：


```c
typedef struct <表格名称>_item_t  <表格名称>_item_t;

struct <表格名称>_item_t {
    // 每条记录中的内容
};

typedef struct <表格名称>_t  <表格名称>_t;

struct <表格名称>_t {
    uint16_t hwItemSize;
    uint16_t hwCount;
    <表格名称>_item_t *ptItems;
};
```

容易发现，这里表格容器被定义成了一个叫做 <表格名称>_t 的结构体，其中包含了三个至关重要的元素：

- ***ptItems***：一个指针，指向条目数组；
- ***hwCount***：条目数组的元素个数
- ***hwItemSize***：每个条目的尺寸



------

这个**hwItemSize**其实是来凑数的，因为32位系统中指针4字节对齐的缘故，2字节的hwCount横竖会产生2字节的气泡。不理解这一点的小伙伴，可以参考文章《[漫谈C变量——对齐（3）](http://mp.weixin.qq.com/s?__biz=MzAxMzc2ODMzNg==&mid=2656101829&idx=4&sn=16349aa93de476e422b714992f9d3975&chksm=8039c63ab74e4f2c5aadd9070785c4e1529bd459201bf2727c3988dbc460e9ba5f9f1a84ab1c&scene=21#wechat_redirect)》

------



还是以前面消息地图为例，我们来看看新的容器应该如何定义和使用：

```c
typedef struct msg_item_t msg_item_t;

struct msg_item_t {
    uint8_t chID;                 //!< 指令
    uint8_t chAccess;             //!< 访问权限检测
    uint16_t hwValidDataSize;     //!< 数据长度要求
    bool (*fnHandler)(msg_item_t *ptMSG,   
                      void *pData, 
                      uint_fast16_t hwSize);
};

typedef struct msgmap_t msgmap_t;

struct msgmap_t {
    uint16_t hwItemSize;
    uint16_t hwCount;
    msg_item_t *ptItems;
};

const msg_item_t c_tMSGTableUserMode[] = {
    ...
};

const msgmap_t c_tMSGMapUserMode = {
    .hwItemSize = sizeof(msg_item_t),
    .hwCount = dimof(c_tMSGTableUserMode),
    .ptItems = c_tMSGTableUserMode,
};
```

既然有了定义，***search_msgmap()*** 也要做相应的更新：

```c
bool search_msgmap(msgmap_t *ptMSGMap,
                   uint_fast8_t chID,
                   void *pData,
                   uint_fast16_t hwSize)
{
    for (int n = 0; n < ptMSGMap->hwCount; n++) {
        msg_item_t *ptItem = &(ptMSGMap->ptItems[n]);
        if (chID != ptItem->chID) {
            continue;
        }
        ...
        
        //! 调用消息处理函数
        return ptItem->fnHandler(ptItem, pData, hwSize);
    }
    
    return false;   //!< 没找到对应的消息
}
```



看到这里，相信很多小伙伴内心是毫无波澜的……



“是的……是稍微优雅一点……然后呢？”

“就这！？就这？！”



别急，下面才是见证奇迹的时刻。



**【要优雅……】**

------

在前面的例子中，我们注意到表格的初始化是分两部分进行的：

```c
const msg_item_t c_tMSGTableUserMode[] = {
    [0] = {
        .chID = 0,
        .fnHandler = NULL,
    },
    [1] = {
        ...
    },
    ...
};

const msgmap_t c_tMSGMapUserMode = {
    .hwItemSize = sizeof(msg_item_t),
    .hwCount = dimof(c_tMSGTableUserMode),
    .ptItems = c_tMSGTableUserMode,
};
```

那么，我们可不可以把它们合二为一呢？这样：

- **所有的初始化写在一起；**
- **避免给完全用不到的条目数组起名字：**



要做到这一点，我们可以使用一个类似“匿名数组”的功能：



我们想象中的样子： 

```c
const msgmap_t c_tMSGMapUserMode = {
    .hwItemSize = sizeof(msg_item_t),
    .hwCount = dimof(c_tMSGTableUserMode),
    .ptItems = const msg_item_t c_tMSGTableUserMode[] = {
          [0] = {
              .chID = 0,
              .fnHandler = NULL,
          },
          [1] = {
              ...
          },
          ...
      },
};
```

使用“匿名数组”后的样子（也就是删除数组名称后的样子）：

```c
const msgmap_t c_tMSGMapUserMode = {
    .hwItemSize = sizeof(msg_item_t),
    .hwCount = dimof(c_tMSGTableUserMode),
    .ptItems = (msg_item_t []){
          [0] = {
              .chID = 0,
              .fnHandler = NULL,
          },
          [1] = {
              ...
          },
          ...
      },
};
```



其实，这不是什么“黑魔法”，而是一个广为使用的GNU扩展，被称为“**复合式描述（Compound literal）**”，本质上就是一种以“省略”数组或结构体名称的方式来初始化数组或结构体的语法结构。具体语法介绍，小伙伴们可以参考这篇文章《[C语言语法中匿名的最高境界](http://mp.weixin.qq.com/s?__biz=MzAxMzc2ODMzNg==&mid=2656103818&idx=1&sn=45a0321f3be8171be7fe750659558d35&chksm=8039ce75b74e4763920adca453ec0005ae847468a7c8a4dc1073f9f5a72904219c894b019c2a&scene=21#wechat_redirect)》。



眼尖的小伙伴也许已经发现了问题：**既然我们省略了变量名，那么如何通过 dimof() 来获取数组元素的个数呢？**



少侠好眼力！



解决方法不仅有，而且简单粗暴：

```c
const msgmap_t c_tMSGMapUserMode = {
    .hwItemSize = sizeof(msg_item_t),
    
    .hwCount = dimof((msg_item_t []){
          [0] = {
              .chID = 0,
              .fnHandler = NULL,
          },
          [1] = {
              ...
          },
          ...
      }),
      
    .ptItems = (msg_item_t []){
          [0] = {
              .chID = 0,
              .fnHandler = NULL,
          },
          [1] = {
              ...
          },
          ...
      },
};
```



所以说？……

为了优雅的初始化……

我们要把同样的内容写两次？！！



手写的确挺愚蠢，但宏可以啊！

```c
#define __impl_table(__item_type, ...)                   \
    .ptItems = (__item_type []) {                        \
        __VA_ARGS__                                      \
    },                                                   \
    .hwCount = sizeof((__item_type []) { __VA_ARGS__ })  \
             / sizeof(__item_type),                      \
    .hwItemSize = sizeof(__item_type)

#define impl_table(__item_type, ...)                     \
    __impl_table(__item_type, __VA_ARGS__)
```

借助上面的语法糖，我们可以轻松的将整个表格的初始化变得简单优雅：

```c
const msgmap_t c_tMSGMapUserMode = {
    impl_table(msg_item_t, 
          [0] = {
              .chID = 0,
              .fnHandler = NULL,
          },
          [1] = {
              ...
          },
          ...
    ),
};
```

这下舒服了吧？



**【禁止套娃……】**

------

还记得前面多实例的例子吧？

```c
const msg_item_t c_tMSGTableUserMode[] = {
    ...
};
const msg_item_t c_tMSGTableSetupMode[] = {
    ...
};

const msg_item_t c_tMSGTableDebugMode[] = {
    ...
};

const msg_item_t c_tMSGTableFactoryMode[] = {
    ...
};
```

现在当然就要改为如下的形式了： 

```c
const msgmap_t c_tMSGMapUserMode = {
    impl_table(msg_item_t, 
        ...
    ),
};

const msgmap_t c_tMSGMapSetupMode = {
    impl_table(msg_item_t, 
        ...
    ),
};

const msgmap_t c_tMSGMapDebugMode = {
    impl_table(msg_item_t, 
        ...
    ),
};

const msgmap_t c_tMSGMapFactoryMode = {
    impl_table(msg_item_t, 
        ...
    ),
};
```

但……它们不都是 ***msgmap_t*** 类型的么？为啥不做一个数组呢？


```c
typedef enum {
    USER_MODE = 0,    //!< 普通的用户模式
    SETUP_MODE,       //!< 出厂后的安装模式
    DEBUG_MODE,       //!< 工程师专用的调试模式
    FACTORY_MODE,     //!< 最高权限的工厂模式
} comm_mode_t;

const msgmap_t c_tMSGMap[] = {
    [USER_MODE] = {
        impl_table(msg_item_t, 
            ...
        ),
    },
    [SETUP_MODE] = {
        impl_table(msg_item_t, 
            ...
        ),
    },
    [DEBUG_MODE] = {
        impl_table(msg_item_t, 
            ...
        ),
    },
    [FACTORY_MODE] = {
        impl_table(msg_item_t, 
            ...
        ),
    },
};
```

是不是有点意思了？再进一步，我们完全可以做一个新的表格，表格的元素就是 msgmap_t 呀？


```c
typedef struct cmd_modes_t cmd_modes_t;

struct cmd_modes_t {
    uint16_t hwItemSize;
    uint16_t hwCount;
    msgmap_t *ptItems;
};
```

然后就可以开始套娃咯：


```c
const cmd_modes_t c_tCMDModes = {
    impl_table(msgmap_t,
        [USER_MODE] = {
            impl_table(msg_item_t, 
                [0] = {
                    .chID = 0,
                    .fnHandler = NULL,
                },
                [1] = {
                    ...
                },
                ...
            ),
        },
        [SETUP_MODE] = {
            impl_table(msg_item_t, 
                ...
            ),
        },
        [DEBUG_MODE] = {
            impl_table(msg_item_t, 
                ...
            ),
        },
        [FACTORY_MODE] = {
            impl_table(msg_item_t, 
                ...
            ),
        },
    ),
};
```



【差异化……】

------

在前面的例子中，我们可以根据新的定义方式更新函数 ***frame_process_backend()*** 函数：


```c

extern const cmd_modes_t c_tCMDModes;

bool frame_process_backend(comm_mode_t tWorkMode,
                           uint_fast8_t chID,
                           void *pData,
                           uint_fast16_t hwSize)
{
    bool bHandled = false;
    
    if (tWorkMode > FACTORY_MODE) {
        return false;
    }
    
    return search_msgmap( &(c_tCMDModes.ptItems[tWorkMode]), 
                          chID,
                          pData,
                          hwSize);
}
```



是不是特别优雅？



把容器定义成结构体还有一个好处，就是可以给表格更多的差异化，这意味着，除了条目数组相关的内容外，我们还可以放入其它东西，比如：

- **在结构体内增加更多的成员——为表格添加更多的信息**
- **加入更多的函数指针（用OOPC的概念来说就是加入更多的“方法”）**



现有的 ***frame_process_backend()*** 为每一个消息地图（***msgmap_t***）都使用相同的处理函数 ***search_msgmap()*** ，这显然缺乏差异化的可能性。如果每个消息地图都有可能有自己的特殊处理函数怎么办呢？



为了实现这一功能，我们可以对 msgmap_t 进行扩展：


```c
typedef struct msgmap_t msgmap_t;

struct msgmap_t {
    uint16_t hwItemSize;
    uint16_t hwCount;
    msg_item_t *ptItems;
    bool (*fnHandler)(msgmap_t *ptMSGMap,
                      uint_fast8_t chID,
                      void *pData,
                      uint_fast16_t hwSize);
};
```

则初始化的时候，我们就可以给每个消息地图指定一个不同的处理函数：


```c
extern     
bool msgmap_user_mode_handler(msgmap_t *ptMSGMap,
                      uint_fast8_t chID,
                      void *pData,
                      uint_fast16_t hwSize);

extern     
bool msgmap_debug_mode_handler(msgmap_t *ptMSGMap,
                      uint_fast8_t chID,
                      void *pData,
                      uint_fast16_t hwSize);

const cmd_modes_t c_tCMDModes = {
    impl_table(msgmap_t,
        [USER_MODE] = {
            impl_table(msg_item_t, 
                ...
            ),
            .fnHandler = &msgmap_user_mode_handler,
        },
        [SETUP_MODE] = {
            impl_table(msg_item_t, 
                ...
            ),
            .fnHandler = NULL; //!< 使用默认的处理函数
        },
        [DEBUG_MODE] = {
            impl_table(msg_item_t, 
                ...
            ),
            .fnHandler = &msgmap_debug_mode_handler,
        },
        [FACTORY_MODE] = {
            impl_table(msg_item_t, 
                ...
            ),
            //.fnHandler = NULL  什么都不写，就是NULL（0）
        },
    ),
};
```

此时，我们再更新***frame_process_backend()*** 函数，让上述差异化功能成为可能：


```c

bool frame_process_backend(comm_mode_t tWorkMode,
                           uint_fast8_t chID,
                           void *pData,
                           uint_fast16_t hwSize)
{
    bool bHandled = false;
    msgmap_t *ptMSGMap = c_tCMDModes.ptItems[tWorkMode];
    if (tWorkMode > FACTORY_MODE) {
        return false;
    }
    
    //! 调用每个消息地图自己的处理程序
    if (NULL != ptMSGMap->fnHandler) {
         return ptMSGMap->fnHandler(ptMSGMap, 
                                    chID,
                                    pData,
                                    hwSize);
    }
    //! 默认的消息地图处理程序
    return search_msgmap( ptMSGMap, 
                          chID,
                          pData,
                          hwSize);
}
```



**【说在后面的话】**

------

啥都不说了……你们看着办吧。我们下期再见。