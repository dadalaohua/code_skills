#include <stdio.h>

#include "test_task.h"
#include "TaskManage.h"

unsigned int test_task_2_count = 0;

void test_task_2_poll(void)
{
    printf("test_task_2_poll %d\n", ++test_task_2_count);
}

int test_task_2_init(void)
{
    RegisterTask(500, test_task_2_poll);

    return 0;
}