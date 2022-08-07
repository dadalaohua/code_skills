#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CONCATL(a, b)       a ## b
#define CONCATENATEL(a, b)  CONCATL(a, b)

#define GET_SEC(x, n, ...)  n
#define CHECK(...)          GET_SEC(__VA_ARGS__, 0)
#define PROBE(x)            x, 1

#define IS_EMPTY(x) CHECK(CONCATENATEL(CONCATL(IS_EMPTY_, x), 0))
#define IS_EMPTY_0  PROBE()

#define EMPTY()
#define DEFER(id) id EMPTY()

#define STRUCT_FOR_EACH(struct1, struct2, x, ...)   CONCATENATEL(STRUCT_FOR_EACH_, IS_EMPTY(x)) (struct1, struct2, x, __VA_ARGS__)
#define STRUCT_FOR_EACH_0(struct1, struct2, x, ...) (struct1 x == struct2 x) && DEFER(STRUCT_FOR_EACH_I)() (struct1, struct2, __VA_ARGS__)
#define STRUCT_FOR_EACH_1(...)                      1
#define STRUCT_FOR_EACH_I()                         STRUCT_FOR_EACH

#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

#define STRUCT_CMP(struct1, struct2, x, ...) (EVAL(STRUCT_FOR_EACH(struct1, struct2, x, __VA_ARGS__)))

#define STRUCT_DD_CMP(struct1, struct2, x, ...) STRUCT_CMP(struct1.,  struct2.,  x, __VA_ARGS__)    //Direct Member Access
#define STRUCT_II_CMP(struct1, struct2, x, ...) STRUCT_CMP(struct1->, struct2->, x, __VA_ARGS__)    //Indirect Member Access
#define STRUCT_ID_CMP(struct1, struct2, x, ...) STRUCT_CMP(struct1->, struct2.,  x, __VA_ARGS__)
#define STRUCT_DI_CMP(struct1, struct2, x, ...) STRUCT_CMP(struct1.,  struct2->, x, __VA_ARGS__)
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct test_struct{
    int a;
    char b;
};

struct test_struct_2{
    int a;
    char b;
    short c;
    unsigned int d;
    unsigned char e;
    unsigned short f;
};

struct test_struct_3{
    int a;
    struct test_struct b;
    char *c;
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
void test2(void) {
    struct test_struct x, y;
    x.a = y.a = 10;
    x.b = y.b = 10;
    printf("%d\n", memcmp(&x, &y, sizeof(struct test_struct)));
}

int test1(void) {
    char buf[10] = {0};
    for(int i = 0; i < 10; i++)
        buf[i] = i;
    return buf[0];
}

int main(int argc, char* argv[])
{
    test1();
    test2();
    
    struct test_struct x, y;
    x.a = y.a = 10;
    x.b = y.b = 10;
    printf("%d\n", STRUCT_CMP(x., y., a, b));
    printf("%d\n", STRUCT_DD_CMP(x, y, a, b));
    
    y.a = 5;
    y.b = 10;
    printf("%d\n", STRUCT_CMP(x., y., a, b));
    
    y.a = 10;
    y.b = 5;
    printf("%d\n", STRUCT_CMP(x., y., a, b));
    
    y.a = 8;
    y.b = 5;
    printf("%d\n", STRUCT_CMP(x., y., a, b));
    
    struct test_struct* q = &x;
    printf("%d\n", STRUCT_CMP(q->, y., a, b));
    y.a = 10;
    y.b = 10;
    printf("%d\n", STRUCT_CMP(q->, y., a, b));
    printf("%d\n", STRUCT_ID_CMP(q, y, a, b));
    
    printf("\n");
    
    struct test_struct_2 val1, val2;
    struct test_struct_2 *pval1, *pval2;
    pval1 = &val1;
    pval2 = &val2;
    val1.a = val2.a = 10;
    val1.b = val2.b = 11;
    val1.c = val2.c = 12;
    val1.d = val2.d = 13;
    val1.e = val2.e = 14;
    val1.f = val2.f = 15;
    printf("%d\n", STRUCT_CMP(val1., val2., a, b, c, d, e, f));
    printf("%d\n", STRUCT_CMP(pval1->, pval2->, a, b, c, d, e, f));
    printf("%d\n", STRUCT_CMP(val1., pval2->, a, b, c, d, e, f));
    printf("%d\n", STRUCT_CMP(pval1->, val2., a, b, c, d, e, f));
    
    printf("%d\n", STRUCT_DD_CMP(val1, val2, a, b, c, d, e, f));
    printf("%d\n", STRUCT_II_CMP(pval1, pval2, a, b, c, d, e, f));
    printf("%d\n", STRUCT_ID_CMP(pval1, val2, a, b, c, d, e, f));
    printf("%d\n", STRUCT_DI_CMP(val1, pval2, a, b, c, d, e, f));
    
    printf("\n");
    
    val2.f = 12;
    printf("%d\n", STRUCT_CMP(val1., val2., a, b, c, d, e, f));
    printf("%d\n", STRUCT_CMP(val1., val2., a, b, c, d, e));
    printf("%d\n", STRUCT_CMP(val1., val2., a));
    printf("%d\n", STRUCT_CMP(val1., val2., f));
    printf("%d\n", STRUCT_CMP(val1., val2., b, c, d));
    
    printf("\n");
    
    struct test_struct_3 data1, data2;
    data1.a = data2.a = 66;
    data1.b = data2.b = x;
    data1.c = data2.c = NULL;
    printf("%d\n", STRUCT_CMP(data1., data2., a, c));
    printf("%d\n", STRUCT_CMP(data1.b., data2.b., a, b));
    
    data1.c = malloc(sizeof(char) * 64);
    printf("%d\n", STRUCT_CMP(data1., data2., a, c));
    free(data1.c);
    
    return 0;
}