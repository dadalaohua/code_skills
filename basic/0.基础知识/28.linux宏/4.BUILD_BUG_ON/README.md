# BUILD_BUG_ON 

BUILD_BUG_ON - break compile if a condition is true.

BUILD_BUG_ON - 如果条件为真，则中断编译。 

@condition: the condition which the compiler should know is false.

@condition:编译器应该知道的条件是假的。 

If you have some code which relies on certain constants being equal, or some other compile-time-evaluated condition, you should use BUILD_BUG_ON to detect if someone changes it.

如果你有一些依赖于某些常量相等的代码，或其他一些编译时计算条件，你应该使用BUILD_BUG_ON来检测是否有人更改了它。 

The implementation uses gcc's reluctance to create a negative array, but gcc(as of 4.4) only emits that error for obvious cases (e.g. not arguments to inline functions).  Luckily, in 4.3 they added the "error" function attribute just for this type of case.  Thus, we use a negative sized array(should always create an error on gcc versions older than 4.4) and then call an undefined function with the error attribute (should always create an error on gcc 4.3 and later).  If for some reason, neither creates a compile-time error, we'll still have a link-time error, which is harder to track down.

这个实现使用了gcc不愿意创建负数组的特性，但是gcc（从4.4开始）只在明显的情况下发出这个错误（例如，不是内联函数的参数）。 幸运的是，在4.3中，他们为这种情况添加了 "error "函数属性。 因此，我们使用一个负数组（在4.4以上的gcc版本中应该总是产生错误），然后调用一个带有错误属性的未定义函数（在gcc 4.3及以后的版本中应该总是产生错误）。 如果由于某种原因，两者都没有产生编译时错误，我们仍然会有一个链接时错误，这就更难追踪了。