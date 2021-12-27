# greatest

https://github.com/silentbicycle/greatest

A testing system for C, contained in 1 header file.

一个 c 语言的测试系统，包含在一个头文件中。



## Basic Usage 基本用法

```c
#include "greatest.h"

/* A test runs various assertions, then calls PASS(), FAIL(), or SKIP(). */
TEST x_should_equal_1(void) {
    int x = 1;
    /* Compare, with an automatic "1 != x" failure message */
    ASSERT_EQ(1, x);

    /* Compare, with a custom failure message */
    ASSERT_EQm("Yikes, x doesn't equal 1", 1, x);

    /* Compare, and if they differ, print both values,
     * formatted like `printf("Expected: %d\nGot: %d\n", 1, x);` */
    ASSERT_EQ_FMT(1, x, "%d");
    PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(the_suite) {
    RUN_TEST(x_should_equal_1);
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

    /* Individual tests can be run directly in main, outside of suites. */
    /* RUN_TEST(x_should_equal_1); */

    /* Tests can also be gathered into test suites. */
    RUN_SUITE(the_suite);

    GREATEST_MAIN_END();        /* display results */
}
```

Output:

输出:

```
$ make simple && ./simple
cc -g -Wall -Werror -pedantic    simple.c   -o simple

* Suite the_suite:
.
1 test - 1 passed, 0 failed, 0 skipped (5 ticks, 0.000 sec)

Total: 1 test (47 ticks, 0.000 sec), 3 assertions
Pass: 1, fail: 0, skip: 0.
```

Tests are run with `RUN_TEST(test_name)`, which can be called directly from the test runner's `main` function or grouped into suites (which are run with `RUN_SUITE(suite_name)`). (Calls to `RUN_TEST` from inside another test are ignored.)

测试使用 RUN _ test (test _ name)运行，它可以直接从测试运行程序的主函数调用，也可以组合成套件(使用 RUN _ suite (suite _ name)运行)。(从另一个测试内部调用 RUN _ test 将被忽略。)

Test cases can be run with arguments: `RUN_TEST1(test_name, arg)` passes a single argument, and if C99 features are supported, then `RUN_TESTp(test_name, ...)` uses `__VA_ARGS__` to run a test case with one or mare arguments. `greatest_set_test_suffix` sets a name suffix, so output from the test runner can include info about arguments.

测试用例可以使用参数运行: RUN _ test1(Test _ name，arg)传递一个参数，如果支持 c99特性，那么 RUN _ testp (Test _ name，...)使用 _ VA _ args _ 使用一个或多个参数运行测试用例。将设置一个名称后缀，因此测试运行程序的输出可以包含有关参数的信息。

Test cases should call assertions and then end with `PASS()`, `SKIP()`, `FAIL()`, or their custom message variants (e.g. `SKIPm("TODO");`). If there are any test failures, the test runner will return 1, otherwise it will return 0. (Skips do not cause the test runner to report failure.)

测试用例应该调用断言，然后以 PASS ()、 SKIP ()、 FAIL ()或其自定义消息变体(例如 SKIPm (“ TODO”) ;)结束。如果有任何测试失败，测试运行程序将返回1，否则它将返回0。(跳槽不会导致测试运行人员报告失败。)

`PASS()`, `SKIP()`, `FAIL()`, and their custom message variants are macros that updating internal bookkeeping and then returning and enum value, such as `GREATEST_TEST_RES_FAIL`. They all `return` from the current test case function.

PASS ()、 SKIP ()、 FAIL ()及其自定义消息变体是宏，它们更新内部簿记，然后返回枚举值，如 GREATEST _ test _ res _ FAIL。它们都从当前的测试用例函数返回。

`PASS()`/`PASSm("msg")` prints as a dot when verbosity is zero, or the test name and custom message (if any) with verbosity >= 1.

