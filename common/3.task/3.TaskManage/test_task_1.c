#include <stdio.h>

#include "test_task.h"
#include "TaskManage.h"

unsigned int test_task_1_count = 0;

void test_task_1_poll(void)
{
    printf("test_task_1_poll %d\n", ++test_task_1_count);
}

int test_task_1_init(void)
{
    RegisterTask(1000, test_task_1_poll);

    return 0;
}