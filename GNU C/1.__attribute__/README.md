# \_\_attribute\_\_概述



##### **_\_attribute\_\_**语法的来源

GNU C 的一大特色就是**\_\_attribute\_\_** 机制。**\_\_attribute\_\_** 可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。

其位置约束为：  放于声明的尾部“;” 之前

**\_\_attribute\_\_** 书写特征为:  **\_\_attribute\_\_** 前后都有两个下划线，并切后面会紧跟一对原括弧，括弧里面是相应的**\_\_attribute\_\_** 参数。

**\_\_attribute\_\_** 语法格式为:  **\_\_attribute\_\_** ((attribute-list))

当**\_\_attribute\_\_**  用于修饰对象时，它就如同C 语言语法体系结构的类型限定符，跟const , volatile , restrict 等属一类。
 当**\_\_attribute\_\_** 用于修饰函数时，它就相当于一个函数说明符，跟inline，*Noreturn 属同一类。
 当**\_\_attribute\_\_**  用于修饰一个结构体，联合体或者枚举类型，该限定符只能放在类型标识符之前。

##### **\_\_attribute\_\_** 所支持的类型

当我们需要识别当前编译器能否支持GNU 语法拓展，我们可以使用 **\_\_GNU \_\_** 宏作为区分

| 函数属性(Function Attribute) | 类型属性(Type Attributes) | 变量属性(Variable Attribute)  | Clang特有的  |
| ---------------------------- | ------------------------- | ----------------------------- | ------------ |
| noreturn                     | aligned                   | alias                         | availability |
| noinline                     | packed                    | at(address)                   | overloadable |
| always_inline                | bitband                   | aligned                       |              |
| flatten                      |                           | deprecated                    |              |
| pure                         |                           | noinline                      |              |
| const                        |                           | packed                        |              |
| constructor                  |                           | weak                          |              |
| destructor                   |                           | weakref(“target”)             |              |
| sentinel                     |                           | section(“name”)               |              |
| format                       |                           | unused                        |              |
| format_arg                   |                           | used                          |              |
| section                      |                           | visibility(“visibility_type”) |              |
| used                         |                           | zero_init                     |              |
| unused                       |                           |                               |              |
| deprecated                   |                           |                               |              |
| weak                         |                           |                               |              |
| malloc                       |                           |                               |              |
| alias                        |                           |                               |              |
| warn_unused_result           |                           |                               |              |
| nonnull                      |                           |                               |              |
| nothrow (不抛出C++ 异常)     |                           |                               |              |