PASS ()/PASSm (“ msg”)在 verbosity 为零时打印为一个点，或者测试名称和自定义消息(如果有的话)的 verbosity > = 1。

`FAIL()`/`FAILm("msg")` always prints "FAIL test_name: msg file:line".

FAIL ()/FAILm (“ msg”)总是打印“ FAIL test _ name: msg file: line”。

`SKIP()`/`SKIPm("msg")` prints as an 's' when verbosity is zero, or the test name and custom message (if any) with verbosity >= 1. Because skips are not treated as a failure by the test runner, they can be used to skip test cases that aren't relevant in a particular build or environment, a way to temporarily disable broken tests, or as a sort of todo list for tests and functionality under active development.

当详细程度为零时，SKIP ()/SKIPm (“ msg”)打印为‘ s’，或者测试名称和自定义消息(如果有的话)打印为详细程度 > = 1。因为跳过不会被测试运行程序视为失败，所以它们可以用来跳过与特定构建或环境无关的测试用例，一种暂时禁用失败测试的方法，或者作为正在开发的测试和功能的某种待办事项列表。

Tests and suites are just functions, so normal C scoping rules apply. For example, a test or suite named `main` will have a name collision.

测试和套件只是函数，因此应用正常的 c 范围规则。例如，名为 main 的测试或套件将有名称冲突。

(For more examples, look at `example.c` and `example_suite.c`.)

(要获得更多的例子，看 example.c 和 example_suite.c.)

## Filtering By Name 按名称过滤

greatest runs all tests by default, but can be configured to only run suites or tests whose names contain a filter string, and/or exclude tests whose name contains a filter string. When test name filtering and exclusion are used together, exclusion takes precedence.

默认情况下，greatest 运行所有测试，但是可以配置为只运行名称包含筛选字符串的套件或测试，以及/或者排除名称包含筛选字符串的测试。当同时使用测试名筛选和排除时，排除优先。

```
void greatest_set_suite_filter(const char *name);
void greatest_set_test_filter(const char *name);
void greatest_set_test_exclude(const char *name);
```

These correspond to the following command line test runner options:

这些对应于以下命令行测试运行器选项:

```
`-s SUITE`:   Only run suites whose names contain the string "SUITE"
`-t TEST`:    Only run tests whose names contain the string "TEST"
`-x EXCLUDE`: Exclude tests whose names contain the string "EXCLUDE"
```

For example, to run any tests with "tree" in the name, in suites with "pars" in the name (such as "parser"), but exclude any tests whose names also contain "slow":

例如，要运行名称中带有“ tree”的任何测试，名称中带有“ pars”的测试套件(比如“ parser”) ，但要排除名称中也包含“ slow”的任何测试:

```
./test_project -s pars -t tree -x slow
```

The string matching includes optional test name suffixes.

字符串匹配包括可选的测试名称后缀。

The `greatest_set_exact_name_match()` function and corresponding `-e` command line runner flag can be used to only run tests and/or suites whose names exactly match the name filter(s). Note: exact-match suite filtering by name will not skip tests that are run outside of any suite.

可以使用 greatest _ set _ exact _ name _ match ()函数和 corresponding-e 命令行 runner 标志只运行名称与名称 filter 完全匹配的测试和/或套件。注意: 按名称完全匹配的套件过滤将不会跳过在任何套件之外运行的测试。

## Available Assertions 可用断言

Assertions fail the current test unless some condition holds. All assertions have a custom message variant (with an `m` suffix), which takes a message string as its first argument. For example, the assertion `ASSERT_EQ(apple, orange);` could instead be used like `ASSERT_EQm("these should match", apple, orange)`. Non-message assertions create a default message.

断言不能通过当前的测试，除非某些条件成立。所有断言都有一个自定义的消息变体(带有 m 后缀) ，它以消息字符串作为第一个参数。例如，断言 ASSERT _ eq (apple，orange) ; 可以像 ASSERT _ eqm (“ these should match”，apple，orange)一样使用。非消息断言创建默认消息。

