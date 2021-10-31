# HSM - Hierarchical State Machine

https://github.com/howard-chan/HSM

================================
HSM - Hierarchical State Machine
================================
1. Overview 概述
2. Using HSM Framework 使用 HSM 框架  
    2.1. Define the events and states 定义事件和状态  
    2.2: Implement each of the state's event handler 实现每个状态的事件处理程序  
    2.3: Create the HSM states and HSM instances 创建 HSM 状态和 HSM 实例  
    2.4: Embed the HSM_Run() into your application 将 HSM_Run() 嵌入到你的应用程序中  
3. Using HSM Advance Features 使用 HSM 高级功能  
    3.1. Basic Debug Features 基本调试功能  
    3.2. Advance Debug Features 高级调试功能  
    3.3. Optimization Features 优化功能  
4. HSM Cookbook and Design Patterns HSM 手册和设计模式  
    4.1. Make a transition decision on state entry, try using HSME_INIT 对状态进入做出转换决定，尝试使用HSME_INIT  
    4.2. Run Concurrent model (i.e. concurrent states), try using the parent state as a proxy 运行并发模型（即并发状态），尝试使用父状态作为代理   
    4.3. Guard Condition, try using HSM_IsInState() 保护条件，尝试使用HSM_IsInState   
    4.4. Using child state as filter  使用子状态作为过滤器


1. Overview:
  ============
  Generally a state machine is a "black box" whose output is driven by an input "event" and its internal state.  Another way to look at a state machine is that of an event filter which will only act on "events" relevant to its internal state.  To Illustrate this concept, we would like to design an LED controlled by a "MODE" button that toggles between "Off" -> "On" -> "Blinking" and back to "Off".  The following flat state machine diagram is an example implementation of this LED.

  概述：

  通常状态机是一个“黑盒”，其输出由输入“事件”及其内部状态驱动。
  查看状态机的另一种方式是事件过滤器，它仅作用于与其内部状态相关的“事件”。
  为了说明这个概念，我们想设计一个由“模式”按钮控制的 LED，该按钮在“关闭”->“开启”->“闪烁”和返回“关闭”之间切换。
  以下平面状态机图是此 LED 的示例实现。
```
            +-------------------------+
    +------>|          Off            |<----O
    |       +-------------------------+
    |                   |
    |              MODE / LedOn()
    |                   V
    |       +-------------------------+
    |       |          On             |
    |       +-------------------------+
    |                   |
MODE / LedOff()    MODE / LedOff()
    |                   V
    |       +-------------------------+
    +-------|      BlinkingOff        |
    |        +------------------------+
    |            ^                 |
    |    TIMER / LedOff()    TIMER / LedOn()
    |            |                 V
    |       +-------------------------+
    +-------|      BlinkingOn         |
            +-------------------------+
```
In this state machine, there are 2 events that are generated ("TIMER" and "MODE").  TIMER is a periodic event, while MODE is asynchronous event from the user.  In all states, the "MODE" event is handled and causes a transition that sets the LED output.  However the "TIMER" event is only handled in the "BlinkingOff" and "BlinkingOn" states, while ignored (i.e. filtered) in the "Off" and "On" state.

在此状态机中，生成了 2 个事件（“TIMER”和“MODE”）。 TIMER 是一个周期性事件，而 MODE 是来自用户的异步事件。在所有状态下，都会处理“MODE”事件并导致设置 LED 输出的转换。然而，“TIMER”事件仅在“BlinkingOff”和“BlinkingOn”状态下处理，而在“Off”和“On”状态下被忽略（即过滤）。

Most state machines are flat (i.e. non-hierarchical) which is simple and easy to understand and implement.  When modeling / documenting the state machine on paper, it becomes increasing complex as the number of states and transitions increases.  At the same time, a large number of refactoring opportunities become apparent which is hard to realize in a flat state machine.  For example:

大多数状态机是扁平的（即非分层的），它简单易懂且易于实现。 在纸上建模/记录状态机时，随着状态和转换数量的增加，它变得越来越复杂。 同时，大量的重构机会变得明显，这在平面状态机中是很难实现的。 例如：

  1. Multiple states handling same event - Some states will only differ slight but still needs to handle the same event in the same way.  处理同一事件的多个状态 - 有些状态只会略有不同，但仍需要以相同的方式处理相同的事件。
  2. Large number of transitions - Similar to 1), an event resulting in a transition to a common state will also result in duplicating the handler.  大量转换 - 与 1) 类似，导致转换到公共状态的事件也将导致处理程序重复。
  3. Setup and Teardown - Managing a setup and teardown is normally handled in the transition event.  This becomes difficult to maintain as the number of states and transitions increase  设置和拆卸 - 管理设置和拆卸通常在转换事件中处理。 随着状态和转换数量的增加，这变得难以维持
  4. Unhandled events - States will normally handle explicit events it was designed for.  These unexpected events can indicate a bug or misbehavior  未处理的事件 - 状态通常会处理它设计用于的显式事件。 这些意外事件可能表明存在错误或不当行为

