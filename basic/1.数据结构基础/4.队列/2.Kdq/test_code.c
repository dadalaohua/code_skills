#include <stdio.h>

#include "kdq.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
KDQ_INIT(int)

void example_function(void)
{
    int i, *t;
    kdq_t(int) *q;
    q = kdq_init(int);
    kdq_push(int, q, 7);     // add an element from the tail
    kdq_unshift(int, q, 5);  // ddd an element from the head
    kdq_unshift(int, q, 3);  // ddd an element from the head
    t = kdq_shift(int, q);   // get an element from the head
    printf("head=%d\n\n", *t);
    
    for (i = 0; i < kdq_size(q); ++i) // iterate from head to tail
        printf("q[%d]=%d\n", i, kdq_at(q, i));
    kdq_destroy(int, q);
}

void my_test_function(void)
{
    int i, len;
    kdq_t(int) *q;
    q = kdq_init(int);
    kdq_push(int, q, 17);     // add an element from the tail
    kdq_unshift(int, q, 15);  // ddd an element from the head
    kdq_push(int, q, 16);     // add an element from the tail
    kdq_unshift(int, q, 13);  // ddd an element from the head
    
    len = kdq_size(q);
    for (i = 0; i < len; ++i)
        printf("q[%d]=%d\n", i, *(int *)kdq_pop(int, q));
    
    printf("kdq_size=%ld\n", kdq_size(q));
    
    kdq_destroy(int, q);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    example_function();
    printf("\n");
    my_test_function();
    
    return 0;
}