// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*Token 粘贴*/
#define PRIMITIVE_CAT(x, y) x ## y
#define CAT(x, y) PRIMITIVE_CAT(x, y)

/*模式匹配 if 语句*/
#define IIF(c) PRIMITIVE_CAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

/*取补*/
#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

/*检测 如果有 PROBE的调用 则第二个参数变为1，否则第二个参数保持不变为0*/
#define GET_SEC(x, n, ...) n
#define CHECK(...) GET_SEC(__VA_ARGS__, 0)
#define PROBE(x) x, 1

/*检测参数是否为空*/
#define IS_EMPTY(x) CHECK(CAT(PRIMITIVE_CAT(IS_EMPTY_, x), 0))
#define IS_EMPTY_0 PROBE()

/*取反*/
#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE()

/*转换为布尔值和 if 条件判断*/
#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))

/*完整的 IF 语句,  IF_ELSE 宏可以使用括号作为两个分支的分隔符*/
#define IF_ELSE(condition) CAT(_IF_,  BOOL(condition))
#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE
#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

/*循环, 非递归方案*/
#define FUNCTION(name) void name();
#define FUNCTION_TABLE(seq) CAT(FUNCTION_TABLE_1 seq, _END)
#define FUNCTION_TABLE_1(x) FUNCTION(x) FUNCTION_TABLE_2
#define FUNCTION_TABLE_2(x) FUNCTION(x) FUNCTION_TABLE_1
#define FUNCTION_TABLE_1_END
#define FUNCTION_TABLE_2_END

/*延迟展开*/
#define EMPTY()
#define DEFER(id) id EMPTY()

/*扫描*/
#define EXPAND(...) __VA_ARGS__

// /*列表粘贴*/
// #define LIST_PRIMITIVE_CAT(x, y, ...) x ## y
// #define LIST_CAT(x, ...) LIST_PRIMITIVE_CAT(x, __VA_ARGS__)

// /*检测参数列表是否为空*/
// #define IS_EMPTY_LIST(...) CHECK(LIST_CAT(LIST_PRIMITIVE_CAT(IS_EMPTY_LIST_, __VA_ARGS__), 0))
// #define IS_EMPTY_LIST_0 PROBE()
// #define LIST_PROBE(x) x, 1

// /*循环, 递归方案*/
// #define FOR_EACH(macro, ...) CAT(FOR_EACH_, IS_EMPTY_LIST(__VA_ARGS__)) (macro, __VA_ARGS__)
// #define FOR_EACH_0(macro, x, ...) macro(x) DEFER(FOR_EACH_I)() (macro, __VA_ARGS__)
// #define FOR_EACH_1(...)
// #define FOR_EACH_I() FOR_EACH

/*循环, 递归方案*/
#define FOR_EACH(macro, x, ...) CAT(FOR_EACH_, IS_EMPTY(x)) (macro, x, __VA_ARGS__)
#define FOR_EACH_0(macro, x, ...) macro(x) DEFER(FOR_EACH_I)() (macro, __VA_ARGS__)
#define FOR_EACH_1(...)
#define FOR_EACH_I() FOR_EACH

/*要用于循环替换的宏*/
#define FOO(x) (x + 10), //void x();

/*用 n^3 的增长速率来定义多个扫描*/
#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

// #define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
// #define IS_PAREN_PROBE(...) PROBE()
// #define __COUNT_ARGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _n, X...) _n
// #define COUNT_ARGS(X...) __COUNT_ARGS(, ##X, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
// #define TEST_MACRO(...) COUNT_ARGS(__VA_ARGS__)
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    // FUNCTION_TABLE((a) (b) (c) (x) (y) (z))
    
    // EXPAND(EXPAND(EXPAND(FOR_EACH(FOO, x, y, z)))) 
    // EVAL(FOR_EACH(FOO, x, y, z))
    // EVAL(FOR_EACH(FOO, a, b, c, x, y, z))
    
    //printf("%d\n", TEST_MACRO(1));
    // IS_PAREN(())
    // IS_PAREN(()12345)
    
    unsigned char buf[] = {EVAL(FOR_EACH(FOO, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10))};
    unsigned int i;
    
    for(i = 0;i < sizeof(buf); i++)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");
    
    IF_ELSE(0)(
        printf("test1 true\n");
    ) (
        printf("test1 false\n");
    )
    
    IF_ELSE(1)(
        printf("test1 true\n");
    ) (
        printf("test1 false\n");
    )
    
    return 0;
}