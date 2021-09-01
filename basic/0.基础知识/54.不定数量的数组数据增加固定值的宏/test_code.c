#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define __COUNT_ARGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _n, X...) _n
#define COUNT_ARGS(X...) __COUNT_ARGS(, ##X, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define __CONCATL(a, b) a ## b
#define CONCATENATEL(a, b) __CONCATL(a, b)

#define TEST_MACRO_2(offset, _0, ...)   {(offset+_0)}
#define TEST_MACRO_3(offset, _0, _1, ...)   {(offset+_0), (offset+_1)}
#define TEST_MACRO_4(offset, _0, _1, _2, ...)   {(offset+_0), (offset+_1), (offset+_2)}
#define TEST_MACRO_5(offset, _0, _1, _2, _3, ...) {(offset+_0), (offset+_1), (offset+_2), (offset+_3)}
#define TEST_MACRO_6(offset, _0, _1, _2, _3, _4, ...) {(offset+_0), (offset+_1), (offset+_2), (offset+_3), (offset+_4)}
#define TEST_MACRO_7(offset, _0, _1, _2, _3, _4, _5, ...) {(offset+_0), (offset+_1), (offset+_2), (offset+_3), (offset+_4), (offset+_5)}
#define TEST_MACRO_8(offset, _0, _1, _2, _3, _4, _5, _6, ...) {(offset+_0), (offset+_1), (offset+_2), (offset+_3), (offset+_4), (offset+_5), (offset+_6)}

#define TEST_MACRO(...) CONCATENATEL(TEST_MACRO_, COUNT_ARGS(__VA_ARGS__)) (__VA_ARGS__)

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char buf[] = TEST_MACRO(10, 1, 2, 3, 4, 5);
    unsigned int i;
    
    for(i = 0;i < sizeof(buf); i++)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");
    
    return 0;
}