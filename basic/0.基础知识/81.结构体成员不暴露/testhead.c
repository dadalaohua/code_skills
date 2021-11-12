#include <stdlib.h>
#include <string.h>
#include "testhead.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct _testhead_s
{
    int val;
} _testhead_t;

/************************************************************************/
/*                                                                      */
/************************************************************************/
testhead_t* testhead_malloc(void)
{
    testhead_t* tmp = malloc(sizeof(testhead_t));
    memset(tmp, 0x00, sizeof(testhead_t));
    return tmp;
}

void testhead_set_val(testhead_t* temp, int val)
{
    temp->val = val;
}

int testhead_get_val(testhead_t* temp)
{
    return temp->val;
}