Fortunately using a Hierarchical State Machine Model addresses the issues above:幸运的是，使用分层状态机模型解决了上述问题：
  1. Parent state - Common event handling in multiple states can be moved to the parent state.  Where the child state only handles differences in handling of the event.  Similar to Object-oriented practices.  父状态 - 可以将多个状态中的公共事件处理移动到父状态。 其中子状态仅处理事件处理的差异。 类似于面向对象的实践。
  2. Parent Transition - Similar to 1), The parent state can manage common transitions out of the child state to a common state  父转换 - 类似于1)，父状态可以管理从子状态到公共状态的常见转换
  3. HSME_ENTRY and HSME_EXIT - These are built-in events that handle the Setup and Teardown events in a transition going from and into a state.  HSME_ENTRY 和 HSME_EXIT - 这些是内置事件，用于处理从状态到状态的转换中的设置和拆卸事件。
  4. Root Handler - All unhandled events get routed to the root handler which become detected.  根处理程序 - 所有未处理的事件都被路由到被检测到的根处理程序。

Rather than describe the HSM here, there are far better references and discussions on Unified Modeling Language (UML) and HSM that can be found on the internet.  So instead the next section shall describe how to use the HSM framework and how to implement / map your state machine model into code.

这里没有描述 HSM，而是在 Internet 上可以找到关于统一建模语言 (UML) 和 HSM 的更好的参考和讨论。 因此，下一节将描述如何使用 HSM 框架以及如何实现/映射你的状态机模型到代码中。


2. Using HSM Framework:
=======================
After drawing your HSM model using the UML syntax, you have 4 basic steps:使用 UML 语法绘制 HSM 模型后，你有 4 个基本步骤：
  1. Define the events and states  定义事件和状态
  2. Implement each of the state's event handler  实现每个状态的事件处理程序
  3. Create the HSM states and HSM instances  创建 HSM 状态和 HSM 实例
  4. Embed the HSM_Run() into your application  将 HSM_Run() 嵌入到你的应用程序中

To simply the discussion of the HSM framework, I shall refer to the following example HSM state diagram that models a simple point and shoot camera.为了简单地讨论 HSM 框架，我将参考以下示例 HSM 状态图，该示例模拟了一个简单的傻瓜相机。
```
    +-------------------------+
    |           Off           |
    |-------------------------|<------@
    | entry / EnterLowPower() |
    | exit / ExitLowPower()   |
    +-------------------------+
        |               ^
       PWR             PWR
        V               |
    +-----------------------------------------------------------------------------+
    |                                    On                                       |
    |-----------------------------------------------------------------------------|
    | entry / OpenLens()                                                          |
    | exit / CloseLens()                                                          |
    | LOWBATT / BeepLowBattWarning()                                              |
    |                                                                             |
    |               @                  +----------------------------------------+ |
    |               |                  |                OnDisp                  | |
    |               V                  |----------------------------------------| |
    |  +-------------------------+     | entry / TurnOnLCD()                    | |
    |  |         OnShoot         |     | exit / TurnOffLCD()                    | |
    |  |-------------------------|     |                                        | |
    |  | entry / EnableSensor()  |     |          +---------------------------+ | |
    |  | exit / DisableSensor()  |------MODE----->|         OnDispPlay        | | |
    |  | RELEASE / TakePicture() |     |          |---------------------------| | |
    |  +-------------------------+     |          | entry / DisplayPicture()  | | |
    |               ^                  |          +---------------------------+ | |
    |               |                  |                        |               | |
    |               |                  |                      MODE              | |
    |               |                  |                        V               | |
    |               |                  |          +---------------------------+ | |
    |               |                  |          |        OnDispMenu         | | |
    |               +----------MODE---------------|---------------------------| | |
    |                                  |          | entry / DisplayMenu()     | | |
    |                                  |          +---------------------------+ | |
    |                                  |                                        | |
    |                                  +----------------------------------------+ |
    |                                                                             |
    +-----------------------------------------------------------------------------+
```
This camera features 3 user button events **(PWR, RELEASE, MODE)** and a **LOWBATT** event generated by hardware.  The following describes the events:该相机具有 3 个用户按钮事件（PWR、RELEASE、MODE）和一个由硬件生成的 LOWBATT 事件。下面对事件进行说明：
  * **PWR**: This event can happen at anytime and must be handled in all states 此事件随时可能发生，必须在所有状态下进行处理
  * **RELEASE**: This shutter release event is only handled when the camera is in the picture shoot mode 此快门释放事件仅在相机处于拍照模式时处理
  * **MODE**: This event is handled only in the ON state of the camera and used to toggle the camera mode operation 此事件仅在相机开启状态下处理，用于切换相机模式操作
  * **LOWBATT**: This event can be generated at anytime while the camera is on 此事件可以在相机开启时随时生成