### `ASSERT(COND)`

Assert that `COND` evaluates to a true (non-zero) value.

断言 COND 的计算结果为 true (非零)值。

### `ASSERT_FALSE(COND)`

Assert that `COND` evaluates to a false (zero) value.

断言 COND 的计算结果为 false (零)值。

### `ASSERT_EQ(EXPECTED, ACTUAL)`

Assert that `EXPECTED == ACTUAL`. To print the values if they differ, use `ASSERT_EQ_FMT`. To compare with custom equality test and print functions, use `ASSERT_EQUAL_T` instead.

断言 EXPECTED = = ACTUAL。若要打印不同的值，请使用 ASSERT _ eq _ fmt。要与自定义相等性测试和打印函数进行比较，请使用 ASSERT _ equal _ t。

### `ASSERT_NEQ(EXPECTED, ACTUAL)`

Assert that `EXPECTED != ACTUAL`.

断言被期待! = 实际。

### `ASSERT_GT(EXPECTED, ACTUAL)`

Assert that `EXPECTED > ACTUAL`.

断言预期 > 实际。

### `ASSERT_GTE(EXPECTED, ACTUAL)`

Assert that `EXPECTED >= ACTUAL`.

断言 EXPECTED > = ACTUAL。

### `ASSERT_LT(EXPECTED, ACTUAL)`

Assert that `EXPECTED < ACTUAL`.

断言预期 < 实际。

### `ASSERT_LTE(EXPECTED, ACTUAL)`

Assert that `EXPECTED <= ACTUAL`.

断言预期 < = 实际。

### `ASSERT_EQ_FMT(EXPECTED, ACTUAL, FORMAT)`

Assert that `EXPECTED == ACTUAL`. If they are not equal, print their values using `FORMAT` as the `printf` format string.

断言 EXPECTED = = ACTUAL。如果它们不相等，使用 FORMAT 作为格式化字符串输出它们的值。

For example: `ASSERT_EQ_FMT(123, result, "%d");` will call `printf` like `printf("Expected: %d\nGot: %d\n", 123, result);` if its `EXPECTED` and `ACTUAL` arguments don't match.

例如: ASSERT _ eq _ fmt (123，result,”% d”) ; 将像 printf 一样调用 printf (“ EXPECTED:% d nGot:% d n”，123，result) ; 如果它的 EXPECTED 参数和 ACTUAL 参数不匹配。

Note: `EXPECTED` and `ACTUAL` will be evaluated more than once on failure, so they should not be a function call with side effects. (Since their type is not known by the macro, they cannot be captured in a local variable. `typeof` is a GCC extension.)

注意: EXPECTED 和 ACTUAL 在失败时将被多次评估，所以它们不应该是带有副作用的函数调用。(由于宏不知道它们的类型，因此不能在局部变量中捕获它们。Typeof 是 GCC 扩展名。)

### `ASSERT_IN_RANGE(EXPECTED, ACTUAL, TOLERANCE)`

Assert that `ACTUAL` is within `EXPECTED` +/- `TOLERANCE`, once the values have been converted to a configurable floating point type (`GREATEST_FLOAT`).

一旦值被转换为可配置的浮点类型(GREATEST _ float) ，就断言 ACTUAL 在 EXPECTED +/-TOLERANCE 范围内。

greatest does not depent on floating point math. It is only used within `ASSERT_IN_RANGE`'s macro expansion.

不依赖于浮点数学。它只在 asser_in_range 的宏扩展中使用。

### `ASSERT_STR_EQ(EXPECTED, ACTUAL)`

Assert that the strings are equal (i.e., `strcmp(EXPECTED, ACTUAL) == 0`).

断言字符串相等(即，strcmp (EXPECTED，ACTUAL) = = 0)。

### `ASSERT_STRN_EQ(EXPECTED, ACTUAL, SIZE)`

