#include <stdio.h>

#include "task.h"
#include "test_task.h"

task_t *test_task_2;

int test_task_2_poll(void *priv)
{  
    printf("test_task_2_poll\n");

    return 0;
}

int test_task_2_init(void)
{  
    task_alloc(&test_task_2);
    task_create(test_task_2, test_task_2_poll, NULL);
    task_sch(test_task_2, XTASK_GROUP_500MS, XTASK_FLAG_RUNNING);

    return 0;
}