The camera is implemented using 6 states, 2 of which are parent states ("On" and "OnDisp").  The following describes the states: 相机使用 6 种状态实现，其中 2 种是父状态（“On”和“OnDisp”）。下面描述了这些状态：
  * **Off**: In this state, the camera lens is closed and in a lower power mode 在此状态下，相机镜头关闭并处于低功耗模式
  * **On**: This is a parent state where the camera lens cover is open and powered on 这是相机镜头盖打开并通电的父状态
  * **OnShoot**: This is a child state where the camera sensor is on and ready to take a picture 这是相机传感器打开并准备拍照的子状态
  * **OnDisp**: This is a parent state where the LCD is turned on for Menu or Picture review 这是一个父状态，其中 LCD 打开以进行菜单或图片查看
  * **OnDispPlay**: This is a child state where the Picture can be reviewed on the LCD 这是可以在 LCD 上查看图片的子状态
  * **OnDispMenu**: This is a child state where the Help Menu is displayed showing the status 这是一个子状态，其中显示帮助菜单显示状态


2.1: Define the events and states:
----------------------------------
2.1.1: Create a new header that will define your HSM and include the "hsm.h" header 创建将定义你的 HSM 并包含“hsm.h”头文件

```C
    #include "hsm.h"
```
2.1.2: Enumerate the HSM events (HSME) used by state machine.  HSME are normally 32-bit, but this can be changed to suit the platform.  The user-defined events can be any number as long as the following reserved values are not used (**HSME_NULL(0), HSME_INIT(-3), HSME_ENTRY(-2), HSME_EXIT(-1)**).  You can enumerate from the defined value HSME_START(1) 枚举状态机使用的 HSM 事件 (HSME)。 HSME 通常是 32 位，但可以更改以适应平台。 只要不使用以下保留值（HSME_NULL(0)、HSME_INIT(-3)、HSME_ENTRY(-2)、HSME_EXIT(-1)），用户定义的事件可以是任意数量。 你可以从定义的值 HSME_START(1) 中枚举

```C
    #define HSME_PWR        (HSME_START)
    #define HSME_RELEASE    (HSME_START + 1)
    #define HSME_MODE       (HSME_START + 2)
    #define HSME_LOWBATT    (HSME_START + 3)
```
2.1.3: Derive the state machine class by inheriting the HSM class.  In C, define the state machine with struct and declare the first member as parent of type HSM.  Add additonal members that are relevant to the state machine's context.  This shall be used to instantiate any number of state machines objects 通过继承 HSM 类派生状态机类。 在 C 中，使用 struct 定义状态机并将第一个成员声明为 HSM 类型的父级。 添加与状态机上下文相关的其他成员。 这将用于实例化任意数量的状态机对象

```C
    typedef struct CAMERA_T
    {
        // Parent
        HSM parent;

        // Child members
        char param1;
        char param2;
    } CAMERA;
```
2.1.4: Create a new source file and declare the singleton HSM_STATE objects for each state modeled in your UML State Diagram.  These state objects are later used to bind with the state handler and used for state transitions. 创建一个新的源文件并为 UML 状态图中建模的每个状态声明单例 HSM_STATE 对象。 这些状态对象稍后用于与状态处理程序绑定并用于状态转换。

```C
    HSM_STATE CAMERA_StateOff;
    HSM_STATE CAMERA_StateOn;
    HSM_STATE CAMERA_StateOnShoot;
    HSM_STATE CAMERA_StateOnDisp;
    HSM_STATE CAMERA_StateOnDispPlay;
    HSM_STATE CAMERA_StateOnDispMenu;
```

2.2: Implement each of the state's event handler
------------------------------------------------
For this section, we shall refer to the example Camera state "OnShoot": 对于本节，我们将参考示例相机状态“OnShoot”：
```
                 @
                 |
                 V
    +-------------------------+
    |         OnShoot         |
    |-------------------------|
    | entry / EnableSensor()  |
    | exit / DisableSensor()  |------MODE----->
    | RELEASE / TakePicture() |
    +-------------------------+
```
```C
 1  HSM_EVENT CAMERA_StateOnShootHndlr(HSM *This, HSM_EVENT event, void *param)
 2  {
 3      if (event == HSME_ENTRY)
 4      {
 5          printf("\tEnable Sensor\n");
 6      }
 7      else if (event == HSME_EXIT)
 8      {
 9          printf("\tDisable Sensor\n");
10      }
11      else if (event == HSME_RELEASE)
12      {
13          printf("\tCLICK!, save photo\n");
14          return 0;
15      }
16      else if (event == HSME_MODE)
17      {
18          HSM_Tran(This, &CAMERA_StateOnDispPlay, 0, NULL);
19          return 0;
20      }
21      return event;
22  }
```
2.2.1: Here we define the State Handler that is associated with the **HSM_STATE** object.  Each state handler must use the following prototype: 这里我们定义了与 **HSM_STATE** 对象关联的 State Handler。 每个状态处理程序必须使用以下原型：

