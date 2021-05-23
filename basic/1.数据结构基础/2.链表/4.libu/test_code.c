#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef int uintptr_t;

int test_list_iterator (void)
{
    enum { ITERS = 300 };
    u_list_t *l = NULL;
    void *it;
    size_t j, c;
    intptr_t i, v, tot0, tot1;

    u_list_create(&l);

    // u_test_err_ifm (u_list_count(l), "expecting no items!");
    printf("u_list_count(l) = %d\n", u_list_count(l));

    for (tot0 = 0, i = 1; i < ITERS; ++i)
    {
        u_list_add(l, (void*)i);
        tot0 += i;
    }

    for (i = 1; i < ITERS; ++i)
    {
        u_list_insert(l, (void*)i, i);
        tot0 += i;
    }

    for (tot1 = 0, v = (intptr_t) u_list_first(l, &it); 
            v != 0;
            v = (intptr_t) u_list_next(l, &it))
    {
        tot1 += v;
    }

    //u_test_err_if (tot0 != tot1);
    if(tot0 != tot1)
    {
        printf("tot0 != tot1");
    }

    /* remove some items */
    c = u_list_count(l)/2;
    for (j = 0; j < c; ++j)
    {
        u_list_del_n(l, 0, (void*)&v);
        tot0 -= v;
    }

    for (tot1 = 0, v = (intptr_t) u_list_first(l, &it); 
            v != 0; 
            v = (intptr_t) u_list_next(l, &it))
    {
        tot1 += v;
    }

    // u_test_err_if (tot0 != tot1);
    if(tot0 != tot1)
    {
        printf("tot0 != tot1");
    }

    u_list_free(l);

    return 0;
// err:
    // return -1;
}

int test_list_ins (void)
{
    enum { ITERS = 3 };
    u_list_t *l = NULL;
    uintptr_t i;
    void* prev;

    u_list_create(&l);
    u_list_add(l, (void*)1);
    u_list_add(l, (void*)2);
    u_list_add(l, (void*)99);
    u_list_add(l, (void*)2);
    u_list_add(l, (void*)4);

    u_list_insert(l, (void*)0, 0);
    u_list_insert(l, (void*)3, 3);
    u_list_del(l, (void*)99);
    u_list_del_n(l, 4, NULL);

    u_list_insert(l, (void*)99, 0);
    u_list_insert(l, (void*)99, u_list_count(l));

    u_list_del_n(l, 0, &prev);
    if((uintptr_t) prev != 99)
    {
        printf("uintptr_t) prev != 99\n");
        goto err;
    }

    u_list_del_n(l, u_list_count(l)-1, &prev);
    if((uintptr_t) prev != 99)
    {
        printf("uintptr_t) prev != 99\n");
        goto err;
    }

    for (i = 0; i < ITERS; ++i)
        u_list_insert(l, (void*)99, 2);
    for (i = 0; i < ITERS; ++i)
        u_list_del(l, (void*)99);

    for (i = 0; i < ITERS; ++i)
        u_list_insert(l, (void*)99, 2);

    for (i = 0; i < ITERS; ++i)
    {
        u_list_del_n(l, 2, &prev);
        if((uintptr_t) prev != 99)
        {
            printf("uintptr_t) prev != 99\n");
            goto err;
        }
    }

    for (i = 0; i < (uintptr_t) u_list_count(l); ++i)
    {
        if(i != (uintptr_t) u_list_get_n(l, i))
        {
            printf("%d != (uintptr_t) u_list_get_n(l, %d)\n", i, i);
            goto err;
        }
    }

    u_list_free(l);

    return 0;
err:
    if (l)
        u_list_free(l);
    
    return -1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    test_list_ins ();
    test_list_iterator ();
    
    return 0;
}