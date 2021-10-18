#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

#include "utarray.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
Integers
~~~~~~~~
This example makes a utarray of integers, pushes 0-9 into it, then prints it.
Lastly it frees it.

.Integer elements
*/
void test_function_1(void)
{
    UT_array *nums;
    int i, *p;

    //allocate a new array
    utarray_new(nums,&ut_int_icd);
    for(i=0; i < 10; i++) utarray_push_back(nums,&i);//push element p onto a

    //get first element of a
    for(p=(int*)utarray_front(nums);
      p!=NULL;
      p=(int*)utarray_next(nums,p)) {//get element of a following e (front if e is NULL)
    printf("%d\n",*p);
    }

    //free an allocated array
    utarray_free(nums);
}

void test_function_1_1(void)
{
    UT_array *nums = (UT_array*)malloc(sizeof(UT_array));
    int i, *p;

    //init an array (non-alloc)
    utarray_init(nums,&ut_int_icd);
    for(i=0; i < 10; i++) utarray_push_back(nums,&i);//push element p onto a

    //get first element of a
    for(p=(int*)utarray_front(nums);
      p!=NULL;
      p=(int*)utarray_next(nums,p)) {//get element of a following e (front if e is NULL)
    printf("%d\n",*p);
    }

    //dispose of an array (non-allocd)
    utarray_done(nums);
}

/*
Strings
~~~~~~~
In this example we make a utarray of strings, push two strings into it, print
it and free it.

.String elements
*/
void test_function_2(void)
{
    UT_array *strs;
    char *s, **p;

    utarray_new(strs,&ut_str_icd);

    s = "hello"; utarray_push_back(strs, &s);
    s = "world"; utarray_push_back(strs, &s);
    p = NULL;
    while ( (p=(char**)utarray_next(strs,p))) {
    printf("%s\n",*p);
    }

    utarray_free(strs);
}

/*
Scalar types
~~~~~~~~~~~~

The next example uses `UT_icd` with all its defaults to make a utarray of
`long` elements. This example pushes two longs, prints them, and frees the
array.

.long elements
*/
void test_function_3(void)
{
    UT_icd long_icd = {sizeof(long), NULL, NULL, NULL };

    UT_array *nums;
    long l, *p;
    utarray_new(nums, &long_icd);

    l=1; utarray_push_back(nums, &l);
    l=2; utarray_push_back(nums, &l);

    p=NULL;
    while( (p=(long*)utarray_next(nums,p))) printf("%ld\n", *p);

    utarray_free(nums);
}

/*
Structures
~~~~~~~~~~

Structures can be used as utarray elements. If the structure requires no
special effort to initialize, copy or destruct, we can use `UT_icd` with all
its defaults. This example shows a structure that consists of two integers. Here
we push two values, print them and free the array.

.Structure (simple)
*/
void test_function_4(void)
{
    typedef struct {
        int a;
        int b;
    } intpair_t;

    UT_icd intpair_icd = {sizeof(intpair_t), NULL, NULL, NULL};

    UT_array *pairs;
    intpair_t ip, *p;
    utarray_new(pairs,&intpair_icd);

    ip.a=1;  ip.b=2;  utarray_push_back(pairs, &ip);
    ip.a=10; ip.b=20; utarray_push_back(pairs, &ip);

    for(p=(intpair_t*)utarray_front(pairs);
        p!=NULL;
        p=(intpair_t*)utarray_next(pairs,p)) {
      printf("%d %d\n", p->a, p->b);
    }

    utarray_free(pairs);
}

/*
The real utility of `UT_icd` is apparent when the elements of the utarray are
structures that require special work to initialize, copy or destruct.

For example, when a structure contains pointers to related memory areas that
need to be copied when the structure is copied (and freed when the structure is
freed), we can use custom `init`, `copy`, and `dtor` members in the `UT_icd`.

Here we take an example of a structure that contains an integer and a string.
When this element is copied (such as when an element is pushed into the array),
we want to "deep copy" the `s` pointer (so the original element and the new
element point to their own copies of `s`). When an element is destructed, we
want to "deep free" its copy of `s`. Lastly, this example is written to work
even if `s` has the value `NULL`.

.Structure (complex)
*/
void test_function_5(void)
{
    typedef struct {
        int a;
        char *s;
    } intchar_t;

    void intchar_copy(void *_dst, const void *_src) {
      intchar_t *dst = (intchar_t*)_dst, *src = (intchar_t*)_src;
      dst->a = src->a;
      dst->s = src->s ? strdup(src->s) : NULL;
    }

    void intchar_dtor(void *_elt) {
      intchar_t *elt = (intchar_t*)_elt;
      if (elt->s) free(elt->s);
    }

    UT_icd intchar_icd = {sizeof(intchar_t), NULL, intchar_copy, intchar_dtor};

    UT_array *intchars;
    intchar_t ic, *p;
    utarray_new(intchars, &intchar_icd);

    ic.a=1; ic.s="hello"; utarray_push_back(intchars, &ic);
    ic.a=2; ic.s="world"; utarray_push_back(intchars, &ic);

    p=NULL;
    while( (p=(intchar_t*)utarray_next(intchars,p))) {
        printf("%d %s\n", p->a, (p->s ? p->s : "null"));
    }

    utarray_free(intchars);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("test_function_1\n");
    test_function_1();
    printf("\n");
    
    printf("test_function_1_1\n");
    test_function_1_1();
    printf("\n");
    
    printf("test_function_2\n");
    test_function_2();
    printf("\n");
    
    printf("test_function_3\n");
    test_function_3();
    printf("\n");
    
    printf("test_function_4\n");
    test_function_4();
    printf("\n");
    
    printf("test_function_5\n");
    test_function_5();
    printf("\n");
    
    return 0;
}