> HSM_EVENT CAMERA_StateOnShootHndlr(HSM *This, HSM_EVENT event, void *param);  
> where:
> * **This**  - Pointer to the state machine instance.  Typecast to access derived class members 指向状态机实例的指针。 类型转换以访问派生类成员
> * **event** - The enumerated HSM Events that maybe handled by this state as defined in section 2.1.2 可能由此状态处理的枚举 HSM 事件，如第 2.1.2 节中所定义
> * **param** - [Optional] argument associated with the event [可选] 与事件关联的参数

2.2.2: When events are sent to the state machine (via HSM_Run(...)), the current state handler will be passed with the "event" and "param" which the state handler will perform some action to AND then perform one of the following: 当事件被发送到状态机（通过 HSM_Run(...)）时，当前状态处理程序将与“事件”和“参数”一起传递，状态处理程序将对它们执行一些操作，然后执行以下操作之一 ：

  * Consume the the event and returning NULL(0) (SEE LINE 14 and LINE 19) 使用该事件并返回 NULL(0)（参见第 14 行和第 19 行）
  * Or pass it to the parent state by returning the event (SEE LINE 21) 或者通过返回事件将其传递给父状态（见第 21 行）
*NOTE:* The event can be handled by the state and still pass/defer the event to the parent for common handling. *注意：* 事件可以由状态处理，并且仍然将事件传递/推迟到父级以进行通用处理。

2.2.3: If an event triggers a state transition, use the following API (SEE LINE 18): 如果事件触发状态转换，请使用以下 API（参见第 18 行）：

> void HSM_Tran(HSM *This, HSM_STATE *nextState, void *param, void (*method)(HSM *This, void *param))  
> where:
> * **This**      - Pointer to the state machine instance. 指向状态机实例的指针。
> * **nextState** - pointer to the state object of the next state as defined in section 2.1.4 指向 2.1.4 节中定义的下一个状态的状态对象的指针
> * **param**     - [optional] argument passed to next state handler and optional method [可选] 参数传递给下一个状态处理程序和可选方法
> * **method**    - A callback for lamda like functions which is invoked after all HSME_ENTRY events and before any HSME_EXIT events  lamda 类函数的回调，在所有 HSME_ENTRY 事件之后和任何 HSME_EXIT 事件之前调用
> *NOTE:* The HSM_Tran(...) API will generate HSME_EXIT events to all exiting states (e.g. OnShoot) up to a common parent, invoke the "method" callback if set, generate HSME_ENTRY events to the entered states (e.g. OnDisp and OnDispPlay) from the common parent and then finally generate HSME_INIT event to the final state *注意：* HSM_Tran(...) API 将生成 HSME_EXIT 事件到所有退出状态（例如 OnShoot）直到一个公共父，调用“方法”回调（如果设置），生成 HSME_ENTRY 事件到输入状态（例如 OnDisp 和 OnDispPlay) 从共同的父级，然后最终生成 HSME_INIT 事件到最终状态

2.2.4: Implement the optional handling of the HSME_ENTRY, HSME_EXIT, and/or HSME_INIT events as required by your HSM State Diagram.  These events are generated by the HSM framework on state transition.  It is not necessary to consume these events as the framework will never pass these to the parent state.  The following is a description of the Framework generated events: 根据你的 HSM 状态图的要求，实现 HSME_ENTRY、HSME_EXIT 和/或 HSME_INIT 事件的可选处理。 这些事件由 HSM 框架在状态转换时生成。 没有必要使用这些事件，因为框架永远不会将它们传递给父状态。 以下是框架生成事件的说明：

  1. **HSME_ENTRY** - Used to trigger any SETUP required on entry to the state (SEE LINE 3) 用于触发进入状态所需的任何设置（参见第 3 行）
  2. **HSME_EXIT** - Used to trigger any TEARDOWN required on exit from the state (SEE LINE 7) 用于触发退出状态所需的任何 TEARDOWN（参见第 7 行）
  3. **HSME_INIT** - This event is generated after all HSME_ENTRY and HSME_EXIT have been handled and state has been set to the new state.  This is normally used to trigger another transition that is dependent on some guard condition (i.e. depends on some state machine context) 在处理完所有 HSME_ENTRY 和 HSME_EXIT 并且状态已设置为新状态后生成此事件。 这通常用于触发另一个依赖于某些保护条件的转换（即依赖于某些状态机上下文）


