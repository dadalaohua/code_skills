#include <stdio.h>

#include "uthash.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct {
    void *key;
    int i;
    UT_hash_handle hh;
} el_t;

el_t *hash = NULL;
char *someaddr = NULL;

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    el_t *d;
    el_t *e = (el_t *)malloc(sizeof *e);
    if (!e) return -1;
    e->key = (void*)someaddr;
    e->i = 1;
    HASH_ADD_PTR(hash, key, e);
    HASH_FIND_PTR(hash, &someaddr, d);
    if (d) printf("found\n");

    /* release memory */
    HASH_DEL(hash, e);
    free(e);

    return 0;
}