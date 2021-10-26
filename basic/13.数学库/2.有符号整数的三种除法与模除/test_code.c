#define STB_DIVIDE_IMPLEMENTATION

#include <stdio.h>
#include <math.h>
#include <limits.h>

#include "stb_divide.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
int show=0;
int err=0;

void stbdiv_check(int q, int r, int a, int b, char *type, int dir)
{
    if ((dir > 0 && r < 0) || (dir < 0 && r > 0)) {
      fprintf(stderr, "FAILED: %s(%d,%d) remainder %d in wrong direction\n", type,a,b,r);
      err++;
    } else
      if (b != INT_MIN) // can't compute abs(), but if b==INT_MIN all remainders are valid
         if (r <= -abs(b) || r >= abs(b)) {
            fprintf(stderr, "FAILED: %s(%d,%d) remainder %d out of range\n", type,a,b,r);
            err++;
         }
    #ifdef STB_DIVIDE_TEST_64
    {
        STB_DIVIDE_TEST_64 q64 = q, r64=r, a64=a, b64=b;
        if (q64*b64+r64 != a64) {
            fprintf(stderr, "FAILED: %s(%d,%d) remainder %d doesn't match quotient %d\n", type,a,b,r,q);
            err++;
        }
    }
    #else
    if (q*b+r != a) {
        fprintf(stderr, "FAILED: %s(%d,%d) remainder %d doesn't match quotient %d\n", type,a,b,r,q);
        err++;
    }
    #endif
}

void test(int a, int b)
{
    int q,r;
    if (show) printf("(%+11d,%+d) |  ", a,b);
    q = stb_div_trunc(a,b), r = stb_mod_trunc(a,b);
    if (show) printf("(%+11d,%+2d)  ", q,r); stbdiv_check(q,r,a,b, "trunc",a);
    q = stb_div_floor(a,b), r = stb_mod_floor(a,b);
    if (show) printf("(%+11d,%+2d)  ", q,r); stbdiv_check(q,r,a,b, "floor",b);
    q = stb_div_eucl (a,b), r = stb_mod_eucl (a,b);
    if (show) printf("(%+11d,%+2d)\n", q,r); stbdiv_check(q,r,a,b, "euclidean",1);
}

void testh(int a, int b)
{
    int q,r;
    if (show) printf("(%08x,%08x) |\n", a,b);
    q = stb_div_trunc(a,b), r = stb_mod_trunc(a,b); stbdiv_check(q,r,a,b, "trunc",a);
    if (show) printf("             (%08x,%08x)", q,r);
    q = stb_div_floor(a,b), r = stb_mod_floor(a,b); stbdiv_check(q,r,a,b, "floor",b);
    if (show) printf("   (%08x,%08x)", q,r);
    q = stb_div_eucl (a,b), r = stb_mod_eucl (a,b); stbdiv_check(q,r,a,b, "euclidean",1);
    if (show) printf("   (%08x,%08x)\n ", q,r);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    if (argc > 1) show=1;

    test(8,3);
    test(8,-3);
    test(-8,3);
    test(-8,-3);
    test(1,2);
    test(1,-2);
    test(-1,2);
    test(-1,-2);
    test(8,4);
    test(8,-4);
    test(-8,4);
    test(-8,-4);

    test(INT_MAX,1);
    test(INT_MIN,1);
    test(INT_MIN+1,1);
    test(INT_MAX,-1);
    //test(INT_MIN,-1); // this traps in MSVC, so we leave it untested
    test(INT_MIN+1,-1);
    test(INT_MIN,-2);
    test(INT_MIN+1,2);
    test(INT_MIN+1,-2);
    test(INT_MAX,2);
    test(INT_MAX,-2);
    test(INT_MIN+1,2);
    test(INT_MIN+1,-2);
    test(INT_MIN,2);
    test(INT_MIN,-2);
    test(INT_MIN,7);
    test(INT_MIN,-7);
    test(INT_MIN+1,4);
    test(INT_MIN+1,-4);

    testh(-7, INT_MIN);
    testh(-1, INT_MIN);
    testh(1, INT_MIN);
    testh(7, INT_MIN);

    testh(INT_MAX-1, INT_MIN);
    testh(INT_MAX,   INT_MIN);
    testh(INT_MIN,   INT_MIN);
    testh(INT_MIN+1, INT_MIN);

    testh(INT_MAX-1, INT_MAX);
    testh(INT_MAX  , INT_MAX);
    testh(INT_MIN  , INT_MAX);
    testh(INT_MIN+1, INT_MAX);

    return err > 0 ? 1 : 0;
}