2.3: Create the HSM states and HSM instances
--------------------------------------------
2.3.1: The state machine is defined by its states.  So with the HSM_STATE objects declared and their respective State handlers defined, the state objects and handlers need to be binded using the following API: 状态机由其状态定义。 因此，在声明了 HSM_STATE 对象并定义了它们各自的状态处理程序后，需要使用以下 API 绑定状态对象和处理程序：

> void HSM_STATE_Create(HSM_STATE *This, const char *name, HSM_FN handler, HSM_STATE *parent);  
> where:
> * **This**    - Pointer to state object as defined in section 2.1.4 指向第 2.1.4 节中定义的状态对象的指针
> * **name**    - Name of State used in debug 调试中使用的状态名称
> * **handler** - State handler as defined in section 2.2 to bind with state object 2.2 节中定义的状态处理程序，用于绑定状态对象
> * **parent**  - Pointer to parent state object as defined in section 2.2 指向第 2.2 节中定义的父状态对象的指针

For example using the Camera HSM Model in section 2, we can define the hierarchy as follows: 例如使用第 2 节中的 Camera HSM 模型，我们可以定义层次结构如下：
```C
    HSM_STATE_Create(&CAMERA_StateOff, "Off", CAMERA_StateOffHndlr, NULL);
    HSM_STATE_Create(&CAMERA_StateOn, "On", CAMERA_StateOnHndlr, NULL);
    HSM_STATE_Create(&CAMERA_StateOnShoot, "On.Shoot", CAMERA_StateOnShootHndlr, &CAMERA_StateOn);
    HSM_STATE_Create(&CAMERA_StateOnDisp, "On.Disp", CAMERA_StateOnDispHndlr, &CAMERA_StateOn);
    HSM_STATE_Create(&CAMERA_StateOnDispPlay, "On.Disp.Play", CAMERA_StateOnDispPlayHndlr, &CAMERA_StateOnDisp);
    HSM_STATE_Create(&CAMERA_StateOnDispMenu, "On.Disp.Menu", CAMERA_StateOnDispMenuHndlr, &CAMERA_StateOnDisp);
```

2.3.2: There can be many instances of the state machine defined in 2.3.1 by declare HSM object and initialize the state machine instance using the following API: 2.3.1中定义的状态机实例可以有多个，通过声明HSM对象并使用以下API初始化状态机实例：

> void HSM_Create(HSM *This, const char *name, HSM_STATE *initState);  
> where:
> * **This** - Pointer to the state machine object 指向状态机对象的指针
> * **name** - Name of the state machine, Unique to this instance 状态机的名称，此实例唯一
> * **initState** - Initialize state of the state machine and how the state machine is associated 初始化状态机的状态以及状态机的关联方式

For example: 例如：
```C
    CAMERA basic;
    HSM_Create((HSM *)&basic name, &CAMERA_StateOff);
```
This will set the state machine state to CAMERA_StateOff and generate the HSME_ENTRY and HSME_INIT event to this state 这会将状态机状态设置为 CAMERA_StateOff 并将 HSME_ENTRY 和 HSME_INIT 事件生成到此状态


2.4: Embed the HSM_Run() into your application
----------------------------------------------
Running the HSM is as simple as calling the _HSM_Run()_ API and passing the HSM object along with the "event" and optional "param".  It is up to the state handler to decide what to do with the event and param.  There are no global variables except in one case (SEE 3.1.2), so all of the functions in the HSM framework are re-entrant. 运行 HSM 就像调用 _HSM_Run()_ API 并传递 HSM 对象以及“事件”和可选的“参数”一样简单。 由状态处理程序决定如何处理事件和参数。 除了一种情况（参见 3.1.2）外，没有全局变量，因此 HSM 框架中的所有函数都是可重入的。

A typical use is servicing an event by simply feeding the enumerated event and optional parameter to the HSM object. 一个典型的用途是通过简单地将枚举事件和可选参数提供给 HSM 对象来为事件提供服务。

For Example: 例如：
```C
    HSM_Run(&basic, HSME_PWR, 0);
```
Will generate the following logs (assuming debug is enabled): 将生成以下日志（假设启用了调试）：
```
    [DBG] Run Canon[Off](evt:HSME_PWR, param:00000000)
    [DBG] Tran Canon[Off -> On]
    [DBG]   Canon[Off](EXIT)
        Exit Low Power Mode
    [DBG]   Canon[On](ENTRY)
        Open Lens
    [DBG]   Canon[On](INIT)
```

3. Using HSM Advance Features:
==============================
This HSM Framework provides numerous configurable options to control the level of debug as well optimize for memory constrained systems.  All of these features are configured in hsm.h 此 HSM 框架提供了许多可配置选项来控制调试级别以及针对内存受限系统进行优化。 所有这些功能都在 hsm.h 中配置

