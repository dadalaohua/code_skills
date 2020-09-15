- # C 库宏 - offsetof()

  ## 描述

  C 库宏 **offsetof(type, member-designator)** 会生成一个类型为 **size_t** 的整型常量，它是一个结构成员相对于结构开头的字节偏移量。成员是由 member-designator 给定的，结构的名称是在 type 中给定的。

  ## 声明

  下面是 offsetof() 宏的声明。

  ```c
  offsetof(type, member-designator)
  ```

  ## 参数

  - **type**  -- 这是一个 class 类型，其中，member-designator 是一个有效的成员指示器。
  - **member-designator**  -- 这是一个 class 类型的成员指示器。

  ## 返回值

  该宏返回类型为 **size_t** 的值，表示 type 中成员的偏移量。