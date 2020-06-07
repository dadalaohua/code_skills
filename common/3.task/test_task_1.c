#include <stdio.h>

#include "task.h"
#include "test_task.h"

task_t *test_task_1;

int test_task_1_poll(void *priv)
{  
    printf("test_task_1_poll\n");

    return 0;
}

int test_task_1_init(void)
{  
    task_alloc(&test_task_1);
    task_create(test_task_1, test_task_1_poll, NULL);
    task_sch(test_task_1, XTASK_GROUP_1S, XTASK_FLAG_RUNNING);

    return 0;
}