3.1. Basic Debug Features
-------------------------
It can be difficult to debug the HSM without any type of logging, so it is highly recommended to develop with the debug features on and then disable them in production.  Be sure to run the camera demo to get a feel for the debugging capabilities and the HSM framework.  To enable debugging: 在没有任何类型的日志记录的情况下调试 HSM 可能很困难，因此强烈建议使用调试功能进行开发，然后在生产中禁用它们。请务必运行相机演示以了解调试功能和 HSM 框架。要启用调试：
  1. Enable the compiler flag **HSM_FEATURE_DEBUG_ENABLE** to compile in the HSM debug logging features 启用编译器标志 **HSM_FEATURE_DEBUG_ENABLE** 以在 HSM 调试日志功能中进行编译
  2. If the system does not have _printf(...)_ available, then enable the compiler flag **HSM_FEATURE_DEBUG_EMBEDDED** and implement application specific **DEBUG_OUT(...) ** 如果系统没有 _printf(...)_ 可用，则启用编译器标志 **HSM_FEATURE_DEBUG_EMBEDDED** 并实现应用程序特定的 **DEBUG_OUT(...)**
  3. Set **HSM_NEWLINE** to proper carriage return and line feed matching the host environment (i.e. linux, OSX or windows) 设置为与主机环境（即 linux、OSX 或 Windows）匹配的正确回车和换行
  4. If the host is capable of rending terminal colors, then enable **HSM_FEATURE_DEBUG_COLOR** which colorizes the print for easier readability 如果主机能够渲染终端颜色，则启用 **HSM_FEATURE_DEBUG_COLOR** 为打印着色以提高可读性
  5. Each state machine object can enable or disable debug in run time using **HSM_SET_DEBUG()** and passing the flags: **{HSM_SHOW_RUN, HSM_SHOW_TRAN, HSM_SHOW_INTACT, HSM_SHOW_ALL}** to enable debug from _HSM_Run()_ and _HSM_Tran()_ 每个状态机对象都可以在运行时启用或禁用调试，使用 **HSM_SET_DEBUG()** 并传递标志：**{HSM_SHOW_RUN, HSM_SHOW_TRAN, HSM_SHOW_INTACT, HSM_SHOW_ALL}** 以启用来自 _HSM_Run()_ 和 _HSM_Tran 的调试()_

    * HSM_SHOW_RUN - Shows event logging from calls to HSM_Run() 显示调用 HSM_Run() 的事件记录
    * HSM_SHOW_TRAN - Only shows the state to state transition logging from calls to HSM_Tran() 仅显示从调用到 HSM_Tran() 的状态到状态转换日志记录
    * HSM_SHOW_INTACT - Only shows the internal action logging (i.e. HSM_ENTRY, HSM_EXIT, HSME_INIT) from calls to HSM_Tran() 仅显示调用 HSM_Tran() 的内部操作日志记录
    * HSM_SHOW_ALL - Shows all logging 显示所有日志

3.2 Advance Debug Features
--------------------------
These feature are only supported if **HSM_FEATURE_DEBUG_ENABLE** is enabled 仅当启用 **HSM_FEATURE_DEBUG_ENABLE** 时才支持这些功能

3.2.1: HSM_SET_PREFIX
Each state machine instance can have its own prefix which is commonly used to filter the HSM debug messages with grep 每个状态机实例都可以有自己的前缀，通常用于使用 grep 过滤 HSM 调试消息
For example, using **HSM_SET_PREFIX((HSM *)This, "[DBG] ")** 例如，使用 **HSM_SET_PREFIX((HSM *)This, "[DBG] ")**

```
    [DBG] Run Canon[On.Disp.Menu](evt:HSME_LOWBATT, param:00000000)
    [DBG]   evt:HSME_LOWBATT unhandled, passing to Canon[On.Disp]
    [DBG]   evt:HSME_LOWBATT unhandled, passing to Canon[On]
        Beep low battery warning
```

3.2.2: HSM_SUPPRESS_DEBUG
Some state machines can generate a large number of periodic events which generates a lot of noise in the debug logs.  So it is often desireable to momentarily suppress the debug messages for one run (i.e. one call to HSM_Run()).  Simply call **HSM_SUPPRESS_DEBUG()** and pass the flags: __{HSM_SHOW_RUN, HSM_SHOW_TRAN, HSM_SHOW_INTACT, HSM_SHOW_ALL}__ to suppress debug for one run.  The original flags for **HSM_SET_DEBUG()** are restored for the next run 某些状态机会生成大量周期性事件，从而在调试日志中产生大量干扰。 因此，通常希望暂时抑制一次运行的调试消息（即对 HSM_Run() 的一次调用）。 只需调用 **HSM_SUPPRESS_DEBUG()** 并传递标志：__{HSM_SHOW_RUN, HSM_SHOW_TRAN, HSM_SHOW_INTACT, HSM_SHOW_ALL}__ 以抑制一次运行的调试。 为下次运行恢复 **HSM_SET_DEBUG()** 的原始标志

