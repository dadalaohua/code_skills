#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "testhead.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
testhead_t* test_head;

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    test_head = testhead_malloc();
    
    testhead_set_val(test_head, 1);
    
    printf("%d\n", testhead_get_val(test_head));
    //printf("%d\n", test_head->val); //未知
    return 0;
}