Assert that the first `SIZE` bytes of the strings are equal (i.e., `strncmp(EXPECTED, ACTUAL, SIZE) == 0`).

断言字符串的第一个 SIZE 字节相等(即 strncmp (EXPECTED，ACTUAL，SIZE) = = 0)。

### `ASSERT_MEM_EQ(EXPECTED, ACTUAL, SIZE)`

Assert that the first `SIZE` bytes of memory pointed to by `EXPECTED` and `ACTUAL` are equal. If their memory differs, print a hexdump and highlight the lines and individual bytes which do not match.

断言 EXPECTED 和 ACTUAL 指向的内存的第一个 SIZE 字节相等。如果它们的内存不同，打印一个 hexdump 并突出显示不匹配的行和单个字节。

### `ASSERT_ENUM_EQ(EXPECTED, ACTUAL, ENUM_STR_FUN)`

Assert that the enum value `EXPECTED` is equal to `ACTUAL`. If not, convert each enum value to a string using `ENUM_STR_FUN` before printing them.

断言枚举值 EXPECTED 等于 ACTUAL。如果没有，则在打印之前使用 enum_str _ fun 将每个枚举值转换为字符串。

`ENUM_STR_FUN` should have a type like:

应该有这样的类型:

```
const char *FUN(int x);
```

### `ASSERT_EQUAL_T(EXPECTED, ACTUAL, TYPE_INFO, UDATA)`

Assert that `EXPECTED` and `ACTUAL` are equal, using the `greatest_equal_cb` function pointed to by `TYPE_INFO->equal` to compare them. The assertion's `UDATA` argument can be used to pass in arbitrary user data (or `NULL`) to the callbacks. If the values are not equal and the `TYPE_INFO->print` function is defined, it will be used to print an "Expected: X, Got: Y" message.

断言 EXPECTED 和 ACTUAL 相等，使用 TYPE _ info-> equal 指向的 greatest _ equal _ cb 函数来比较它们。可以使用断言的 UDATA 参数将任意用户数据(或 NULL)传递给回调。如果值不相等，并且定义了 TYPE _ info-> print 函数，那么它将用于打印“ Expected: x，Got: y”消息。

### `ASSERT_OR_LONGJMP(COND)`

Assert that `COND` evaluates to a true value. If not, then use `longjmp(3)` to immediately return from the test case and any intermediate function calls.

断言 COND 的计算结果为真值。如果没有，那么使用 longjmp (3)从测试用例和任何中间函数调用中立即返回。

If built with `GREATEST_USE_LONGJMP` `#define`d to 0, then all setjmp/longjmp-related functionality will be compiled out. This also reduces memory usage by `sizeof jmp_buf`, which may be several hundred bytes, depending on the platform.

如果使用 GREATEST _ use _ longjmp # 定义为0来构建，那么所有与 setjmp/longjmp 相关的功能都将被编译出来。这也减少了 jmp _ buf 的内存使用，根据平台的不同，jmp _ buf 可能有几百个字节。

## Random Shuffling 随机洗牌

Groups of suites or tests can be run in shuffled order by using `GREATEST_SHUFFLE_SUITES` and `GREATEST_SHUFFLE_TESTS`, respectively. This can help find and eliminate accidental coupling between tests.

可以分别使用 GREATEST shuffle _ suites 和 GREATEST shuffle _ tests 以混乱的顺序运行一组套件或测试。这可以帮助查找和消除测试之间的偶然耦合。

The shuffling depends on the seed and the test/suite count, so a consistent seed will only lead to reproducible ordering until the group's count changes.

洗牌取决于种子和测试/套件计数，因此一致的种子只会导致可重复的排序，直到组的计数发生变化。

Shuffling suites:

洗牌组曲:

```
SHUFFLE_SUITES(seed, {
    RUN_SUITE(suite1);
    RUN_SUITE(suite2);
    RUN_SUITE(suite3);
    RUN_SUITE(suite4);
    RUN_SUITE(suite5);
});
```