3.2.3: HSM_DEBUG_EVT2STR
When reviewing the debug logs, it is difficult to manually decode the encoded event values like this: 查看调试日志时，很难像这样手动解码编码的事件值：

```
    [DBG] Run Canon[On.Disp.Menu](evt:4, param:00000000)
    [DBG]   evt:4 unhandled, passing to Canon[On.Disp]
    [DBG]   evt:4 unhandled, passing to Canon[On]
```
It is significatly easier if the output was human readable like this: 如果输出是人类可读的，则要容易得多：
```
    [DBG] Run Canon[On.Disp.Menu](evt:HSME_LOWBATT, param:00000000)
    [DBG]   evt:HSME_LOWBATT unhandled, passing to Canon[On.Disp]
    [DBG]   evt:HSME_LOWBATT unhandled, passing to Canon[On]
```
To enable this feature, define a function that will translate the enumerated event with a string. 要启用此功能，请定义一个函数，该函数将使用字符串转换枚举事件。
For example: 例如：

```C
    const char *HSM_Evt2Str(uint32_t event)
    {
        switch(event)
        {
        case HSME_PWR:
            return "HSME_PWR";
        case HSME_RELEASE:
            return "HSME_RELEASE";
        case HSME_MODE:
            return "HSME_MODE";
        case HSME_LOWBATT:
            return "HSME_LOWBATT";
        }
    }
```
Then in the makefile define HSM_DEBUG_EVT2STR to the above function: 然后在 makefile 中将 HSM_DEBUG_EVT2STR 定义为上述函数：
```
    # Add this define for customized HSM_EVENT value to string function for human readable debug
    CFLAGS += -DHSM_DEBUG_EVT2STR=HSM_Evt2Str
```

3.2.4: HSM_FEATURE_DEBUG_NESTED_CALL
This is a special debug feature that is useful for constrained systems that have multiple running HSM instances operating in a single thread.  This necessitates calling the _HSM_Run()_ from within the state handler (i.e. nesting the HSM) which makes debugging confusing (i.e. interleaved debug logs). 这是一个特殊的调试功能，对于在单个线程中运行多个正在运行的 HSM 实例的受限系统非常有用。 这需要从状态处理程序中调用 _HSM_Run()_（即嵌套 HSM），这使调试变得混乱（即交错的调试日志）。

To eliminate the confusion, you can enable the flag **HSM_FEATURE_DEBUG_NESTED_CALL** which will indent the output by the number of nesting levels.  However there is one caveat, this will make calls to _HSM_Run()_ non-reentrant as a global will need to be defined to tracked the nesting levels which isn't really a penalty. 为了消除混淆，您可以启用标志 **HSM_FEATURE_DEBUG_NESTED_CALL**，它将按照嵌套级别的数量缩进输出。 但是有一个警告，这将调用 _HSM_Run()_ 不可重入，因为需要定义全局以跟踪嵌套级别，这并不是真正的惩罚。

It is important to note that the global **apucHsmNestIndent[]** may need to extended if the nesting gets too deep 需要注意的是，如果嵌套太深，全局 **apucHsmNestIndent[]** 可能需要扩展
```C
    const char *apucHsmNestIndent[] = { "", "", "\t", "\t\t", "\t\t\t", "\t\t\t\t"};
```

3.3: Optimization Features
--------------------------
The following features can be configure to decrease the memory footprint and decrease the latency and should only be disabled for a system that has been well tested, else debugging can be difficult 可以配置以下功能以减少内存占用并减少延迟，并且只能在经过良好测试的系统中禁用，否则调试可能会很困难

3.3.1: HSM_FEATURE_SAFETY_CHECK
Enabling this feature performs sanity checks on the state handler performing illegal calls which result in erroneous behavior.  This can be disabled in production after full regression testing to save just a little memory and latency 启用此功能将对执行导致错误行为的非法调用的状态处理程序执行健全性检查。 这可以在完全回归测试后在生产中禁用，以节省一点内存和延迟

3.3.2: HSM_FEATURE_INIT
Enabling this feature enables generation of the HSME_INIT event during a call to HSM_Tran() from the state handler.  If you do not use the HSME_INIT in your UML state diagram, you can disable this feature to save a little memory and improve latency 启用此功能可在从状态处理程序调用 HSM_Tran() 期间生成 HSME_INIT 事件。 如果您在 UML 状态图中不使用 HSME_INIT，您可以禁用此功能以节省一点内存并改善延迟

