# EFSM(事件驱动型有限状态机：Event Finite State Machine)

https://gitee.com/simpost/EFSM/tree/master/

需要支持malloc，free，pthread，不适合MCU



#### 一、介绍

EFSM(event finite state machine，事件驱动型有限状态机)，是一个基于事件驱动的有限状态机，主要应用于嵌入式设备的软件系统中。

EFSM的设计原则是：简单！EFSM的使用者只需要关心：

1. **当事件到来时，通过EFSM取得对应事件的处理方法**；
2. **当特定事件到来，或者条件满足时，调用状态切换方法进行状态切换**。

由于EFSM的巧妙设计，避免了命名冲突的问题，你可以在一个程序中定义多个状态机；要是能对不同状态进行组织，还可以做出层次状态机的结构。

EFSM总共分为两个部分：

- EFSM核心：由uthash.h、efsm.h和efsm_conf.h三个文件组成；他们构成了事件驱动型状态机的核心；使用的时候只需要包含efsm.h即可；
- EFSM扩展：在EFSM核心的基础上，增加efsmt.h和efsmt.c两个文件，这两个文件会根据具体的状态机创建状态机线程，用于驱动状态机运转；使用的时候只需要包含efsmt.h即可；

#### 二、接口总览

EFSM总共提供了两套接口，你只需要选择其中套用法即可。全部接口概述如下：

##### 2.1 使用状态机工具集（EFSM核心）

若你想自己把控状态机的整个运转过程，可以直接使用EFSM核心，详细接口如下。

1. 状态操作接口

| API                    | 说明                     | 参数                 |
| ---------------------- | ---------------------- | ------------------ |
| EFSM_SETS              | 用于创建某一状态下不同时间的处理集合     | 类型，无参数             |
| EFSM_CREATE(state)     | 用于创建某一状态名              | state是状态名          |
| EFSM_DECLEAR(state)    | 当在其它地方需要使用到某个状态时，用于声明  | state是状态名          |
| EFSM_BIND(state, sets) | 用于将状态state与处理集sets进行绑定 | state是状态名，sets是处理集 |

2. 状态指针操作接口

| API                        | 说明                             | 参数                    |
| -------------------------- | ------------------------------ | --------------------- |
| EFSM_PTR_CREATE(name)      | 用于创建一个状态机指针                    | name是状态机指针名           |
| EFSM_PTR_DECLEAR(name)     | 当在其它地方需要使用到某个状态指针时，用于声明        | name是状态机指针名           |
| EFSM_PTR_BIND(name, state) | 用于为状态机指针name绑定到初始状态state，只调用一次 | name是状态机指针名，state是状态名 |

3. 状态切换接口

| API                         | 说明                           | 参数                    |
| --------------------------- | ---------------------------- | --------------------- |
| EFSM_TRANSFER(name, state)  | 用于把状态机name切换到state状态         | name是状态机指针名，state是状态名 |
| EFSM_TRANSFER_ENABLE(name)  | 使能状态切换功能，在EFSM_TRANSFER()前调用 | name是状态机指针名           |
| EFSM_TRANSFER_DISABLE(name) | 除能状态切换功能，在EFSM_TRANSFER()后调用 | name是状态机指针名           |

4. 获取处理函数接口

| API                       | 说明                              | 参数                   |
| ------------------------- | ------------------------------- | -------------------- |
| EFSM_HANDLER(name, event) | 用与当某个事件到来时，通过该方法获取到当前状态下的对应处理方法 | name是状态机指针名，event是事件 |

#### 2.2 使用状态机

若你不关心状态机的内部细节实现，需要一个可直接运转的状态机，那么请使用efsmt.h头文件，并将efsmt.c编译进你的源码。详细接口如下。

1. 状态操作接口

| API                    | 说明                     | 参数                 |
| ---------------------- | ---------------------- | ------------------ |
| EFSM_SETS              | 用于创建某一状态下不同时间的处理集合     | 类型，无参数             |
| EFSM_CREATE(state)     | 用于创建某一状态名              | state是状态名          |
| EFSM_DECLEAR(state)    | 当在其它地方需要使用到某个状态时，用于声明  | state是状态名          |
| EFSM_BIND(state, sets) | 用于将状态state与处理集sets进行绑定 | state是状态名，sets是处理集 |

2. 状态机操作接口

| API                     | 说明                   | 参数                  |
| ----------------------- | -------------------- | ------------------- |
| EFSMT_CREATE(name)      | 创建一个状态机              | name是状态机名           |
| EFSMT_DESTROY(name)     | 当不再使用状态机时，用于销毁       | name是状态机名           |
| EFSMT_DECLEAR(name)     | 当在其它地方需要使用到状态机时，用于声明 | name是状态机名           |
| EFSMT_BIND(name, state) | 用于绑定状态机的初始状态         | name是状态机名，state是状态名 |

3. 状态切换接口

| API                         | 说明                           | 参数                    |
| --------------------------- | ---------------------------- | --------------------- |
| EFSM_TRANSFER(name, state)  | 用于把状态机name切换到state状态         | name是状态机指针名，state是状态名 |
| EFSM_TRANSFER_ENABLE(name)  | 使能状态切换功能，在EFSM_TRANSFER()前调用 | name是状态机指针名           |
| EFSM_TRANSFER_DISABLE(name) | 除能状态切换功能，在EFSM_TRANSFER()后调用 | name是状态机指针名           |

