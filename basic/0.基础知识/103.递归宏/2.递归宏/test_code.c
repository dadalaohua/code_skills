#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define HMStringify(A) _HMStringify(A)
#define _HMStringify(A) #A

#define HMConcat(A, B) _HMConcat(A, B)
#define _HMConcat(A, B) A##B

#define HMMacroArgCheck(...) _HMMacroArgCheck(__VA_ARGS__, N, N, N, N, N, N, N, N, N, 1)
#define _HMMacroArgCheck(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, TARGET, ...) TARGET

#define HMPrint(...) printf(HMStringify(HMExpand(HMForeach(_HMFormat, __VA_ARGS__))), __VA_ARGS__)
#define _HMFormat(A) A->%d\n

#define HMForeach(MACRO, ...) HMConcat(_HMForeach, HMMacroArgCheck(__VA_ARGS__)) (MACRO, __VA_ARGS__)
#define _HMForeach() HMForeach
#define _HMForeach1(MACRO, A) MACRO(A)
#define _HMForeachN(MACRO, A, ...) MACRO(A)HMDefer(_HMForeach)() (MACRO, __VA_ARGS__)

#define HMEmpty()
#define HMDefer(ID) ID HMEmpty()

#define HMExpand(...)   _HMExpand1(_HMExpand1(_HMExpand1(__VA_ARGS__)))
#define _HMExpand1(...) _HMExpand2(_HMExpand2(_HMExpand2(__VA_ARGS__)))
#define _HMExpand2(...) _HMExpand3(_HMExpand3(_HMExpand3(__VA_ARGS__)))
#define _HMExpand3(...) __VA_ARGS__

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    #define Increase(X) X += 1; // 定义一个宏，准备用来处理每一个参数。注意最后有分号
    int aa = 10, bb = 20, cc = 30;
    // 使用HMForeach需要有HMExpand包裹起来，以便多次扫描顺利展开
    HMExpand(HMForeach(Increase, aa, bb, cc))
    
    //printf(HMStringify(HMExpand(HMForeach(_HMFormat, a, b, c))), a, b, c);
    HMPrint(aa, bb, cc);
    
    return 0;
}