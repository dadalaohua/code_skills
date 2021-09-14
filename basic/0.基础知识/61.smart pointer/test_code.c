#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct meta {
    void (*dtor)(void *);
    void *ptr;
};

static struct meta *get_meta(void *ptr) {
    return ptr - sizeof (struct meta);
}

__attribute__((malloc))
void *smalloc(size_t size, void (*dtor)(void *)) {
    struct meta *meta = malloc(sizeof (struct meta) + size);
    *meta = (struct meta) {
        .dtor = dtor,
        .ptr  = meta + 1
    };
    return meta->ptr;
}

void sfree(void *ptr) {
    if (ptr == NULL)
        return;
    struct meta *meta = get_meta(ptr);
    assert(ptr == meta->ptr); // ptr shall be a pointer returned by smalloc
    meta->dtor(ptr);
    free(meta);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define smart __attribute__((cleanup(sfree_stack)))

__attribute__ ((always_inline))
inline void sfree_stack(void *ptr) {
    sfree(*(void **) ptr);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//析构函数
void print_int(void *ptr)
{
    (void) ptr;
    //printf("%d\n", *(int*) ptr);
}

int main(int argc, char* argv[])
{
    smart int *i = smalloc(sizeof(int), print_int);
    *i = 1;
    return *i;
}