3.3.3: HSM_MAX_DEPTH
This is a configurable value for the maximum depth (i.e. nesting) of states you are designing.  HSM_Tran() uses this value to allocate the memory required to performs a run-time trace of the state ancestry.  HSM_STATE_Create() shall assert if the state creation exceeds the maximum depth, in which case you should either redesign your HSM or increase this value (Default is 5) 这是您正在设计的状态的最大深度（即嵌套）的可配置值。 HSM_Tran() 使用此值来分配执行状态祖先的运行时跟踪所需的内存。 如果状态创建超过最大深度，则 HSM_STATE_Create() 应断言，在这种情况下，您应该重新设计 HSM 或增加此值（默认值为 5）


4. HSM Cookbook and Design Patterns:
====================================
4.1: Make a transition decision on state entry, try using HSME_INIT 做状态进入的过渡决策，尝试使用HSME_INIT
-------------------------------------------------------------------
Normally when we enter a state, there is some SETUP operation (initiated by HSME_ENTRY) that may fail (e.g allocating memory) which would cause the system to fail if allowed to continue.  In this case, we should take a course of action such as changing to another state. 通常当我们进入一个状态时，有一些 SETUP 操作（由 HSME_ENTRY 启动）可能会失败（例如分配内存），如果允许继续，这将导致系统失败。 在这种情况下，我们应该采取一系列行动，例如更改为另一种状态。

To illustrate, we shall use our camera model again where we need to handle the case where the camera lens fails to open (e.g. its obstructed or jammed).  In this case we should go back to the Off state to prevent further damage. 为了说明这一点，我们将再次使用我们的相机模型，我们需要处理相机镜头无法打开的情况（例如，它被阻挡或卡住）。 在这种情况下，我们应该回到关闭状态以防止进一步损坏。
```
    +-------------------------+
    |           Off           |
    |-------------------------|<------O
    | entry / EnterLowPower() |
    | exit / ExitLowPower()   |
    +-------------------------+
        |           ^       ^
       PWR         PWR      |
        V           |       |
    +-----------------------|-----------------------------------------------------+
    |                       |            On                                       |
    |---------------------- |-----------------------------------------------------|
    | entry / OpenLens()    |                                                     |
    | exit / CloseLens()    |                                                     |
    |                       |                                                     |
    |            [Lens Failed to Open]                                            |
    |                       |                                                     |
    |                       @          +----------------------------------------+ |
    |                       |          |                OnDisp                  | |
    |                       V          |----------------------------------------| |
    |  +-------------------------+     | entry / TurnOnLCD()                    | |
    |  |         OnShoot         |     | exit / TurnOffLCD()                    | |
    |  |-------------------------|     |                                        | |
    |  | entry / EnableSensor()  |     |          +---------------------------+ | |
    |  | exit / DisableSensor()  |------MODE----->|         OnDispPlay        | | |
    |  | RELEASE / TakePicture() |     |          +---------------------------+ | |
    |  +-------------------------+     |                                        | |
    |                                  +----------------------------------------+ |
    +-----------------------------------------------------------------------------+
```

Here we check if the lens is open successfully.  If its not, then we can transition back to Off (or some other safe state) instead of the OnShoot state. 这里我们检查一下镜头是否打开成功。 如果不是，那么我们可以转换回 Off（或其他一些安全状态）而不是 OnShoot 状态。
```C
    HSM_EVENT CAMERA_StateOnHndlr(HSM *This, HSM_EVENT event, void *param)
    {
        if (event == HSME_ENTRY)
        {
            printf ("\tOpen Lens\n");
        }
    ..
    ..
        else if (event == HSME_INIT)
        {
            if (isLensOpen())
            {
                HSM_Tran(This, &CAMERA_StateOnShoot, 0, NULL);
            }
            else
            {
                printf ("\tBeep Failure Warning\n");
                HSM_Tran(This, &CAMERA_StateOff, 0, NULL);
            }
        }
    ..
    ..
    }
```
**NOTE!!** It is illegal to invoke a HSM_Tran() for the HSME_ENTRY and HSME_EXIT event, since this would create a recursion in HSM_Tran().  Thus only HSM_Tran() can only be invoked by user event or HSME_INIT.  **注意！！** 为 HSME_ENTRY 和 HSME_EXIT 事件调用 HSM_Tran() 是非法的，因为这会在 HSM_Tran() 中创建递归。 因此只有 HSM_Tran() 只能由用户事件或 HSME_INIT 调用。

4.2. Run Concurrent model (i.e. concurrent states), try using the parent state as a proxy
-----------------------------------------------------------------------------------------
TODO

4.3. Guard Condition, try using HSM_IsInState()
-----------------------------------------------
TODO

4.4. Using child state as filter
--------------------------------
TODO