4. 触发事件接口

| API                            | 说明                              | 参数                          |
| ------------------------------ | ------------------------------- | --------------------------- |
| EFSMT_INVOKE(name, event, arg) | 当事件到来时，触发该事件，状态机会自动寻找并调用对应的处理事件 | name是状态机名，event是事件，arg是事件参数 |

##### 2.3 总结

从接口可以看出，创建处理集与状态集，和状态切换方法是完全一样的；两种方法的唯一差异就是：当事件来了之后，事件对应的处理是由你来控制，还是由状态机内部进行控制。

#### 三、使用说明

要使用EFSM，非常简单，只需要如下三步：定义事件集、定义状态集、使用状态集。

##### 3.1 定义事件集

在我们设计业务/功能时，首先对需要使用到的事件进行定义。具体实现方法是在efsm_event.h文件中，使用EFSM_EVENT()宏定义需要的事件。如果你需要定义多个状态机，那请将不同状态机的事件分块保存，建议使用enum进行管理。比如：

```
enum {
     EVENT_PLAY  = EFSM_EVENT(1),
     EVENT_STOP  = EFSM_EVENT(2),
     EVENT_NEXT  = EFSM_EVENT(3),
     EVENT_PREV  = EFSM_EVENT(4),
     EVENT_START = EFSM_EVENT(7),    //not require continuous
 };
```

##### 3.2 定义状态集

1. **定义状态**：使用EFSM_CREATE(state)创建一个状态state；在其它使用到它的地方用EFSM_DECLEAR(state)宏进行声明；

2. **定义处理集**：使用EFSM_SETS state_sets定义一个状态集合state_sets，其中每个事件可以对应一个处理函数，也可以对应多个函数，当然也可以为NULL；处理函数需满足如下格式：
   
   ```
   typedef void (*EFSM_EVENT_HANDLER)(EFSM_EVENT_TYPE event, void *arg);
   ```

3. **绑定状态与处理集**：在模块初始化函数中调用EFSM_BIND(state, sets)宏将状态state与处理集sets进行绑定；

##### 3.3 使用状态集

当为模块/产品实现了所有的状态，那么编写业务应用程序来实现调度，让所有的状态机完美的运作起来。具体使用方法如下：

1. **定义状态指针**：使用EFSM_PTR_CREATE(name)定义一个状态指针name；当然你也可以定义多个状态指针，每个指针对应一个状态机。在其它使用到该状态指针的地方使用EFSM_PTR_DECLEAR(name)宏进行声明；

2. **绑定初始状态**：在整个状态机运作之前，需要使用EFSM_PTR_BIND(name, state)宏将状态指针name与状态state进行绑定；

3. **获取处理函数指针**：当接收到某个事件时，可以通过EFSM_HANDLER(name,event)宏从状态指针name中获取对该事件的处理方法，第一个参数是状态指针，第二个参数为事件；

4. **状态切换**：当遇到某个事件，或者在事件处理函数中条件满足，需要进行状态切换时，使用下面流程进行切换：
   
   ```
   EFSM_TRANSFER_ENABLE(name);
   EFSM_TRANSFER(name, state);
   EFSM_TRANSFER_DISABLE(name);
   ```
- EFSM_TRANSFER_ENABLE(name)宏使能状态指针name的切换能力；
- EFSM_TRANSFER_DISABLE(name)宏除能状态指针name的切换能力；
- EFSM_TRANSFER(name, state)宏执行状态指针name切换到state；

注意：做状态切换时，必须满足ENABLE()->TRANSFER()->DISABLE()的流程。这么做的目的，是为了让编程者思考：**状态设计与状态的跳转是否必要与合理**。

#### 四、常见问题

1. 使用过程中若遇到如下错误，是因为在正式使用前，没有把状态指针绑定到具体的状态：
   
   ```
   EFSM: cur-state-ptr have't bind a state: %xxx!!!
   ```

2. 使用过程中若遇到如下错误，是因为状态切换动作不满足ENABLE()->TRANSFER()->DISABLE()的流程：
   
   ```
   EFSM: 'xxx' switch to 'xxx' failed!!!
   ```

3. 使用过程中，若遇到了死锁或卡死，是因为状态切换动作不满足ENABLE()->TRANSFER()->DISABLE()的流程：

4. 命名定义了处理函数，为什么每次EFSM_HANDLER()得到的都是NULL？
   答： 因为你没有将状态与事件集进行绑定。

5. 对于某个状态没有使用到的事件，我是否可以不对其定义？
   答： 完全可以，这样还可以加快EFSM的处理速度。不过不建议直接删除，而采用注释的形式，比如：
   
   ```
   EFSM_SETS online[] = { {EVENT_PLAY, online_play},
                      /*{EVENT_STOP, NULL}, */
                      {EVENT_NEXT, online_next},
                      /*{EVENT_PREV, NULL}, */
                      {EVENT_START, online_start},
                    };
   ```
