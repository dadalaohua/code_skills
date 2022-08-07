# BUILD_BUG_ON_ZERO

Force a compilation error if condition is true, but also produce a result (of value 0 and type size_t), so the expression can be used e.g. in a structure initializer (or where-ever else comma expressions aren't permitted).

如果条件为真，则强制编译错误，但也产生一个结果（值为0，类型为size_t），因此表达式可以用于例如结构体初始化中（或者任何其他不允许使用逗号表达式的地方）。