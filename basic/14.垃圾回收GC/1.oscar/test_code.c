#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "oscar.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct link {
    void *d;                    /* data */
    pool_id n;                  /* next */
} link;

static int mark_from_zero(oscar *p, void *udata) {
    int *zero_is_live = (int *) udata;

    if (*zero_is_live) {
        pool_id id = 0;         /* assume 0 is the root. */
        link *n = (link *) oscar_get(p, id);
        if (n == NULL) return 0;
        oscar_mark(p, id);
        id = n->n;

        while (id != 0) {
            oscar_mark(p, id);
            n = (link *) oscar_get(p, id);
            id = n->n;
        }
    }
    return 0;
}

static void basic_free_hook(oscar *pool, pool_id id, void *udata) {
    int *freed_flags = (int *) udata;
    freed_flags[id] = 1;
}

/* In a dynamically allocated 5-cell pool, check that live values
 * persist and unreachable values are swept as expected. */
void basic_dynamic(void) {
    int zero_is_live = 1;
    int basic_freed[] = {0,0,0,0,0};
    oscar *p = oscar_new(sizeof(link), 5, oscar_generic_mem_cb, NULL,
        mark_from_zero, &zero_is_live,
        basic_free_hook, basic_freed);
    //ASSERT(p);
    unsigned int count = oscar_count(p);
    pool_id id = oscar_alloc(p);
    //ASSERT_EQ(0, id);
    printf("id %d\n", id);
    link *l = (link *) oscar_get(p, id);
    link *l1 = NULL;
    //ASSERT(l->d == NULL);
    //ASSERT_EQ(0, l->n);         /* [0] */
    printf("l->n %d\n", l->n);
    //ASSERT(l);

    id = oscar_alloc(p);
    //ASSERT_EQ(1, id);
    printf("id %d\n", id);
    l->n = id;                  /* [0] -> [1] */
    l = (link *) oscar_get(p, id);
    //ASSERT(l);
    l1 = l;

    id = oscar_alloc(p);
    //ASSERT_EQ(2, id);
    printf("id %d\n", id);
    l->n = id;                  /* [0] -> [1] -> [2] */
    l = (link *) oscar_get(p, id);
    //ASSERT(l);

    /* Allocate a couple cells that aren't kept live, to force GC */
    for (int i=0; i<count; i++) (void) oscar_alloc(p);
    id = oscar_alloc(p);
    //ASSERT_EQ(4, id);
    printf("id %d\n", id);
    l1->n = id;                 /* [0] -> [1] -> [n], 2 is garbage */
    
    /* Allocate a couple cells that aren't kept live, to force GC */
    for (int i=0; i<count; i++) (void) oscar_alloc(p);
    //ASSERT_EQ(1, basic_freed[2]);
    printf("basic_freed[2] %d\n", basic_freed[2]);

    for (int i=0; i<count; i++) basic_freed[i] = 0;

    zero_is_live = 0;           /* [0] is no longer root, all are garbage */
    oscar_force_gc(p);

    for (int i=0; i<count; i++) {
        //ASSERT_EQ(1, basic_freed[i]);
        printf("basic_freed[%d] %d\n", i, basic_freed[i]);
    }
    
    oscar_free(p);
}

/* Roughly the same as basic_dynamic, but build the GC pool
 * in statically allocated memory. */
void basic_static(void) {
    int zero_is_live = 1;
    int SZ = (88 + 10*(sizeof(link)));
    int basic_freed[SZ];
    char raw_mem[SZ];
    oscar *p = oscar_new_fixed(sizeof(link), SZ, raw_mem,
        mark_from_zero, &zero_is_live,
        basic_free_hook, basic_freed);
    //ASSERTm("no oscar *", p);
    bzero(basic_freed, SZ * sizeof(int));
    unsigned int count = oscar_count(p);
    pool_id id = oscar_alloc(p);
    //ASSERT_EQ(0, id);
    printf("id %d\n", id);
    link *l = (link *) oscar_get(p, id);
    link *l1 = NULL;
    //ASSERT(l->d == NULL);
    //ASSERT_EQ(0, l->n);         /* [0] */
    printf("l->n %d\n", l->n);
    //ASSERT(l);

    id = oscar_alloc(p);
    //ASSERT_EQ(1, id);
    printf("id %d\n", id);
    l->n = id;                  /* [0] -> [1] */
    l = (link *) oscar_get(p, id);
    //ASSERT(l);
    l1 = l;

    id = oscar_alloc(p);
    //ASSERT_EQ(2, id);
    printf("id %d\n", id);
    l->n = id;                  /* [0] -> [1] -> [2] */
    l = (link *) oscar_get(p, id);
    //ASSERT(l);

    /* Allocate a couple cells that aren't kept live, to force GC */
    for (int i=0; i<count; i++) (void) oscar_alloc(p);
    id = oscar_alloc(p);
    l1->n = id;                 /* [0] -> [1] -> [n], 2 is garbage */
   
    /* Allocate a couple cells that aren't kept live, to force GC */
    for (int i=0; i<count; i++) (void) oscar_alloc(p);
    //ASSERT_EQ(1, basic_freed[2]);
    printf("basic_freed[2] %d\n", basic_freed[2]);

    for (int i=0; i<5; i++) basic_freed[i] = 0;

    zero_is_live = 0;           /* [0] is no longer root, all are garbage */
    oscar_force_gc(p);

    for (int i=0; i<5; i++) {
        //ASSERT_EQ(1, basic_freed[i]);
        printf("basic_freed[%d] %d\n", i, basic_freed[i]);
    }
    
    oscar_free(p);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    basic_dynamic();
    basic_static();
    return 0;
}