#include <stdio.h>

#include "test_task.h"
#include "timeslice.h"

TimesilceTaskObj task_1;
unsigned int test_task_1_count = 0;

void test_task_1_poll(void)
{
    printf("test_task_1_poll %d\n", ++test_task_1_count);
}

int test_task_1_init(void)
{
    timeslice_task_init(&task_1, test_task_1_poll, 1, 1000);
    timeslice_task_add(&task_1);

    return 0;
}