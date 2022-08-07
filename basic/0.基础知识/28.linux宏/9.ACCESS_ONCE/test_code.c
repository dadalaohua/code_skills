#include <stdio.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    https://elixir.bootlin.com/linux/v3.10.108/source/include/linux/compiler.h
*/

/*
 * Prevent the compiler from merging or refetching accesses.  The compiler
 * is also forbidden from reordering successive instances of ACCESS_ONCE(),
 * but only when the compiler is aware of some particular ordering.  One way
 * to make the compiler aware of ordering is to put the two invocations of
 * ACCESS_ONCE() in different C statements.
 *
 * This macro does absolutely -nothing- to prevent the CPU from reordering,
 * merging, or refetching absolutely anything at any time.  Its main intended
 * use is to mediate communication between process-level code and irq/NMI
 * handlers, all running on the same CPU.
 */
#define ACCESS_ONCE(x) (*(volatile typeof(x) *)&(x))
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct {
    void (*func)(void);
} test_struct_t;

test_struct_t *global_ptr = NULL;

void test_printf(void) {
    printf("test_printf\n");
}

void test(void) {
    
    printf("test\n");
    
    test_struct_t *p;
    // p = global_ptr;
    p = ACCESS_ONCE(global_ptr);
    if (p && p->func)
        p->func();
}

int main(int argc, char* argv[])
{
    test();
    test_struct_t x;
    x.func = test_printf;
    global_ptr = &x;
    test();
    global_ptr = NULL;
    test();

    return 0;
}