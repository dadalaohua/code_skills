# MinUnit

https://github.com/siu/minunit

Minunit is a minimal unit testing framework for C/C++ self-contained in a single header file.

Minunit是一个包含在单个头文件中的C/ c++的最小单元测试框架。

It provides a way to define and configure test suites and a few handy assertion types. It reports the summary of the number of tests run, number of assertions and time elapsed.

它提供了一种定义和配置测试套件以及一些方便的断言类型的方法。它报告运行的测试数、断言数和所用时间的摘要。

## Setup and teardown functions 安装和卸载功能

One can define setup and teardown functions and configure the test suite to run them by using the macro `MU_SUITE_CONFIGURE` with within a `MU_TEST_SUITE` declaration.

我们可以定义setup和teardown函数，并通过在 `MU_TEST_SUITE`声明中使用宏`MU_SUITE_CONFIGURE`来配置测试套件来运行它们。

## Assertion types 断言类型

`mu_check(condition)`: will pass if the condition is evaluated to `true`, otherwise it will show the condition as the error message

如果条件被评估为' true '将通过，否则它将显示条件作为错误消息

`mu_fail(message)`: will fail and show the message

会失败并显示消息

`mu_assert(condition, message)`: will pass if the condition is `true`, otherwise it will show the failed condition and the message

如果条件是`true`将通过，否则它将显示失败的条件和消息

`mu_assert_int_eq(expected, result)`: it will pass if the two numbers are equal or show their values as the error message

如果这两个数字相等将通过，否则将它们的值显示为错误消息

`mu_assert_double_eq(expected, result)`: it will pass if the two values are almost equal or show their values as the error message. The value of `MINUNIT_EPSILON` sets the threshold to determine if the values are close enough.

如果这两个值几乎相等，它将通过，或者将它们的值显示为错误消息。`MINUNIT_EPSILON`的值设置了阈值，以确定这些值是否足够接近。

