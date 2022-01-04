#include <stdio.h>
#include <setjmp.h>

#include "cmockery.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
// A test case that does nothing and succeeds.
void null_test_success(void **state) {
    printf("null test success\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    const UnitTest tests[] = {
        unit_test(null_test_success),
        unit_test_with_prefix(someprefix_, null_test_success),
    };
    return run_tests(tests);
}