Shuffling tests:

洗牌测试:

```
SHUFFLE_TESTS(seed, {
    RUN_TEST(test_a);
    RUN_TEST1(test_b, 12345);
    RUN_TEST(test_c);
    RUN_TESTp(test_d, "some_argument");
    RUN_TEST(test_e);
});
```

Note: Any other code inside the block will be executed several times. The shuffling macro expands to a loop with (count + 1) iterations -- the first pass counts, and the following passes only execute the next chosen suite/test. In particular, avoid running tests directly inside of a `SHUFFLE_SUITES` block without a suite, because the test will be run on each iteration.

注意: 块中的任何其他代码将被多次执行。混排宏扩展为一个循环，其中包含(计数 + 1)迭代——第一次传递计数，以下传递只执行下一次选择的套件/测试。特别是，避免在没有套件的 SHUFFLE _ suites 块中直接运行测试，因为测试将在每次迭代中运行。

## Test Name Suffixes 测试名称后缀

`greatest_set_test_suffix` can be used to set an optional name suffix for the next test:

可以使用 greatest _ set _ test _ suffix 为下一个测试设置一个可选的名称后缀:

```
for (i = 0; i < row_count; i++) {
    const struct table_row *row = &table[row_count];
    greatest_set_test_suffix(row->name);
    RUN_TEST1(test_with_arg, row);
}
```

This will cause the test name to print with a `_` separator and the suffix in all pass/fail/skip messages (i.e., `test_with_arg_KEY`). This is especially useful when running a test several times with different arguments, in shuffled order. The name suffix is included when using name-based filtering.

这将导致使用 _ separator 打印测试名称，并在所有 pass/fail/skip 消息中使用后缀(例如，使用 _ arg _ key 进行 test _)。当使用不同的参数以混乱的顺序多次运行一个测试时，这尤其有用。当使用基于名称的筛选时，会包含名称后缀。

The test name and optional suffix are copied into an internal buffer. Its size can be configured by `#define`ing the constant `GREATEST_TESTNAME_BUF_SIZE`. (If not `#define`d, it defaults to 128 bytes.) If the buffer is not large enough for the name and suffix, it will truncate after `size - 1` bytes, to ensure that it is properly `\0`-terminated.

测试名称和可选后缀被复制到内部缓冲区中。它的大小可以通过 # 定义常量 GREATEST _ testname _ buf _ size 来配置。(如果没有 # defined，则默认为128字节。)如果缓冲区对于名称和后缀来说不够大，它将在 size-1字节之后截断，以确保它正确地以0结尾。

The name suffix pointer is cleared after each `RUN_TEST*` call, so a suffix can be constructed in a stack allocated buffer without later dereferencing a pointer that has gone out of scope.

名称后缀指针在每次 RUN _ test * 调用后被清除，因此可以在堆栈分配的缓冲区中构造一个后缀，而不需要稍后解引用超出范围的指针。

## Sub-Functions 附属职能

Because of how `PASS()`, `ASSERT()`, `FAIL()`, etc. are implemented (returning a test result enum value), calls to functions that use them directly from test functions must be wrapped in `CHECK_CALL`:

由于 PASS ()、 ASSERT ()、 FAIL ()等是如何实现的(返回一个测试结果 enum 值) ，从测试函数直接使用它们的函数调用必须包装在 CHECK _ call 中:

```
TEST example_using_subfunctions(void) {
    CHECK_CALL(less_than_three(5));
    PASS();
}
```

This is only necessary if the called function can cause test failures. The function should have a return type of `enum greatest_test_res`.

只有在被调用的函数会导致测试失败时才需要这样做。函数的返回类型应该是 enum greatest _ test _ res。

## Command Line Options 命令行选项

Test runners build with the following command line options:

测试运行器使用以下命令行选项进行构建:

