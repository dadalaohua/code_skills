#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
// As used in the linux kernel.
// A macro that expands to 1 if a preprocessor value
// was defined to 1, and 0 if it was not defined or
// defined to an other value.
// 这个宏，如果预处理器值定义为1，则扩展为1；如果未定义或未定义为其他值，则扩展为0。

#define IS_DEFINED(macro) IS_DEFINED_(macro)
#define MACROTEST_1 ,
#define IS_DEFINED_(value) IS_DEFINED__(MACROTEST_##value)
#define IS_DEFINED__(comma) IS_DEFINED___(comma 1, 0)
#define IS_DEFINED___(_, v, ...) v

// Can be used in preprocessor macros:
#if IS_DEFINED(SOMETHING)
    ...
#endif

// Or even directly in the code.
// Same effect but looks better.
// if (IS_DEFINED(SOMETHING)) {
    // ...
// }

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
#if IS_DEFINED(0)
    printf("IS_DEFINED(0)\n");
#endif

#if IS_DEFINED(1)
    printf("IS_DEFINED(1)\n");
#endif

#define TEST_MARCO_0 0
#define TEST_MARCO_1 1
#define TEST_MARCO_2 2

    if (IS_DEFINED(TEST_MARCO_0)) {
        printf("TEST_MARCO_0\n");
    }
    
    if (IS_DEFINED(TEST_MARCO_1)) {
        printf("TEST_MARCO_1\n");
    }
    
    if (IS_DEFINED(TEST_MARCO_2)) {
        printf("TEST_MARCO_2\n");
    }
    
    return 0;
}