```
Usage: (test_runner) [-hlfave] [-s SUITE] [-t TEST] [-x EXCLUDE]
  -h, --help  print this Help
  -l          List suites and tests, then exit (dry run)
  -f          Stop runner after first failure
  -a          Abort on first failure (implies -f)
  -v          Verbose output
  -s SUITE    only run suite w/ name containing substring SUITE
  -t TEST     only run test w/ name containing substring TEST
  -e          only run exact name match for -s or -t
  -x EXCLUDE  exclude tests containing string substring EXCLUDE
```

Any arguments after `--` will be ignored.

之后的任何参数都将被忽略。

If you want to run multiple test suites in parallel, look at [parade](https://github.com/silentbicycle/parade).

如果希望并行运行多个测试套件，请参阅 parade。

These command line options are processed by `GREATEST_MAIN_BEGIN();`.

这些命令行选项由 GREATEST _ main _ begin ()处理;。

## Running Tests In Another Program 在另一个程序中运行测试

Rather than producing a command line test runner (which checks the command line options, and exits with a pass/fail return code after running tests), greatest can be used more like a library. Instead of using `GREATEST_MAIN_BEGIN()`, use `GREATEST_INIT()` to (re-)initialize greatest, then use either `GREATEST_PRINT_REPORT()` to print the report to `GREATEST_STDOUT`, or use `greatest_get_report(&report)` to get the pass, fail, skip, and assertion counters.

与其生成一个命令行测试运行器(它检查命令行选项，并在运行测试后使用通过/失败返回代码退出) ，不如更像一个库那样使用 greatest。不使用 GREATEST _ main _ begin () ，而是使用 GREATEST _ init ()来(重新)初始化 GREATEST，然后使用 GREATEST _ print _ report ()将报告打印到 GREATEST _ stdout，或者使用 GREATEST _ get _ report (& report)来获取通过、失败、跳过和断言计数器。

The command line flags above have corresponding functions:

上面的命令行标志有相应的函数:

- `greatest_stop_at_first_fail()`
- `greatest_abort_on_fail()`
- `greatest_list_only()`
- `greatest_set_exact_name_match()`
- `greatest_set_suite_filter(const char *filter)`
- `greatest_set_test_filter(const char *filter)`
- `greatest_set_test_exclude(const char *filter)`
- `greatest_get_verbosity()`
- `greatest_set_verbosity(unsigned int verbosity)`

## Aliases 别名

Most of the macros have prefixed and unprefixed forms. For example, `SUITE` is the same as `GREATEST_SUITE`.

大多数宏都有前缀和不前缀的形式。例如，SUITE 与 GREATEST _ SUITE 相同。

Check the source for the list -- search for `GREATEST_USE_ABBREVS`.

检查列表的源代码---- 搜索 GREATEST _ use _ abbrevs。

These aliases can be disabled by `#define`-ing `GREATEST_USE_ABBREVS` to 0.

这些别名可以通过 # define-ing GREATEST _ use _ abbrevs 到0来禁用。

## Color Output 彩色输出

If you want color output (`PASS` in green, `FAIL` in red, etc.), you can pipe the output through the included `greenest` script in `contrib/`:

如果需要颜色输出(PASS 为绿色，FAIL 为红色，等等) ，可以通过 contrib/中包含的 greenest 脚本管道输出:

```
$ ./example -v | greenest
```

(Note that `greenest` depends on a Unix-like environment.)

(注意 greenest 取决于类 unix 环境。)

greatest itself doesn't have built-in coloring to stay small and portable.

最伟大的本身并没有内置的颜色，以保持小和便携。

## TAP Format TAP 格式

There is an awk script provided, `contrib/entapment`, that converts the verbose output from the default CLI test runner to TAP version 13 format:

提供了一个 awk 脚本 contrib/entapment，它将默认 CLI 测试运行程序的详细输出转换为 TAP 13版本格式:

```
./example -v | contrib/entapment
```
